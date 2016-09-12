/*
 * uart.h
 *
 *  Created on: Aug 18, 2016
 *      Author: Holguer
 */

#ifndef UART_H_
#define UART_H_

#include "fifo_control.h"

//UART init
void uart_init();
//UART tx stream
char uart_tx_stream(unsigned char * data, int len);
//UART rx
char uart_read();
//UART tx single data
char uart_tx(unsigned char data);
int uart_queue();

#endif /* UART_H_ */
