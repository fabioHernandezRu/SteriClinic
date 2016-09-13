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

#include <pthread.h>
#include "../Nextion/Nextion.h"
#include "../Interruptores/interruptores.h"
#include "../rtc/rtc.h"
#include "../Valves/valves.h"
#include "../Network/Network.h"
#include "../Printer/printer.h"
#include "../DataLog/DataLogger.h"
#include "../audio/audio.h"
#include "../ADC/adcltc2308.h"
#include "../MAX6675/max6675.h"

extern HashTable Events_table;

extern rtc * real_time_clock;
extern Network * Ethernet;
extern printer * impresora;
extern DataLogger * grabador;
extern Nextion * LCD;
extern audio * sound_card;
extern adc_ltc2308 * sensores_presion;
extern max6675 * sensores_temperatura;
extern valves * Valvulas;
extern interruptores * ElectroSondas;

string send_string;
int send_int;
float send_float;

#define SEND_SINGLE_STR_NEXTION(input,input2) send_string=grabador->init_configs input; \
LCD->nextionF(input2,send_string.c_str())

#define SEND_SINGLE_INT_NEXTION(input,input2) send_int=grabador->init_configs input; \
LCD->nextionF(input2,send_int)

#define SEND_SINGLE_FLOAT_NEXTION(input,input2) send_float=grabador->init_configs input; \
LCD->nextionF(input2,send_float)

#define SET_JSON_STR(input,input2) send_string=input2; \
grabador->init_configs input=send_string

#define SET_JSON_INT(input,input2) send_int=input2; \
grabador->init_configs input=send_int

#define SET_JSON_FLOAT(input,input2) send_float=input2; \
grabador->init_configs input=send_float

int print(void * shared) {

	int last_cycle = grabador->init_configs["general"]["last_cycle"];

	impresora->printF("/Stericlinic/Cycle2Print/cyclep%d", last_cycle);
	printf("mandando a imprimir\n");

	return 0;
}

int pagina(void * shared) {
	puts("evento pagina");
	return 0;
}

extern interruptores * Interrup;
int enviar_emergencia = 0;
void *rx_uart(void *x_void_ptr) {

	while (1) { //bucle infinito

		LCD->receiver();
		usleep(100000);

	}

	return NULL;

}

void init_gui_configs() {

	std::string ip_to_Set = grabador->init_configs["gui"]["ini"]["ipC"];
	//Seteo ip
	Ethernet->setIP("eth0", ip_to_Set);

	//enviar variables de inicializacion a la pantalla
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
	LCD->nextionF("page ini");
	init_gui_configs();
	sound_card->boot();
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
			LCD->nextionF("ini.msg.txt=\"Valvula de escape activa\"");
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

int gui_buttons(void * shared) {

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

	int number = 0;
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

	int number = 0;
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

	int number = 0;
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

	int number = 0;
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

	int number = 0;
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

	int number = 0;
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

	int number = 0;
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

	int number = 0;
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

	int number = 0;
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

	int number = 0;
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

	int number = 0;
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

	int number = 0;
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

	int number = 0;
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

	int number = 0;
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

void init_gui() {
	//tipo, pagina, id, tipo de evento, fin de linea
	// if 0 replace with xf5
	Item * valve1_on = new Item { "\x65\x03\x16\x01", &button_val1_on, NULL };
	Item * valve1_off = new Item { "\x65\x03\x16\xf5", &button_val1_off, NULL };
	Item * valve2_on = new Item { "\x65\x03\x1f\x01", &button_val2_on, NULL };
	Item * valve2_off = new Item { "\x65\x03\x1f\xf5", &button_val2_off, NULL };
	Item * valve3_on = new Item { "\x65\x03\x20\x01", &button_val3_on, NULL };
	Item * valve3_off = new Item { "\x65\x03\x20\xf5", &button_val3_off, NULL };
	Item * printer = new Item { "\x65\x19\x0d\x01", &print, NULL };

	Item * sp_121_mant_t_up = new Item { "\x65\x05\x06\xf5",
			&button_sp_121_mant_t, NULL };
	Item * sp_121_mant_t_down = new Item { "\x65\x05\x07\xf5",
			&button_sp_121_mant_t, NULL };

	Item * sp_121_mant_p_up = new Item { "\x65\x05\x08\xf5",
			&button_sp_121_mant_p, NULL };
	Item * sp_121_mant_p_down = new Item { "\x65\x05\x09\xf5",
			&button_sp_121_mant_p, NULL };

	Item * sp_134_mant_t_up = new Item { "\x65\x06\x05\xf5",
			&button_sp_134_mant_t, NULL };
	Item * sp_134_mant_t_down = new Item { "\x65\x06\x06\xf5",
			&button_sp_134_mant_t, NULL };

	Item * sp_134_mant_p_up = new Item { "\x65\x06\x07\xf5",
			&button_sp_134_mant_p, NULL };
	Item * sp_134_mant_p_down = new Item { "\x65\x06\x08\xf5",
			&button_sp_134_mant_p, NULL };

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
//	Item * evento_pagina = new Item { "\x66\xf5", &pagina, NULL };

	// Add 3 Items to Hash Table.
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

	/* this variable is our reference to the second thread */
	pthread_t rx_uart_thread, refresh_events, rtc_sd_and_ethernet,
			alarm_task_stk, pages_stk;

	//task para recepcion UART de la pantall LCD
	pthread_create(&rx_uart_thread, NULL, rx_uart, NULL);

	//task para refrescar eventos de recepcion
	pthread_create(&refresh_events, NULL, update_events, NULL);

	//task para refrescar eventos de recepcion
	pthread_create(&rtc_sd_and_ethernet, NULL, rtc_sd_and_ethernet_task, NULL);

	//task para alarma
	pthread_create(&alarm_task_stk, NULL, alarm_task, NULL);

	//task para refrescado de paginas
	pthread_create(&pages_stk, NULL, pages_refresh, NULL);

}
