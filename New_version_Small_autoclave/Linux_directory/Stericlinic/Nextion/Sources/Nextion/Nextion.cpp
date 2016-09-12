/*
 * Nextion.cpp
 *
 *  Created on: Aug 18, 2016
 *      Author: Holguer
 */

#include "Nextion.hpp"

extern "C" {
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/mman.h>
#include "hps.h"
#include <pthread.h>

#include "../uart_fpga/uart.h"
}

nextionRX NextionRX[NEXTION_LEN + 1];

unsigned int nextion_tail = 0;
unsigned int nextion_head = 0;

// Create a Hash Table of 250 Linked List elements.
HashTable Events_table(250);

unsigned char uart_rx[4000];

char getNextionCmd_available() {
	if (nextion_head == nextion_tail) {
		return -1;
	}
	return 1;
}
char getNextionCmd() {
	char ret;
	if (nextion_head == nextion_tail) {
		return -1;
	} else {
		ret = nextion_head;
		nextion_head++;
		if (nextion_head >= NEXTION_LEN) {
			nextion_head = 0;
		}
		return ret;
	}
}

void test_send(string comando){

	sendNextioncmd(comando);

}

void receiver() {
	unsigned char cByteRxed;
	int tail_uart = 0;
	int _i = 0;

	while (!uart_queue()) {

		cByteRxed = uart_read();

		uart_rx[tail_uart] = cByteRxed;
		//printf("%02x,",uart_rx[tail_uart]);
		if (tail_uart > 2) {

			if (uart_rx[tail_uart] == 0xff && uart_rx[tail_uart - 1] == 0xff
					&& uart_rx[tail_uart - 2] == 0xff) {
				for (_i = 0; _i <= tail_uart; _i++) {
					NextionRX[nextion_tail].command[_i] = uart_rx[_i];
				}

				NextionRX[nextion_tail].lencommand = tail_uart - 3;

				nextion_tail++;
				if (nextion_tail >= NEXTION_LEN) {
					nextion_tail = 0;
				}
				tail_uart = 2048;
			}

		}
		tail_uart++;
		if (tail_uart >= 2048) {
			tail_uart = 0;
		}

	}

}

void sendNextioncmd(string cmd) {
	uart_tx_stream((unsigned char*)cmd.c_str(),cmd.length());
	uart_tx('\xff');
	uart_tx('\xff');
	uart_tx('\xff');
//	xSerialPutChar(serCOM1, 'ÿ', 0);
//	xSerialPutChar(serCOM1, 'ÿ', 0);
//	xSerialPutChar(serCOM1, 'ÿ', 0);
//

}

void print_receiver(unsigned char * cmd, unsigned char len) {
	int i;
	unsigned char data[len];
	for (i = 0; i <= len; i++) {
		data[i] = cmd[i];
	}
	for (i = 0; i <= len; i++) {
		printf("%02x,", data[i]);
	}
	printf("\n");
	//nextion_debug(data, len);

}

void nextion_debug(unsigned char * cmd, unsigned char len) {
	int i;
	switch (cmd[0]) {

	case 0x00:
		printf("Invalid instruction \n");
		break;
	case 0x01:
		printf("Succeessful execution of instruction \n");
		break;
	case 0x03:
		printf("Page ID invalid\n");
		break;
	case 0x04:
		printf("Picture ID invalid \n");
		break;
	case 0x05:
		printf("Font ID invalid\n");
		break;
	case 0x11:
		printf("Baud rate setting invalid\n");
		break;
	case 0x12:
		printf("Curve control ID number or channel number is invalid\n");
		break;
	case 0x1A:
		printf("Variable name invalid\n");
		break;
	case 0x1B:
		printf("Variable operation invalid\n");
		break;
	case 0x1C:
		printf("Failed to assign\n");
		break;
	case 0x1D:
		printf("Operate PERFROM failed\n");
		break;
	case 0x1E:
		printf("Parameter quantity invalid\n");
		break;
	case 0x1F:
		printf("IO operate failed\n");
		break;
	case 0x65:
		printf("Touch oprimido en page: %d Componente: %d event: \n", cmd[1],
				cmd[2], cmd[3]);
		break;
	case 0x66:
		printf("page now: %d\n", cmd[1]);
		break;

	case 0x67:
		printf(
				"Touch coordinate X High %d coordinate X Low %d coordinate Y high %d coordinate Y low %d touch event %d\n",
				cmd[1], cmd[2], cmd[3], cmd[4], cmd[5]);
		break;
	}

}



void * update_events(void * shared) {

	char cmnd_number;
	if (getNextionCmd_available()) { // si en el fifo hay datos
		cmnd_number = getNextionCmd(); // toma el primer comando

		while (cmnd_number >= 0) { // mientras q el fifo este lleno

			switch (NextionRX[cmnd_number].command[0]) {

			case 0x65: // en el caso que sea un boton
				printf("buscado...boton %x %x %x %x\n",
						NextionRX[cmnd_number].command[0],
						NextionRX[cmnd_number].command[1],
						NextionRX[cmnd_number].command[2],
						NextionRX[cmnd_number].command[3]);
				//busca el la lista eventos
				Item * result =
						Events_table.getItemByKey(
								std::string(
										(const char*) &NextionRX[cmnd_number].command[0]));

				if (result != NULL) { // existe el evento
					//printf("Evento %x %x %x\n",NextionRX[cmnd_number].command[0],NextionRX[cmnd_number].command[1],NextionRX[cmnd_number].command[2]);
					usleep(10000);
					++cmnd_number;
					cmnd_number %= NEXTION_LEN;
					result->_event((void*) &NextionRX[cmnd_number].command);
				} else {						 // no existe el evento
					//  	printf("no encontrado\n");
				}
				break;
			}

			cmnd_number = getNextionCmd();
		}
	}



	usleep(50000);

}

/*
 void print_key(alt_u8 contador) {
 char data[20];
 switch (contador) {
 case 0:
 sprintf(data, "t0.txt=\"\"");
 sendNextioncmd(&data[0], strlen(data));
 break;
 case 1:
 sprintf(data, "t0.txt=\"X\"");
 sendNextioncmd(&data[0], strlen(data));
 break;
 case 2:
 sprintf(data, "t0.txt=\"X X\"");
 sendNextioncmd(&data[0], strlen(data));
 break;
 case 3:
 sprintf(data, "t0.txt=\"X X X\"");
 sendNextioncmd(&data[0], strlen(data));
 break;
 case 4:
 sprintf(data, "t0.txt=\"X X X X\"");
 sendNextioncmd(&data[0], strlen(data));
 break;
 case 5:
 sprintf(data, "t0.txt=\"X X X X X\"");
 sendNextioncmd(&data[0], strlen(data));
 break;
 case 6:
 sprintf(data, "t0.txt=\"X X X X X X\"");
 sendNextioncmd(&data[0], strlen(data));
 break;
 case 7:
 sprintf(data, "t0.txt=\"X X X X X X X\"");
 sendNextioncmd(&data[0], strlen(data));
 break;
 }

 }*/
/*
 void key_mant() {

 char clave_comp[7];
 alt_u8 contador = 0;
 alt_u8 flag = 0;
 char *cmd; // puntero encargado de recibir los datos
 int clave;
 char data[20];
 ini: memset(&clave_comp, 0, 7);
 while (contador < 7) {
 cmd = receiver();
 if (cmd[0] == 0x65) {
 switch (cmd[2]) {
 case 1:
 clave_comp[contador] = '1';
 printf("\n%s", clave_comp);
 contador++;
 print_key(contador);
 break;
 case 2:
 clave_comp[contador] = '2';
 printf("\n%s", clave_comp);
 contador++;
 print_key(contador);
 break;
 case 3:
 clave_comp[contador] = '3';
 printf("\n%s", clave_comp);
 contador++;
 print_key(contador);
 break;
 case 9:
 clave_comp[contador] = '4';
 printf("\n%s", clave_comp);
 contador++;
 print_key(contador);
 break;
 case 4:
 clave_comp[contador] = '5';
 printf("\n%s", clave_comp);
 contador++;
 print_key(contador);
 break;
 case 5:
 clave_comp[contador] = '6';
 printf("\n%s", clave_comp);
 contador++;
 print_key(contador);
 break;
 case 6:
 clave_comp[contador] = '7';
 printf("\n%s", clave_comp);
 contador++;
 print_key(contador);
 break;
 case 7:
 clave_comp[contador] = '8';
 printf("\n%s", clave_comp);
 contador++;
 print_key(contador);
 break;
 case 8:
 clave_comp[contador] = '9';
 printf("\n%s", clave_comp);
 contador++;
 print_key(contador);
 break;
 case 21:
 memset(&clave_comp, 0, 7);
 printf("\n%s", clave_comp);
 contador = 0;
 print_key(contador);
 break;
 case 20:
 contador = 8;
 print_key(contador);
 break;
 case 23:
 goto final;
 break;

 default:
 contador = 0;
 break;

 }
 }

 }
 clave = atoi(clave_comp);
 printf("clave %d\n", clave);
 if (clave == 6719181) {
 sprintf(data, "t0.txt=\"CLAVE CORRECTA\"");
 sendNextioncmd(&data[0], strlen(data));
 vTaskDelay(2000);
 sprintf(data, "page mant2");
 sendNextioncmd(&data[0], strlen(data));
 printf("data %s", data);
 while (flag != 1) {
 cmd = receiver();
 if (cmd[0] == 0x65) {
 if (cmd[2] == 20) {
 sprintf(data, "page mant2");
 sendNextioncmd(&data[0], strlen(data));
 printf("data %s", data);
 flag = 1;

 }
 }
 }
 } else {
 contador = 0;
 print_key(contador);
 sprintf(data, "t0.txt=\"CLAVE INCORRECTA\"");
 sendNextioncmd(&data[0], strlen(data));
 memset(&clave_comp, 0, 7);
 goto ini;
 }
 final: printf("sali de la funcion \n");
 }
 */
/*
 void GUI_STERIMASTER() {
 alt_u8 i;
 alt_u8 variable1 = 0;
 alt_u8 variable2 = 0;
 alt_u8 variable3 = 0;
 char *cmd;
 cmd = receiver(); //se recibe el array http://wiki.iteadstudio.com/Nextion_Instruction_Set#page_pageid
 switch (cmd[0]) {

 case 0x65:
 if (cmd[1] == 1 && cmd[2] == 11) {
 printf("menu mantenimiento\n");
 key_mant();
 }
 if (cmd[1] == 3) {
 switch (cmd[2]) {
 case 9:
 ev_mant();
 break;
 case 10:
 bomb_mant();
 break;
 case 13:
 puerta_mant();
 break;
 case 17:
 error_mant();
 break;
 case 19:
 fecha_mant();
 break;
 case 21:
 sd_mant();
 break;
 case 23:
 eth_mant();
 break;
 case 25:
 printer_mant();
 break;
 }
 }

 break;
 case 0x66:
 variable1 = cmd[1];

 printf("page now: %d\n", cmd[1]);
 break;

 case 0x67:
 printf(
 "Touch coordinate X High %d coordinate X Low %d coordinate Y high %d coordinate Y low %d touch event %d\n",
 cmd[1], cmd[2], cmd[3], cmd[4], cmd[5]);
 break;
 }

 }
 */
