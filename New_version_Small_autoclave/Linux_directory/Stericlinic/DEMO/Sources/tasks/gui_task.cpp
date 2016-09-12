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

#include "../Nextion/Nextion.hpp"
#include "../Interruptores/interruptores.h"
#include "../rtc/rtc.h"
#include "../Network/Network.h"
#include "../Printer/printer.h"
#include "../DataLog/DataLogger.h"

extern HashTable Events_table;

extern rtc * real_time_clock;
extern Network * Ethernet;
extern printer * impresora;
extern DataLogger * grabador;

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
	char buffer[100];
	snprintf(buffer, sizeof(buffer), "pass.txt=pass.txt+\"%d\"",
			temp->command[1]);
	string comando = buffer;
	test_send(comando);

	return 0;
}

int print(void * shared) {
	char buffer[100];

	snprintf(buffer, sizeof(buffer), "cycle%d",
			grabador->read_byte("/Stericlinic/Init_config/LastCycle"));
	printf("mandando a imprimir\n");
	impresora->print("/Stericlinic/Cycle2Print/cyclep1");

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
			char buffer[100];
			snprintf(buffer, sizeof(buffer), "page alarma_llenado");
			string comando = buffer;
			test_send(comando);

		} else {
			if (Interrup->get_emergencia() == 0) {

				if (enviar_emergencia) {
					printf("Enviando a la pantalla De inicio\n");
					char buffer[100];
					snprintf(buffer, sizeof(buffer), "page ini");
					string comando = buffer;
					test_send(comando);
				}
				enviar_emergencia = 0;
			}
		}
		receiver();
		usleep(100000);

	}

	return NULL;

}

void *rtc_sd_and_ethernet_task(void *x_void_ptr) {
	string comando;
	char buffer_task_rtc[550];
	char counter = 0;

	//enviar ir a la pagina principal
	snprintf(buffer_task_rtc, sizeof(buffer_task_rtc), "page ini");
	comando = buffer_task_rtc;
	test_send(comando);

	usleep(7000000);
	//enviar ir a la pagina principal
	snprintf(buffer_task_rtc, sizeof(buffer_task_rtc), "page home");
	comando = buffer_task_rtc;
	test_send(comando);

	real_time_clock->rtc_time_get();
	snprintf(&buffer_task_rtc[0], sizeof(buffer_task_rtc),
			"hora.txt=\"%02d:%02d\"", real_time_clock->yymmddhhmmss.hour,
			real_time_clock->yymmddhhmmss.minutes);
	comando = buffer_task_rtc;
	test_send(comando);

	snprintf(&buffer_task_rtc[0], sizeof(buffer_task_rtc),
			"Fecha.txt=\"%02d/%02d/2%03d\"", real_time_clock->yymmddhhmmss.date,
			real_time_clock->yymmddhhmmss.month,
			real_time_clock->yymmddhhmmss.year);
	comando = buffer_task_rtc;
	test_send(comando);

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

		if (counter % 45 == 0) {
			//printf("-----RTC---------\n\n");

			snprintf(&buffer_task_rtc[0], sizeof(buffer_task_rtc),
					"hora.txt=\"%02d:%02d\"",
					real_time_clock->yymmddhhmmss.hour,
					real_time_clock->yymmddhhmmss.minutes);
			comando = buffer_task_rtc;
			test_send(comando);

			snprintf(&buffer_task_rtc[0], sizeof(buffer_task_rtc),
					"Fecha.txt=\"%02d/%02d/2%03d\"",
					real_time_clock->yymmddhhmmss.date,
					real_time_clock->yymmddhhmmss.month,
					real_time_clock->yymmddhhmmss.year);
			comando = buffer_task_rtc;
			test_send(comando);

		}

		//printf("-----Ethernet---------\n\n");
		snprintf(&buffer_task_rtc[0], sizeof(buffer_task_rtc), "NetSta.pic=%s",
				Ethernet->GetIp("eth0") ? NET_OKAY : NET_MISSING);
		comando = buffer_task_rtc;
		test_send(comando);

		if (Ethernet->GetIp("eth0")) {
				snprintf(&buffer_task_rtc[0], sizeof(buffer_task_rtc),
					"ip.pco=65535");
			comando = buffer_task_rtc;
			test_send(comando);
			snprintf(&buffer_task_rtc[0], sizeof(buffer_task_rtc),
					"ip.txt=\"ip: %s\"", Ethernet->ip.c_str());
			comando = buffer_task_rtc;
			test_send(comando);
		} else {
			snprintf(&buffer_task_rtc[0], sizeof(buffer_task_rtc),
					"ip.txt=\"\"", Ethernet->ip.c_str());
			comando = buffer_task_rtc;
			test_send(comando);

		}

		//printf("-----Printer---------\n\n");
		if (counter % 30 == 0) {
			impresora->getStatus();
		}
		snprintf(&buffer_task_rtc[0], sizeof(buffer_task_rtc), "PrinSta.pic=%s",
				impresora->enable ? NET_OKAY : NET_MISSING);
		comando = buffer_task_rtc;
		test_send(comando);

		counter++;

		usleep(1000000);

	}

	return NULL;

}

void init_gui() {
	//tipo, pagina, id, 0x00
	Item * boton1 = new Item { "\x65\x01\x02\x00", &test, NULL };
	Item * boton2 = new Item { "\x65\x0e\x0c\x00", &test2, NULL };
	Item * boton3 = new Item { "\x65\x19\x0d\x00", &print, NULL };
	Item * boton_numerico1 = new Item { "\x65\x02\x04\x00", &teclado, NULL };
	Item * boton_numerico2 = new Item { "\x65\x02\x05\x00", &teclado, NULL };
	Item * boton_numerico3 = new Item { "\x65\x02\x06\x00", &teclado, NULL };
	Item * boton_numerico4 = new Item { "\x65\x02\x07\x00", &teclado, NULL };
	Item * boton_numerico5 = new Item { "\x65\x02\x08\x00", &teclado, NULL };
	Item * boton_numerico6 = new Item { "\x65\x02\x08\x00", &teclado, NULL };
	Item * boton_numerico7 = new Item { "\x65\x02\x0a\x00", &teclado, NULL };
	Item * boton_numerico8 = new Item { "\x65\x02\x0b\x00", &teclado, NULL };
	Item * boton_numerico9 = new Item { "\x65\x02\x0c\x00", &teclado, NULL };

	// Add 3 Items to Hash Table.
	Events_table.insertItem(boton1);
	Events_table.insertItem(boton2);
	Events_table.insertItem(boton3);
	Events_table.insertItem(boton_numerico1);
	Events_table.insertItem(boton_numerico2);
	Events_table.insertItem(boton_numerico3);
	Events_table.insertItem(boton_numerico4);
	Events_table.insertItem(boton_numerico5);
	Events_table.insertItem(boton_numerico6);
	Events_table.insertItem(boton_numerico7);
	Events_table.insertItem(boton_numerico8);
	Events_table.insertItem(boton_numerico9);

	/* this variable is our reference to the second thread */
	pthread_t rx_uart_thread, refresh_events, rtc_sd_and_ethernet;

	//task para recepcion UART de la pantall LCD
	pthread_create(&rx_uart_thread, NULL, rx_uart, NULL);

	//task para refrescar eventos de recepcion
	pthread_create(&refresh_events, NULL, update_events, NULL);

	//task para refrescar eventos de recepcion
	pthread_create(&rtc_sd_and_ethernet, NULL, rtc_sd_and_ethernet_task, NULL);

}
