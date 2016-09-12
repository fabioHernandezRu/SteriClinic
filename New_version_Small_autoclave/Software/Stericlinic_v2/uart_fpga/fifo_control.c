/*
 * fifo_control.c
 *
 *  Created on: Aug 18, 2016
 *      Author: Holguer
 */

#include "fifo_control.h"

extern void *ports_base;

void fifo32_init(struct fifo32 *fifo, unsigned int data_address,
		unsigned int status_address) {
	fifo->data_port =
			(unsigned int *) (data_address + (unsigned int) ports_base);
	fifo->fill_level_port = (unsigned int *) (status_address + FIFO_FILL_LEVEL
			+ (unsigned int) ports_base);
	fifo->status_port = (unsigned int *) (status_address + FIFO_STATUS
			+ (unsigned int) ports_base);

	printf("ports_base = %p\n", ports_base);
	printf("data_port = %p\n", fifo->data_port);
	printf("fill_level_port = %p\n", fifo->fill_level_port);
	printf("status_port = %p\n", fifo->status_port);
}

int fifo32_empty(struct fifo32 *fifo) {
	return (*fifo->status_port & FIFO_STATUS_EMPTY) ? 1 : 0;
}

int fifo32_full(struct fifo32 *fifo) {
	return (*fifo->status_port & FIFO_STATUS_FULL) ? 1 : 0;
}

void fifo32_write(struct fifo32 *fifo, unsigned int v) {
	while (fifo32_full(fifo));
	*fifo->data_port = v;
}

unsigned int fifo32_read(struct fifo32 *fifo) {
	while (fifo32_empty(fifo))
		;
	return *fifo->data_port;
}

unsigned int fifo32_entries(struct fifo32 *fifo) {
	return *fifo->fill_level_port;
}

