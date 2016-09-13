/*
 * Nextion.cpp
 *
 *  Created on: Sep 12, 2016
 *      Author: Holguer
 */

#include "Nextion.h"

#define NULL 0

#include <string.h>

#include <stddef.h>
#include <stdint.h>

#include <strings.h>

#include <ctype.h>

#include <sys/types.h>
#include <stdarg.h>

#include <stdlib.h>

#include <stdio.h>

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

Nextion::Nextion() {
	// TODO Auto-generated constructor stub

}

Nextion::~Nextion() {
	// TODO Auto-generated destructor stub
}

char Nextion::getNextionCmd_available() {
	if (nextion_head == nextion_tail) {
		return -1;
	}
	return 1;
}
char Nextion::getNextionCmd() {
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

void Nextion::test_send(string comando) {

	sendNextioncmd(comando);

}

void Nextion::receiver() {
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

void Nextion::sendNextioncmd(string cmd) {
	uart_tx_stream((unsigned char*) cmd.c_str(), cmd.length());
	uart_tx('\xff');
	uart_tx('\xff');
	uart_tx('\xff');
//	xSerialPutChar(serCOM1, 'ÿ', 0);
//	xSerialPutChar(serCOM1, 'ÿ', 0);
//	xSerialPutChar(serCOM1, 'ÿ', 0);
//

}

void Nextion::print_receiver(unsigned char * cmd, unsigned char len) {
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

void Nextion::nextion_debug(unsigned char * cmd, unsigned char len) {
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

void * Nextion::update_events(void * shared) {
	Item * result;
	char cmnd_number;
	if (getNextionCmd_available()) { // si en el fifo hay datos
		cmnd_number = getNextionCmd(); // toma el primer comando

		while (cmnd_number >= 0) { // mientras q el fifo este lleno

			switch (NextionRX[cmnd_number].command[0]) {
			case 0x66:
				printf("Evento Pagina %x %x\n",
						NextionRX[cmnd_number].command[0],
						NextionRX[cmnd_number].command[1]);
				NextionRX[cmnd_number].command[1] =
						(NextionRX[cmnd_number].command[1] == 0) ?
								0xf5 : NextionRX[cmnd_number].command[1];
				NextionRX[cmnd_number].command[2] = 0x0;
				NextionRX[cmnd_number].command[3] = 0x0;
				NextionRX[cmnd_number].command[4] = 0x0;
				NextionRX[cmnd_number].command[5] = 0x0;
				//busca el la lista eventos
				result =
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
			case 0x65: // en el caso que sea un boton

				printf("buscado...boton %x %x %x %x\n",
						NextionRX[cmnd_number].command[0],
						NextionRX[cmnd_number].command[1],
						NextionRX[cmnd_number].command[2],
						NextionRX[cmnd_number].command[3]);
				NextionRX[cmnd_number].command[1] =
						(NextionRX[cmnd_number].command[1] == 0) ?
								0xf5 : NextionRX[cmnd_number].command[1];
				NextionRX[cmnd_number].command[3] =
						(NextionRX[cmnd_number].command[3] == 0) ?
								0xf5 : NextionRX[cmnd_number].command[3];
				NextionRX[cmnd_number].command[4] = 0x0;
				NextionRX[cmnd_number].command[5] = 0x0;
				//busca el la lista eventos
				result =
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

int Nextion::nextionF(char *str, size_t count, const char *fmt, ...) {
	size_t ret;
	va_list ap;

	va_start(ap, fmt);
	ret = vsnprintf(str, count, fmt, ap);
	va_end(ap);

	this->test_send(str);

	return ret;
}

int Nextion::nextionF(const char *fmt, ...) {
	char str[500];
	size_t count;
	count= 500;
	size_t ret;
	va_list ap;

	va_start(ap, fmt);
	ret = vsnprintf(str, count, fmt, ap);
	va_end(ap);

	this->test_send(str);

	return ret;
}
