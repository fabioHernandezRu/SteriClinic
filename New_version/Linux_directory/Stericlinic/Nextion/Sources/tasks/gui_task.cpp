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


extern HashTable Events_table;

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
	snprintf(buffer,sizeof(buffer),"b10.txt=b10.txt+\"%d\"",temp->command[1]);
	string comando=buffer;
	test_send(comando);

	return 0;
}

int print(void * shared) {


	printf("mandando a imprimir\n");


	return 0;
}



int enviar_emergencia=0;
void *rx_uart(void *x_void_ptr) {

	while (1) { //bucle infinito


		receiver();
		usleep(100000);

	}

	return NULL;

}

void init_gui() {
								//tipo, pagina, id, 0x00
	Item * boton1 = new Item { "\x65\x01\x02\x00", &test, NULL };
	Item * boton2 = new Item { "\x65\x0e\x0c\x00", &test2, NULL };
	Item * boton3 = new Item { "\x65\x19\x0d\x00", &print, NULL };
	Item * boton_numerico1 = new Item { "\x65\x02\x0c\x00", &teclado, NULL };
	Item * boton_numerico2 = new Item { "\x65\x02\x0d\x00", &teclado, NULL };
	Item * boton_numerico3 = new Item { "\x65\x02\x0e\x00", &teclado, NULL };
	Item * boton_numerico4 = new Item { "\x65\x02\x0f\x00", &teclado, NULL };
	Item * boton_numerico5 = new Item { "\x65\x02\x10\x00", &teclado, NULL };
	Item * boton_numerico6 = new Item { "\x65\x02\x11\x00", &teclado, NULL };
	Item * boton_numerico7 = new Item { "\x65\x02\x12\x00", &teclado, NULL };
	Item * boton_numerico8 = new Item { "\x65\x02\x13\x00", &teclado, NULL };
	Item * boton_numerico9 = new Item { "\x65\x02\x14\x00", &teclado, NULL };

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
	pthread_t rx_uart_thread, refresh_events;

	//task para recepcion UART de la pantall LCD
	pthread_create(&rx_uart_thread, NULL, rx_uart, NULL);

	//task para refrescar eventos de recepcion
	pthread_create(&refresh_events, NULL, update_events, NULL);

}
