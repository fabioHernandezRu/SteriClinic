/*
 * interruptores.cpp
 *
 *  Created on: Aug 25, 2016
 *      Author: Holguer
 */

#include "interruptores.h"

extern "C" {
#include "../fpga_ports/fpga_ports.h"
}

interruptores::interruptores() {
	// TODO Auto-generated constructor stub
	this->baseport = NULL;
	this->number_int = 0;
	this->inicio = 0;
	this->emergencia = 0;
	this->final = 0;
}

interruptores::interruptores(unsigned int address, unsigned int number_int) {
	this->baseport = open_lw(address);
	this->number_int = number_int;
	this->inicio = 0;
	this->emergencia = 0;
	this->final = 0;
}

unsigned char interruptores::get(unsigned char channel) {
	channel = channel % this->number_int;
	unsigned int data = *(unsigned int *) this->baseport;

	data = (data >> channel) & 1;

	return (unsigned char) data;
}

unsigned char interruptores::get() {
	unsigned int data = *(unsigned int *) this->baseport;

	this->inicio = (data >> 1) & 1;
	this->final = (data) & 1;
	this->emergencia = (data >> 2) & 1;

	return (unsigned char) data;
}

unsigned char interruptores::get_inicio() {
	unsigned int data = *(unsigned int *) this->baseport;

	this->inicio = (data >> 1)& 1;

	return this->inicio;
}

unsigned char interruptores::get_final() {
	unsigned int data = *(unsigned int *) this->baseport;

	this->final = (data) & 1;

	return this->final;
}

unsigned char interruptores::get_emergencia() {
	unsigned int data = *(unsigned int *) this->baseport;

	this->emergencia = (data >> 2) & 1;

	return this->emergencia;
}

interruptores::~interruptores() {
	// TODO Auto-generated destructor stub
}

