/*
 * gui_task.cpp
 *
 *  Created on: Aug 18, 2016
 *      Author: Holguer
 */

extern "C" {
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/mman.h>
}

#include <pthread.h>//Libreria para uso de Threads#include "../Nextion/Nextion.h"#include "../Interruptores/interruptores.h"#include "../rtc/rtc.h"#include "../Valves/valves.h"#include "../Network/Network.h"
#include "../Printer/printer.h"
#include "../DataLog/DataLogger.h"
#include "../audio/audio.h"
#include "../ADC/adcltc2308.h"
#include "../MAX6675/max6675.h"

/*--------------------------------------------------------------------------------------*/
/*
 * Variables Creadas en el main.cpp, que enlazan el hw con la aplicacion del sistem
 * */
extern HashTable Events_table; // ---> para registro de Eventos de Nextion
extern rtc * real_time_clock; // ----> obtner la hora del sistema
extern Network * Ethernet;   // ---> Para manejar la tarjeta de Red
extern printer * impresora; // ---> Para usar la Impresora(Depende de scrips de Python q estan en la carpeta /Stericlinic/Printer/Python)
extern DataLogger * grabador; // --> Para hacer registro de datos del sistema y de los ciclos, por medio de JSON
extern Nextion * LCD; // ---------> Para comunicarse con la pantalla Nextion
extern audio * sound_card; // -----> Para generar Sonidos
extern adc_ltc2308 * sensores_presion; //--> comunicarse con los sensores de presion
extern max6675 * sensores_temperatura; //--> comunicarse con los sensores de temperatura
extern valves * Valvulas; //---------------> tener acceso a las valvulas
extern interruptores * ElectroSondas; //---> tener acceso a la electrosondas
extern interruptores * Interrup; //--> para tener acceso a los interruptores de inicio, fin y final de carrera
int enviar_emergencia = 0; // --> bandera q sirve para determinar parado de mensaje de emergencia
/*--------------------------------------------------------------------------------------*/

/*EVENTOS DEL SISTEMA DE AUTOCLAVE
 *
 * print() --> Este evento es encargado e imprimir el ultimo ciclo guardado, q esta localizado en la carpeta /Stericlinic/Cycle2Print
 * button_val1_on() --> este evento se activa cuando se recibe un evento down de parte de el boton 1 q esta en el menu de mantenimiento, Valve1
 * 						se encarga de prender la valvula 1
 * button_val1_off() --> este evento se activa cuando se recibe un evento up de parte de el boton 1 q esta en el menu de mantenimiento, Valve1
 * 						se encarga de apagar la valvula 1
 * button_val2_on, button_val2_on == lo mismo que button_val1_on()
 * button_val2_off, button_val2_off == lo mismo que button_val1_off()
 * button_sp_121_mant_t() --> Cada vez q se recibe un evento up, del boton q esta en el menu de ajuste de Setpoint
 * 							  la pantalla Nextion recibe una variable q se guarda en el JSON del sistema, para actualizar la suma q se hace al oprimir este boton
 * 							  El Formato de datos en la pantalla nextion es la sigueinte:
 * 							  	Ejemplo:
 * 							  			1210 == 121.0
 * 							  			1215 == 121.5
 * 							    dentro del Nextion se hace la suma entera en pasos de 5, ya que Nextion
 * 							    no soporta flotantes, pero se escala por 10 el numero para q la suma se haga correctamente.
 * 							    en el caso de que se quiera usar este dato para CONTROL, se debe tener encuenta q se debe dividir en 10
 * 							    dentro del ARM la variable donde se guardan estos datos debe tener el formato signed short(16 bits con signo)
 * 							    de modo que se conserve el signo en los datos.
 * 							    Relacion 10:1
 *
 * 	Todas las funciones que finalicen en su nombre _mant_t, o _mant_p, son funciones que se hacen lo mismo que la funcion button_sp_121_mant_t() con la diferencia
 * 	que cada una de ella maneja una variable diferente, pero el formato de dato siempre esta escalado a 10.
 * 	En el caso de las funciones de error, nextion no suma de a pasos de 5, pero si de 1, y los valores pueden ser negativos
 *
 *
 * button_tiempos_esteri_121_mant_up() --> esta funcion recibe el evento up cuando se oprime el boton de aumento de tiempo
 * 										   al contrario de las funciones mant_t, mant_p, el formato del numero q se tiene aqui no esta escalado
 * 										   y su precision es de minuto, relacion 1:1
 * 										   1 --> 1 min
 * mant_up(), mant_down() --> todas funcionan de la misma manera que 	button_tiempos_esteri_121_mant_up()
 *
 * set_ip_function() --> Cuando se oprime el boton de setear la ip en la pantalla nextion se envia la ip q el usuario escribio
 * 						 se recibe por medio de esta funcion y se setea en el sistema.
 *
 * test_printer() --> en el momento q se recibe este evento se recibe un mensaje de parte de nextion.
 * 					  Que puede ser, "test_print" ó "alarma_printer"
 * 					  si recibe test_print ==> se envia la impresion
 * 					  de lo contrario no se imprime
 * */
int print(void * shared) {

	int last_cycle = grabador->init_configs["general"]["last_cycle"];

	/*
	 * La funcion printF de la impresora funciona exactamente igual q la funcion printf del estandar de C/C++
	 * esta funcion tiene la ventaja q se envia directamente un texto en el formato deseado a la impresora determinando
	 * la ubicacion del archivo de una manera simple y rapida
	 * Ejemplo:
	 * 	     impresora->printF("/%s/Cycle%dPrint/cyclep%d","Stericlinic" , 2 , last_cycle);
	 * 	                          ^		  ^             ^       v          v    v
	 * 	                          |       |				|		|		   |	|
	 * 							  --------|-------------|--------          |    |
	 * 							          --------------|-------------------    |
	 * 							          				-------------------------
	 * */
	impresora->printF("/Stericlinic/Cycle2Print/cyclep%d", last_cycle);
	printf("mandando a imprimir\n");

	return 0;
}

int button_val1_on(void * shared) {

	Valvulas->turn_on(0);

	return 0;
}

int button_val1_off(void * shared) {

	Valvulas->turn_off(0);

	return 0;
}

int button_val2_on(void * shared) {

	Valvulas->turn_on(1);

	return 0;
}

int button_val2_off(void * shared) {

	Valvulas->turn_off(1);

	return 0;
}

int button_val3_on(void * shared) {

	Valvulas->turn_on(2);

	return 0;
}

int button_val3_off(void * shared) {

	Valvulas->turn_off(2);

	return 0;
}

//evento para refrescar el valor de la GUI
int button_sp_121_mant_t(void * shared) {

	signed short number = 0;
	nextionRX * temp = (nextionRX*) shared;

	if (temp->lencommand) {
		number = temp->command[1];
		number = number | (temp->command[2] << 8);
		grabador->init_configs["gui"]["sp_121mant"]["Stemp121"] = number;
	} else {
		number = grabador->init_configs["gui"]["sp_121mant"]["Stemp121"];
	}

	return 0;
}

int button_sp_121_mant_p(void * shared) {

	signed short number = 0;
	nextionRX * temp = (nextionRX*) shared;

	if (temp->lencommand) {
		number = temp->command[1];
		number = number | (temp->command[2] << 8);
		grabador->init_configs["gui"]["sp_121mant"]["Spre121"] = number;
	} else {
		number = grabador->init_configs["gui"]["sp_121mant"]["Spre121"];
	}

	return 0;
}

//evento para refrescar el valor de la GUI
int button_sp_134_mant_t(void * shared) {

	signed short number = 0;
	nextionRX * temp = (nextionRX*) shared;

	if (temp->lencommand) {
		number = temp->command[1];
		number = number | (temp->command[2] << 8);
		grabador->init_configs["gui"]["sp_134mant"]["Stemp134"] = number;
	} else {
		number = grabador->init_configs["gui"]["sp_134mant"]["Stemp134"];
	}

	return 0;
}

int button_sp_134_mant_p(void * shared) {

	signed short number = 0;
	nextionRX * temp = (nextionRX*) shared;

	if (temp->lencommand) {
		number = temp->command[1];
		number = number | (temp->command[2] << 8);
		grabador->init_configs["gui"]["sp_134mant"]["Spre134"] = number;
	} else {
		number = grabador->init_configs["gui"]["sp_134mant"]["Spre134"];
	}

	return 0;
}

//evento para refrescar el valor de la GUI
int button_error_121_mant_t(void * shared) {

	signed short number = 0;
	nextionRX * temp = (nextionRX*) shared;

	if (temp->lencommand) {
		number = temp->command[1];
		number = number | (temp->command[2] << 8);
		grabador->init_configs["gui"]["error_121mant"]["Etemp121"] = number;
	} else {
		number = grabador->init_configs["gui"]["error_121mant"]["Etemp121"];
	}

	return 0;
}

int button_error_121_mant_p(void * shared) {

	signed short number = 0;
	nextionRX * temp = (nextionRX*) shared;

	if (temp->lencommand) {
		number = temp->command[1];
		number = number | (temp->command[2] << 8);
		grabador->init_configs["gui"]["error_121mant"]["Epres121"] = number;
	} else {
		number = grabador->init_configs["gui"]["error_121mant"]["Epres121"];
	}

	return 0;
}

//evento para refrescar el valor de la GUI
int button_error_134_mant_t(void * shared) {

	signed short number = 0;
	nextionRX * temp = (nextionRX*) shared;

	if (temp->lencommand) {
		number = temp->command[1];
		number = number | (temp->command[2] << 8);
		grabador->init_configs["gui"]["error_134mant"]["Etemp134"] = number;
	} else {
		number = grabador->init_configs["gui"]["error_134mant"]["Etemp134"];
	}

	return 0;
}

int button_error_134_mant_p(void * shared) {

	signed short number = 0;
	nextionRX * temp = (nextionRX*) shared;

	if (temp->lencommand) {
		number = temp->command[1];
		number = number | (temp->command[2] << 8);
		grabador->init_configs["gui"]["error_134mant"]["Epres134"] = number;
	} else {
		number = grabador->init_configs["gui"]["error_134mant"]["Epres134"];
	}

	return 0;
}

int button_tiempos_esteri_121_mant_up(void * shared) {

	signed short number = 0;
	nextionRX * temp = (nextionRX*) shared;

	if (temp->lencommand) {
		number = temp->command[1];
		number = number | (temp->command[2] << 8);
		grabador->init_configs["gui"]["tiempo_121mant"]["T121e"] = number;
	} else {
		number = grabador->init_configs["gui"]["tiempo_121mant"]["T121e"];
	}

	return 0;
}

int button_tiempos_desca_121_mant_up(void * shared) {

	signed short number = 0;
	nextionRX * temp = (nextionRX*) shared;

	if (temp->lencommand) {
		number = temp->command[1];
		number = number | (temp->command[2] << 8);
		grabador->init_configs["gui"]["tiempo_121mant"]["T121d"] = number;
	} else {
		number = grabador->init_configs["gui"]["tiempo_121mant"]["T121d"];
	}

	return 0;
}

int button_tiempos_seca_121_mant_up(void * shared) {

	signed short number = 0;
	nextionRX * temp = (nextionRX*) shared;

	if (temp->lencommand) {
		number = temp->command[1];
		number = number | (temp->command[2] << 8);
		grabador->init_configs["gui"]["tiempo_121mant"]["T121s"] = number;
	} else {
		number = grabador->init_configs["gui"]["tiempo_121mant"]["T121s"];
	}

	return 0;
}

int button_tiempos_esteri_134_mant_up(void * shared) {

	signed short number = 0;
	nextionRX * temp = (nextionRX*) shared;

	if (temp->lencommand) {
		number = temp->command[1];
		number = number | (temp->command[2] << 8);
		grabador->init_configs["gui"]["tiempo_134mant"]["T134e"] = number;
	} else {
		number = grabador->init_configs["gui"]["tiempo_134mant"]["T134e"];
	}

	return 0;
}

int button_tiempos_desca_134_mant_up(void * shared) {

	signed short number = 0;
	nextionRX * temp = (nextionRX*) shared;

	if (temp->lencommand) {
		number = temp->command[1];
		number = number | (temp->command[2] << 8);
		grabador->init_configs["gui"]["tiempo_134mant"]["T134d"] = number;
	} else {
		number = grabador->init_configs["gui"]["tiempo_134mant"]["T134d"];
	}

	return 0;
}

int button_tiempos_seca_134_mant_up(void * shared) {

	signed short number = 0;
	nextionRX * temp = (nextionRX*) shared;

	if (temp->lencommand) {
		number = temp->command[1];
		number = number | (temp->command[2] << 8);
		grabador->init_configs["gui"]["tiempo_134mant"]["T134s"] = number;
	} else {
		number = grabador->init_configs["gui"]["tiempo_134mant"]["T134s"];
	}

	return 0;
}

int set_ip_function(void * shared) {

	int i;
	nextionRX * temp = (nextionRX*) shared;
	std::string ip_to_Set;
	char ip_rx[25];
	for (i = 1; i <= (temp->lencommand); i++) {

		ip_rx[i - 1] = temp->command[i];
	}
	printf("ip =%s\n", ip_rx);
	ip_to_Set = ip_rx;
	Ethernet->setIP("eth0", ip_to_Set);
	return 0;
}

int test_printer(void * shared) {
	int i;
	nextionRX * temp = (nextionRX*) shared;

	char mensaje[25];
	for (i = 1; i <= (temp->lencommand); i++) {

		mensaje[i - 1] = temp->command[i];
	}
	printf("impresion de test =%s\n", mensaje);

	if(mensaje[0]=='t'){
		impresora->printF("/Stericlinic/Cycle2Print/cycleTest");
		printf("mandando a imprimir\n");
	}

	return 0;
}
/*--------------------------------------------------------------------------------------*/
/*THREADS DEL SISTEMA
 * rx_uart() --> encargado de la recepcion UART para que el LCD NExtion funcione
 * rtc_sd_and_ethernet_task() --> su funciones son:
 * 								 1) inicializar la pantalla Nextion con los valores iniciales q estan en Json
 * 								 2) Sonido de inicializacion o boot.
 * 								 3) Refrescar la hora y fecha del sistema
 * 								 4) refrescar el estado del cable ethernet.
 * 								 5) refrecar el estado de la impresora.
 * 								 6) Guardar el archivo Json cada 20 segundos.
 *
 * update_events() --->	Esta funcion esta encargada de hacer efectivos los eventos enlazados a cada boton del sistema.
 * 						sin esta funcion los eventos no funcionarian.
 * pages_refresh() --> Verifica en que pagina se esta en el momento para enviar periodicamente datos como
 * 					   el estado de las valvulas, el nivel del tanque, y el estado de la puerta
 * alarm_task() ---> esta encargado de hacer efectivas las alarmas, y verificar el boton de emergencia.
 * 					 si se esta en la pagina 27(alarma) se activara una alarma por medio de sofwtare usando
 * 					 la funcion sound_card->siren();
 * 					 pero si la activacion esta hecha por hardware, se activa la ventana de emergencia automaticamente
 *
 * init_gui_configs() --> NO es un THREAD, pero se usa para enviar los valores iniciales leidos desde JSON
 *                        a la pantalla Nextion, para inicializar los valores del sistema.
 *                        Esta funcion se usa en el arranque del THREAD rtc_sd_and_ethernet_task()
 *
 * */
//EVENTOS O THREADS del sistema
void *rx_uart(void *x_void_ptr) {

	while (1) { //bucle infinito

		LCD->receiver();
		usleep(100000);

	}

	return NULL;

}

/*Explicacion de MACROS
 *
 * */
void init_gui_configs() {

	std::string ip_to_Set = grabador->init_configs["gui"]["ini"]["ipC"];
	//Seteo ip
	Ethernet->setIP("eth0", ip_to_Set);



	//enviar variables de inicializacion a la pantalla
	/*
	 * SEND_SINGLE_STR_NEXTION ==> el MACRO envia directamente un string desde el origen JSON a la pantalla Nextion
	 * Ejemplo:
	 *   SEND_SINGLE_STR_NEXTION(["gui"]["ini"]["ipC"], "ini.ipC.txt=\"%s\"");
	 *   						  |________________|	|__________________|
	 *   							|									|
	 *   							|									---> Texto en el formato q se quiere enviar, debe ser 1 solo argumento
	 *   							---------------------------------------> ubicacion en el archivo JSON
	 *
	 * De la misma manera funciona SEND_SINGLE_INT_NEXTION, y SEND_SINGLE_FLOAT_NEXTION
	 *
	 *
	 *
	 *
	 * */
	SEND_SINGLE_STR_NEXTION(["gui"]["ini"]["ipC"], "ini.ipC.txt=\"%s\"");
	SEND_SINGLE_STR_NEXTION(["gui"]["ini"]["pas"], "ini.pas.txt=\"%s\"");
	SEND_SINGLE_STR_NEXTION(["gui"]["ini"]["temperatura"],
			"ini.temperatura.txt=\"%s\"");
	SEND_SINGLE_STR_NEXTION(["gui"]["ini"]["presion"], "ini.presion.txt=\"%s\"");
	SEND_SINGLE_STR_NEXTION(["gui"]["ini"]["Fecha"], "ini.Fecha.txt=\"%s\"");
	SEND_SINGLE_STR_NEXTION(["gui"]["ini"]["hora"], "ini.hora.txt=\"%s\"");
	SEND_SINGLE_INT_NEXTION(["gui"]["ini"]["autoPrint"], "ini.autoPrint.val=%d");
	SEND_SINGLE_INT_NEXTION(["gui"]["ini"]["puerta"], "ini.puerta.val=%d");
	SEND_SINGLE_INT_NEXTION(["gui"]["ini"]["lpuerta"], "ini.lpuerta.val=%d");
	SEND_SINGLE_INT_NEXTION(["gui"]["ini"]["Sprint"], "ini.Sprint.val=%d");
	SEND_SINGLE_INT_NEXTION(["gui"]["ini"]["elec1.val"], "ini.elec1.val=%d");
	SEND_SINGLE_INT_NEXTION(["gui"]["ini"]["elec2.val"], "ini.elec2.val=%d");
	SEND_SINGLE_INT_NEXTION(["gui"]["ini"]["elec3.val"], "ini.elec3.val=%d");
	SEND_SINGLE_INT_NEXTION(["gui"]["ini"]["elec4.val"], "ini.elec4.val=%d");
	SEND_SINGLE_INT_NEXTION(["gui"]["sp_121mant"]["Spre121"],
			"sp_121mant.Spre121.val=%d");
	SEND_SINGLE_INT_NEXTION(["gui"]["sp_121mant"]["Stemp121"],
			"sp_121mant.Stemp121.val=%d");
	SEND_SINGLE_INT_NEXTION(["gui"]["sp_134mant"]["Spre134"],
			"sp_134mant.Spre134.val=%d");
	SEND_SINGLE_INT_NEXTION(["gui"]["sp_134mant"]["Stemp134"],
			"sp_134mant.Stemp134.val=%d");
	SEND_SINGLE_INT_NEXTION(["gui"]["error_121mant"]["Etemp121"],
			"error_121mant.Etemp121.val=%d");
	SEND_SINGLE_INT_NEXTION(["gui"]["error_121mant"]["Epres121"],
			"error_121mant.Epres121.val=%d");
	SEND_SINGLE_INT_NEXTION(["gui"]["error_134mant"]["Etemp134"],
			"error_134mant.Etemp134.val=%d");
	SEND_SINGLE_INT_NEXTION(["gui"]["error_134mant"]["Epres134"],
			"error_134mant.Epres134.val=%d");

	SEND_SINGLE_INT_NEXTION(["gui"]["tiempo_121mant"]["T121e"],
			"tiempo_121mant.T121e.val=%d");
	SEND_SINGLE_INT_NEXTION(["gui"]["tiempo_121mant"]["T121d"],
			"tiempo_121mant.T121d.val=%d");
	SEND_SINGLE_INT_NEXTION(["gui"]["tiempo_121mant"]["T121s"],
			"tiempo_121mant.T121s.val=%d");

	SEND_SINGLE_INT_NEXTION(["gui"]["tiempo_134mant"]["T134e"],
			"tiempo_134mant.T134e.val=%d");
	SEND_SINGLE_INT_NEXTION(["gui"]["tiempo_134mant"]["T134d"],
			"tiempo_134mant.T134d.val=%d");
	SEND_SINGLE_INT_NEXTION(["gui"]["tiempo_134mant"]["T134s"],
			"tiempo_134mant.T134s.val=%d");

	SEND_SINGLE_INT_NEXTION(["gui"]["llena_agua"]["tanque"],
			"llena_agua.tanque.val=%d");
	SEND_SINGLE_INT_NEXTION(["gui"]["esteriliza"]["timeMea"],
			"esteriliza.timeMea.val=%d");
	SEND_SINGLE_INT_NEXTION(["gui"]["descarga"]["timeMea"],
			"descarga.timeMea.val=%d");
	SEND_SINGLE_INT_NEXTION(["gui"]["secado"]["timeMea"],
			"secado.timeMea.val=%d");
	SEND_SINGLE_INT_NEXTION(["gui"]["finalizando"]["done"],
			"finalizando.finalizando.val=%d");
	SEND_SINGLE_INT_NEXTION(["gui"]["finalizado"]["done"],
			"finalizado.done.val=%d");

}

void *rtc_sd_and_ethernet_task(void *x_void_ptr) {
	char buffer_task_rtc[100];
	string comando;
	char counter = 0;

//	//enviar ir a la pagina principal


	/*
	 * La funcion printF de Nextion funciona exactamente igual q la funcion printf del estandar de C/C++
	 * esta funcion tiene la ventaja q se envia directamente un texto en el formato deseado a la pantalla Nextion
	 * Ejemplo:
	 * 	     LCD->nextionF("%s.%s.val=\"%d\"","ini" ,"puerta" , 1);
	 * 	                     ^  ^        ^      v        v      v
	 * 	                     |	|	     |		|        |      |
	 * 	                     ---|--------|-------		 |		|
	 * 	                    	---------|----------------      |
	 * 	                    			 ------------------------
	 * */
	LCD->nextionF("page ini");
	LCD->nextionF("page ini");
	sound_card->boot();// hacer que suene la cancion de inicializacion
	init_gui_configs();
	//enviar ir a la pagina principal
	LCD->nextionF("page home");


	while (1) { //bucle infinito

		//enviar estados a la pantalla
		real_time_clock->rtc_time_get();

		if (counter % 1 == 0) {
			//printf("-----RTC---------\n\n");
			snprintf(&buffer_task_rtc[0], sizeof(buffer_task_rtc), "%02d:%02d",
					real_time_clock->yymmddhhmmss.hour,
					real_time_clock->yymmddhhmmss.minutes);
			/*
			 * SET_JSON_STR ==> el MACRO envia directamente un string al JSON
			 * Ejemplo:
			 *   SET_JSON_STR(["gui"]["ini"]["hora"], buffer_task_rtc);
             * 				  |________________|	|__________________|
			 *   				|									|
			 *   				|									---> String que se desea guardar en el JSON
			 *   			 	------------------------------------|--> ubicacion en el archivo JSON
			 *														---> en el caso que sea un INT, se usa SET_JSON_INT y en el caso de un FLOAT SET_JSON_FLOAT
			 * De la misma manera funciona SET_JSON_INT, y SET_JSON_FLOAT
			 *
			 *
			 *
			 *
			 * */
			SET_JSON_STR(["gui"]["ini"]["hora"], buffer_task_rtc);
			snprintf(&buffer_task_rtc[0], sizeof(buffer_task_rtc),
					"%02d/%02d/%02d", real_time_clock->yymmddhhmmss.date,
					real_time_clock->yymmddhhmmss.month,
					real_time_clock->yymmddhhmmss.year);
			SET_JSON_STR(["gui"]["ini"]["Fecha"], buffer_task_rtc);
			SEND_SINGLE_STR_NEXTION(["gui"]["ini"]["Fecha"],
					"ini.Fecha.txt=\"%s\"");
			SEND_SINGLE_STR_NEXTION(["gui"]["ini"]["hora"],
					"ini.hora.txt=\"%s\"");

		}

		//printf("-----Ethernet---------\n\n");
		LCD->nextionF("NetSta.pic=%s",
				Ethernet->GetIp("eth0") ? NET_OKAY : NET_MISSING);

		if (Ethernet->GetIp("eth0")) {
			LCD->nextionF("ip.pco=65535");
			LCD->nextionF("ip.txt=\"ip: %s\"", Ethernet->ip.c_str());

			LCD->nextionF("ini.ipC.txt=\"%s\"", Ethernet->ip.c_str());

		} else {
			LCD->nextionF("ip.txt=\"\"", Ethernet->ip.c_str());

		}

		//printf("-----Printer---------\n\n");
		if (counter % 30 == 0) {
			impresora->getStatus();
		}

		//envia el estado de la impresora a la pantalla
		LCD->nextionF("ini.Sprinter.val=%d", impresora->enable ? 1 : 0);
		SET_JSON_INT(["gui"]["ini"]["Sprint"], impresora->enable ? 1 : 0);

		//cada 20 segundos se guarda las configuraciones especiales de grabador
		if (counter % 20 == 0) {
			grabador->save_init_configs();
		}

		counter++;

		usleep(1000000);

	}

	return NULL;

}

void * update_events(void * shared) {

	while (1) {
		LCD->update_events(shared);

		usleep(10000);
	}
	return NULL;
}

void * pages_refresh(void * shared) {
	char buffer_refresh[100];
	char puerta=0,lpuerta=0;

	while (1) {
		if (LCD->current_page == 3) //Mantenimiento
				{
			//elesctrosondas
			SET_JSON_INT(["gui"]["ini"]["elec1.val"], ElectroSondas->get(0));
			LCD->nextionF("ini.elec1.val=%d", ElectroSondas->get(0));
			SET_JSON_INT(["gui"]["ini"]["elec2.val"], ElectroSondas->get(1));
			LCD->nextionF("ini.elec2.val=%d", ElectroSondas->get(1));
			SET_JSON_INT(["gui"]["ini"]["elec3.val"], ElectroSondas->get(2));
			LCD->nextionF("ini.elec3.val=%d", ElectroSondas->get(2));
			SET_JSON_INT(["gui"]["ini"]["elec4.val"], ElectroSondas->get(3));
			LCD->nextionF("ini.elec4.val=%d", ElectroSondas->get(3));

		}

		//estado de la puerta:
		if(Interrup->get_final()!= puerta){// final de carrera
			lpuerta=puerta;// estado anterior de la puerta
			puerta=Interrup->final;
		}
		SET_JSON_INT(["gui"]["ini"]["puerta"], puerta);
		SET_JSON_INT(["gui"]["ini"]["lpuerta"], lpuerta);
		SEND_SINGLE_INT_NEXTION(["gui"]["ini"]["puerta"], "ini.puerta.val=%d");
		SEND_SINGLE_INT_NEXTION(["gui"]["ini"]["lpuerta"], "ini.lpuerta.val=%d");
		//Nivel Tanque
		if (ElectroSondas->get(2)) {
			SET_JSON_INT(["gui"]["llena_agua"]["tanque"], 100);
			SEND_SINGLE_INT_NEXTION(["gui"]["llena_agua"]["tanque"],
					"llena_agua.tanque.val=%d");
		} else if (ElectroSondas->get(1)) {
			SET_JSON_INT(["gui"]["llena_agua"]["tanque"], 50);
			SEND_SINGLE_INT_NEXTION(["gui"]["llena_agua"]["tanque"],
					"llena_agua.tanque.val=%d");
		} else if (ElectroSondas->get(0)) {
			SET_JSON_INT(["gui"]["llena_agua"]["tanque"], 25);
			SEND_SINGLE_INT_NEXTION(["gui"]["llena_agua"]["tanque"],
					"llena_agua.tanque.val=%d");
		} else {
			SET_JSON_INT(["gui"]["llena_agua"]["tanque"], 0);
			SEND_SINGLE_INT_NEXTION(["gui"]["llena_agua"]["tanque"],
					"llena_agua.tanque.val=%d");
		}

		snprintf(&buffer_refresh[0], sizeof(buffer_refresh), "%0.2f",
				sensores_temperatura->readCelsius(0));

		//temperatura global y presiones
		SET_JSON_STR(["gui"]["ini"]["temperatura"], buffer_refresh);
		SEND_SINGLE_STR_NEXTION(["gui"]["ini"]["temperatura"],
				"ini.temperatura.txt=\"%s\"");

		snprintf(&buffer_refresh[0], sizeof(buffer_refresh), "%0.2f",
				sensores_presion->getPSI(0));

		SET_JSON_STR(["gui"]["ini"]["presion"], buffer_refresh);
		SEND_SINGLE_STR_NEXTION(["gui"]["ini"]["presion"],
				"ini.presion.txt=\"%s\"");

		usleep(700000);
	}
	return NULL;
}

void * alarm_task(void * shared) {

	char activated = 0;
	while (1) {

		//alarm task

		//verificar si el boton de alarma esta encendido
		//Enviar comando
		if (Interrup->get_emergencia() && enviar_emergencia == 0) {
			enviar_emergencia = 1;
			printf("Enviando a la pantalla De emergencia\n");

			LCD->nextionF("ini.Emergency.val=1");
			LCD->nextionF("ini.msg.txt=\"Boton de emergencia activado\"");
			LCD->nextionF("ini.msg2.txt=\"Valvula de escape activa\"");
			LCD->nextionF("page alarma_llenado");

		} else {
			if (Interrup->get_emergencia() == 0) {

				if (enviar_emergencia) {
					printf("Enviando a la pantalla De inicio\n");
					LCD->nextionF("ini.Emergency.val=0");

				}
				enviar_emergencia = 0;
			}
		}

		if (LCD->current_page == 27 && enviar_emergencia == 0) {

			sound_card->siren();
			activated = 1;
		} else if (activated) {
			activated = 0;
			sound_card->mute();
		}
		usleep(1000);
	}
	return NULL;
}


/*--------------------------------------------------------------------------------------*/
	/*
	 * Para añadir cada evento tiene la siguiente estructura
	 * {"identifacdor del objeto", &funcion_del_evento,&datos_a_compartir}
	 * Ejemplo 1:
	 * 		Item * valve1_on = new Item { "\x65\x03\x16\x01", &button_val1_on, NULL };
	 *										|    |	 |	 |    	 |
	 *										|	 | 	 |	 |		 |
	 *										|	 |	 |	 | 		 ------------> Funcion a la que se llama cuando se recibe el evento
	 *										|	 |	 |	  ------> Evento down(Tipo de evento q se esta realizando en el caso de boton, up(release) o down(press))
	 *										|	 |	 ------------> ID del objeto dentro de la pagina
	 	 	 	 	 	 	 	 	 	 	|	 |-----> Pagina donde esta el objeto
	 	 	 	 	 	 	 	 	 	 	 ----------> Es el tipo de objeto q se va recibir, en este caso 0x65 es un boton,
	 * 	   		  									    para el caso de paginas seria 0x66, y para caso de datos string 0x70, y 0x71 para datos de un numero entero.
	 *Ejemplo 2: "\x65\x03\x16\xf5"
	 *				|	|	|	|
	 *				|	|	|	-------> indica q se esta recibiendo un evento release(up), deberia ser 0x0, pero para no confundir con
	 *				|	|	|			 EOF(end of line) se pone 0xf5
	 *				|	|	-----------> indica el el id del objeto
	 *				|	---------------> indica la pagina donde esta el objeto
	 *				-------------------> Indica el tipo de objeto q se recibe, sea boton, pagina o dato
	 *		en el caso de de que se quiera recibir una pagina como evento, seria de la siguiente forma
	 *		Ejemplo 1:
	 *			Item * evento_pagina = new Item { "\x66\xf5", &pagina, NULL };
	 *												|	 |    	|		|
	 *												|	 | 		|
	 *												|	 | 		------------> Funcion a la que se llama cuando se recibe el evento
	 *												|	  ------> pagina 0
	 *												------------> Tipo de objeto en este caso pagina
	 *		Ejemplo 2:
	 *			Item * evento_pagina = new Item { "\x66\x01", &pagina, NULL };
	 *												|	 |
	 *												|	  ------> pagina 1
	 *												------------> Tipo de objeto en este caso pagina
	 *			En este caso 0xf5 ==> es 0x0
	 * */
void init_gui() {

	/*--------------------------------------------------------------------------------------*/
	// Botones de mantenimiento para prender y apagar valvulas
	// en el evento(0x01) down la valvula se debe prender
	// en el evento(0xf5) up la valvula se debe prender
	Item * valve1_on = new Item { "\x65\x03\x16\x01", &button_val1_on, NULL };
	Item * valve1_off = new Item { "\x65\x03\x16\xf5", &button_val1_off, NULL };
	Item * valve2_on = new Item { "\x65\x03\x1f\x01", &button_val2_on, NULL };
	Item * valve2_off = new Item { "\x65\x03\x1f\xf5", &button_val2_off, NULL };
	Item * valve3_on = new Item { "\x65\x03\x20\x01", &button_val3_on, NULL };
	Item * valve3_off = new Item { "\x65\x03\x20\xf5", &button_val3_off, NULL };
	/*--------------------------------------------------------------------------------------*/
	//boton de la impresora, para imprimir ultimo registro de datos
	Item * printer = new Item { "\x65\x19\x0d\x01", &print, NULL };
	/*--------------------------------------------------------------------------------------*/
	//botones del menu de mantenimiento para ajuste del Set Point
	//121 C
	Item * sp_121_mant_t_up = new Item { "\x65\x05\x06\xf5",
			&button_sp_121_mant_t, NULL };// ---> Boton de up para aumentar set point de temperatura
	Item * sp_121_mant_t_down = new Item { "\x65\x05\x07\xf5",
			&button_sp_121_mant_t, NULL };// ---> Boton de up para disminuir set point de temperatura

	Item * sp_121_mant_p_up = new Item { "\x65\x05\x08\xf5",
			&button_sp_121_mant_p, NULL };// ---> Boton de up para aumentar set point de presion
	Item * sp_121_mant_p_down = new Item { "\x65\x05\x09\xf5",
			&button_sp_121_mant_p, NULL };// ---> Boton de up para disminuir set point de presion
	//134 C
	Item * sp_134_mant_t_up = new Item { "\x65\x06\x05\xf5",
			&button_sp_134_mant_t, NULL };
	Item * sp_134_mant_t_down = new Item { "\x65\x06\x06\xf5",
			&button_sp_134_mant_t, NULL };

	Item * sp_134_mant_p_up = new Item { "\x65\x06\x07\xf5",
			&button_sp_134_mant_p, NULL };
	Item * sp_134_mant_p_down = new Item { "\x65\x06\x08\xf5",
			&button_sp_134_mant_p, NULL };
	/*--------------------------------------------------------------------------------------*/
	//botones de mantenimiento para el error
	Item * error_121_mant_t_up = new Item { "\x65\x08\x05\xf5",
			&button_error_121_mant_t, NULL };
	Item * error_121_mant_t_down = new Item { "\x65\x08\x06\xf5",
			&button_error_121_mant_t, NULL };

	Item * error_121_mant_p_up = new Item { "\x65\x08\x07\xf5",
			&button_error_121_mant_p, NULL };
	Item * error_121_mant_p_down = new Item { "\x65\x08\x08\xf5",
			&button_error_121_mant_p, NULL };

	Item * error_134_mant_t_up = new Item { "\x65\x09\x05\xf5",
			&button_error_134_mant_t, NULL };
	Item * error_134_mant_t_down = new Item { "\x65\x09\x06\xf5",
			&button_error_134_mant_t, NULL };

	Item * error_134_mant_p_up = new Item { "\x65\x09\x07\xf5",
			&button_error_134_mant_p, NULL };
	Item * error_134_mant_p_down = new Item { "\x65\x09\x08\xf5",
			&button_error_134_mant_p, NULL };

	/*--------------------------------------------------------------------------------------*/
	// evento del boton de configuracion de cambio de IP ETHERNET
	Item * network = new Item { "\x65\x1d\x19\xf5", &set_ip_function, NULL };

	// evento del boton de configuracion de test de impresion
	Item * printerTest = new Item { "\x65\x1c\x11\xf5", &test_printer, NULL };

	/*--------------------------------------------------------------------------------------*/

	//botones de mantenimiento para ajuste de tiempos para cada ciclo
	Item * tiempos_esteri_121_mant_up = new Item { "\x65\x0b\x0a\xf5",
			&button_tiempos_esteri_121_mant_up, NULL };
	Item * tiempos_esteri_121_mant_down = new Item { "\x65\x0b\x0b\xf5",
			&button_tiempos_esteri_121_mant_up, NULL };
	Item * tiempos_desca_121_mant_up = new Item { "\x65\x0b\x0c\xf5",
			&button_tiempos_desca_121_mant_up, NULL };
	Item * tiempos_desca_121_mant_down = new Item { "\x65\x0b\x0d\xf5",
			&button_tiempos_desca_121_mant_up, NULL };
	Item * tiempos_seca_121_mant_up = new Item { "\x65\x0b\x0e\xf5",
			&button_tiempos_seca_121_mant_up, NULL };
	Item * tiempos_seca_121_mant_down = new Item { "\x65\x0b\x0f\xf5",
			&button_tiempos_seca_121_mant_up, NULL };

	Item * tiempos_esteri_134_mant_up = new Item { "\x65\x0c\x0a\xf5",
			&button_tiempos_esteri_134_mant_up, NULL };
	Item * tiempos_esteri_134_mant_down = new Item { "\x65\x0c\x0b\xf5",
			&button_tiempos_esteri_134_mant_up, NULL };
	Item * tiempos_desca_134_mant_up = new Item { "\x65\x0c\x0c\xf5",
			&button_tiempos_desca_134_mant_up, NULL };
	Item * tiempos_desca_134_mant_down = new Item { "\x65\x0c\x0d\xf5",
			&button_tiempos_desca_134_mant_up, NULL };
	Item * tiempos_seca_134_mant_up = new Item { "\x65\x0c\x0e\xf5",
			&button_tiempos_seca_134_mant_up, NULL };
	Item * tiempos_seca_134_mant_down = new Item { "\x65\x0c\x0f\xf5",
			&button_tiempos_seca_134_mant_up, NULL };

	/*--------------------------------------------------------------------------------------*/
	// Añadir los eventos a la tabla de Eventos, cada boton debe se registrado como un evento
	Events_table.insertItem(valve1_on);
	Events_table.insertItem(valve1_off);
	Events_table.insertItem(valve2_on);
	Events_table.insertItem(valve2_off);
	Events_table.insertItem(valve3_on);
	Events_table.insertItem(valve3_off);
	Events_table.insertItem(printer);
	Events_table.insertItem(sp_121_mant_t_up);
	Events_table.insertItem(sp_121_mant_t_down);
	Events_table.insertItem(sp_121_mant_p_up);
	Events_table.insertItem(sp_121_mant_p_down);
	Events_table.insertItem(sp_134_mant_t_up);
	Events_table.insertItem(sp_134_mant_t_down);
	Events_table.insertItem(sp_134_mant_p_up);
	Events_table.insertItem(sp_134_mant_p_down);
	Events_table.insertItem(error_121_mant_t_up);
	Events_table.insertItem(error_121_mant_t_down);
	Events_table.insertItem(error_121_mant_p_up);
	Events_table.insertItem(error_121_mant_p_down);
	Events_table.insertItem(error_134_mant_t_up);
	Events_table.insertItem(error_134_mant_t_down);
	Events_table.insertItem(error_134_mant_p_up);
	Events_table.insertItem(error_134_mant_p_down);
	Events_table.insertItem(tiempos_esteri_121_mant_up);
	Events_table.insertItem(tiempos_esteri_121_mant_down);
	Events_table.insertItem(tiempos_desca_121_mant_up);
	Events_table.insertItem(tiempos_desca_121_mant_down);
	Events_table.insertItem(tiempos_seca_121_mant_up);
	Events_table.insertItem(tiempos_seca_121_mant_down);
	Events_table.insertItem(tiempos_esteri_134_mant_up);
	Events_table.insertItem(tiempos_esteri_134_mant_down);
	Events_table.insertItem(tiempos_desca_134_mant_up);
	Events_table.insertItem(tiempos_desca_134_mant_down);
	Events_table.insertItem(tiempos_seca_134_mant_up);
	Events_table.insertItem(tiempos_seca_134_mant_down);
	Events_table.insertItem(network);
	Events_table.insertItem(printerTest);
	/*--------------------------------------------------------------------------------------*/
	/*Variables para manejo del id de cada uno de los THREAD o task q se van a correr para manejar el
	 * sistema
	 * */
	pthread_t rx_uart_thread, refresh_events, rtc_sd_and_ethernet,
			alarm_task_stk, pages_stk;

	//task para recepcion UART de la pantall LCD
	pthread_create(&rx_uart_thread, NULL, rx_uart, NULL);
	/*				|						|      |
	 *				|						|		---> Datos a compartir con el Thread
	 *				|						-----------> funcion del thread
	 *				-----------------------------------> Variable unica del thread
	 *										*/

	//task para refrescar eventos de recepcion
	pthread_create(&refresh_events, NULL, update_events, NULL);

	//task para actualizar variables del sistema nextion
	pthread_create(&rtc_sd_and_ethernet, NULL, rtc_sd_and_ethernet_task, NULL);

	//task para alarma
	pthread_create(&alarm_task_stk, NULL, alarm_task, NULL);

	//task para refrescado de paginas
	pthread_create(&pages_stk, NULL, pages_refresh, NULL);

}
