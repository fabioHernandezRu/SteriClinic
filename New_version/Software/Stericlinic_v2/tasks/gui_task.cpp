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
#include "../Network/Network.h"
#include "../Printer/printer.h"
#include "../DataLog/DataLogger.h"
#include "../audio/audio.h"

extern HashTable Events_table;

extern rtc * real_time_clock;
extern Network * Ethernet;
extern printer * impresora;
extern DataLogger * grabador;
extern Nextion * LCD;
extern audio * sound_card;

int test(void *shared) {

	printf("evento shared \n");

	return 0;
}

int test2(void *shared) {

	printf("Hola Sexy");

	return 0;
}

int teclado(void *shared) {
	int i;
	nextionRX * temp = (nextionRX*) shared;
	for (i = 0; i <= temp->lencommand; i++) {
		printf("%d,", temp->command[i]);
	}
	printf("\n");

	//Enviar comando

	LCD->nextionF("pass.txt=pass.txt+\"%d\"", temp->command[1]);

	return 0;
}

int fabio_function(void *shared) {
	int i;
	nextionRX * temp = (nextionRX*) shared;
	for (i = 0; i <= temp->lencommand; i++) {
		printf("%d,", temp->command[i]);
	}
	printf("\n");

	return 0;
}

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

		//verificar si el boton de alarma esta encendido
		//Enviar comando
		if (Interrup->get_emergencia() && enviar_emergencia == 0) {
			enviar_emergencia = 1;
			printf("Enviando a la pantalla De emergencia\n");

			LCD->nextionF("page alarma_llenado");

		} else {
			if (Interrup->get_emergencia() == 0) {

				if (enviar_emergencia) {
					printf("Enviando a la pantalla De inicio\n");
					LCD->nextionF("page ini");

				}
				enviar_emergencia = 0;
			}
		}
		LCD->receiver();
		usleep(100000);

	}

	return NULL;

}

void init_gui_configs() {

	std::string ip_to_Set = grabador->init_configs["gui"]["ini"]["ipC"];
	//Seteo ip
	Ethernet->setIP("eth0", ip_to_Set);

}

void *rtc_sd_and_ethernet_task(void *x_void_ptr) {
	string comando;
	char counter = 0;

//	//enviar ir a la pagina principal
	LCD->nextionF("page ini");
	sound_card->boot();
	usleep(7000000);
	//enviar ir a la pagina principal
	LCD->nextionF("page home");

	/*
	 real_time_clock->rtc_time_get();
	 snprintf(&buffer_task_rtc[0], sizeof(buffer_task_rtc),
	 "ini.hora.txt=\"%02d:%02d\"", real_time_clock->yymmddhhmmss.hour,
	 real_time_clock->yymmddhhmmss.minutes);
	 comando = buffer_task_rtc;
	 test_send(comando);

	 snprintf(&buffer_task_rtc[0], sizeof(buffer_task_rtc),
	 "ini.hora.txt=\"%02d/%02d/2%03d\"", real_time_clock->yymmddhhmmss.date,
	 real_time_clock->yymmddhhmmss.month,
	 real_time_clock->yymmddhhmmss.year);
	 comando = buffer_task_rtc;
	 test_send(comando);
	 */

	/*
	 char cyclo = grabador->read_byte("/Stericlinic/Init_config/current_cycle");
	 if (grabador->CheckIfSystemWasShutAbruted()) {
	 printf("El sistema fue apagado abrutamente\n");
	 snprintf(&buffer_task_rtc[0], sizeof(buffer_task_rtc),
	 "page alarma_llenado");
	 comando = buffer_task_rtc;
	 test_send(comando);
	 snprintf(&buffer_task_rtc[0], sizeof(buffer_task_rtc),
	 "t2.txt=\"El Sistema fue Apagado\"");
	 comando = buffer_task_rtc;
	 test_send(comando);
	 snprintf(&buffer_task_rtc[0], sizeof(buffer_task_rtc),
	 "t0.txt=\"Abrutamente en el Cyclo\"");
	 comando = buffer_task_rtc;
	 test_send(comando);
	 snprintf(&buffer_task_rtc[0], sizeof(buffer_task_rtc),
	 "t1.txt=\"  %c \"", cyclo);
	 comando = buffer_task_rtc;
	 test_send(comando);
	 while (1) {

	 usleep(1000000);
	 }

	 }*/

	while (1) { //bucle infinito

		//enviar estados a la pantalla
		real_time_clock->rtc_time_get();

		if (counter % 1 == 0) {
			//printf("-----RTC---------\n\n");
			/*
			 snprintf(&buffer_task_rtc[0], sizeof(buffer_task_rtc),
			 "ini.hora.txt=\"%02d:%02d\"",
			 real_time_clock->yymmddhhmmss.hour,
			 real_time_clock->yymmddhhmmss.minutes);
			 comando = buffer_task_rtc;
			 test_send(comando);

			 snprintf(&buffer_task_rtc[0], sizeof(buffer_task_rtc),
			 "ini.Fecha.txt=\"%02d/%02d/2%03d\"",
			 real_time_clock->yymmddhhmmss.date,
			 real_time_clock->yymmddhhmmss.month,
			 real_time_clock->yymmddhhmmss.year);
			 comando = buffer_task_rtc;
			 test_send(comando);
			 */

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
		LCD->nextionF("PrinSta.pic=%s",
				impresora->enable ? NET_OKAY : NET_MISSING);

		counter++;

		usleep(1000000);

	}

	return NULL;

}

void * update_events(void * shared) {

	while(1){
		LCD->update_events(shared);
		usleep(10000);
	}
	return NULL;
}

void init_gui() {
	//tipo, pagina, id, tipo de evento, fin de linea
	// if 0 replace with xf5
	Item * boton1 = new Item { "\x65\x01\x02\xf5", &test, NULL };
	Item * boton2 = new Item { "\x65\x0e\x0c\xf5", &test2, NULL };
	Item * boton3 = new Item { "\x65\x19\x0d\xf5", &print, NULL };
	Item * boton_numerico1 = new Item { "\x65\x01\x02\x01", &teclado, NULL };
	Item * evento_pagina = new Item { "\x66\xf5", &pagina, NULL };

	// Add 3 Items to Hash Table.
	Events_table.insertItem(evento_pagina);
	Events_table.insertItem(boton1);
	Events_table.insertItem(boton2);
	Events_table.insertItem(boton3);
	Events_table.insertItem(boton_numerico1);

	/* this variable is our reference to the second thread */
	pthread_t rx_uart_thread, refresh_events, rtc_sd_and_ethernet;

	//task para recepcion UART de la pantall LCD
	pthread_create(&rx_uart_thread, NULL, rx_uart, NULL);

	//task para refrescar eventos de recepcion
	pthread_create(&refresh_events, NULL, update_events, NULL);

	//task para refrescar eventos de recepcion
	pthread_create(&rtc_sd_and_ethernet, NULL, rtc_sd_and_ethernet_task, NULL);

}
