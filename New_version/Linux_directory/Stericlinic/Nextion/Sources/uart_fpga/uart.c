/*
 * uart.c
 *
 *  Created on: Aug 18, 2016
 *      Author: Holguer
 */

#include "fifo_control.h"
#include "uart.h"

#include "../hpss.h"


struct fifo32 uart_rx_d; // acceso a los registros del FIFO
struct fifo32 uart_tx_d; // acceso a los registros del FIFO


void uart_init() {
	//inicializar rx
	fifo32_init(&uart_rx_d, FIFO_RX_UART_OUT_BASE, FIFO_RX_UART_OUT_CSR_BASE);
	//inicializar tx
	fifo32_init(&uart_tx_d, FIFO_TX_UART_IN_BASE, FIFO_TX_UART_IN_CSR_BASE);

}

char uart_tx(unsigned char data) {

	unsigned int tx_d= (unsigned int )data;
	//printf("transmitiendo %x %d\n",tx_d,fifo32_entries(&uart_tx_d));
	//funcion para enviar al hw el dato q se desea enviar
	fifo32_write(&uart_tx_d, tx_d);
	return 0;
}

char uart_tx_stream(unsigned char * data, int len) {

	while (len > 0) {
		uart_tx(*data);
		data++;
		len--;
	}

	return 0;
}
//UART rx
char uart_read() {
	unsigned int data_D = fifo32_read(&uart_rx_d);
	char ret = data_D & 0xff;
	return ret;
}

int uart_queue() {
	return fifo32_empty(&uart_rx_d);

}

