/*
 * fifo_control.h
 *
 *  Created on: Aug 18, 2016
 *      Author: Holguer
 */

#ifndef FIFO_CONTROL_H_
#define FIFO_CONTROL_H_

#include <stdio.h>

#define FIFO_FILL_LEVEL     0
#define FIFO_STATUS         4
#define FIFO_STATUS_FULL    0x01
#define FIFO_STATUS_EMPTY   0x02
#define FIFO_EVENT          8
#define FIFO_INTERRUPT_ENABLE   12
#define FIFO_ALMOST_FULL    16
#define FIFO_ALMOST_EMPTY   20

struct fifo32 {
	volatile unsigned int *data_port;
	volatile unsigned int *fill_level_port;
	volatile unsigned int *status_port;
};

void fifo32_init(struct fifo32 *fifo, unsigned int data_address,
		unsigned int status_address);

int fifo32_empty(struct fifo32 *fifo);

int fifo32_full(struct fifo32 *fifo);

void fifo32_write(struct fifo32 *fifo, unsigned int v);
unsigned int fifo32_read(struct fifo32 *fifo);

unsigned int fifo32_entries(struct fifo32 *fifo);

#endif /* FIFO_CONTROL_H_ */
