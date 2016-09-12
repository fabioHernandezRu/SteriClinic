/*
 * max6675.cpp
 *
 *  Created on: Aug 25, 2016
 *      Author: Holguer
 */

#include "max6675.h"

#include <stdio.h>

extern "C" {
#include "../fpga_ports/fpga_ports.h"
}

max6675::max6675() {
	// TODO Auto-generated constructor stub
	// TODO Auto-generated constructor stub
	this->baseport_ch = NULL;
	this->baseport_data = NULL;
}

max6675::max6675(unsigned int address_ch, unsigned int address_data) {

	this->baseport_ch = open_lw(address_ch);
	this->baseport_data = open_lw(address_data);
}

unsigned int max6675::getValue(unsigned int address_ch) {
	unsigned int value = 0;
	*(unsigned int *) this->baseport_ch = address_ch;

	value = *(unsigned int *) this->baseport_data;
	return value;
}

double max6675::readCelsius(unsigned int address_ch) {
	unsigned int value = 0;
	double celsius;
	value = this->getValue(address_ch);

	if (value & 0x4) {
		printf("uh oh, no thermocouple attached!  in channel %d\n",address_ch);
		return -100;
	}
	value >>= 3;
	celsius= (double)value * 0.25;

	return celsius;
}

max6675::~max6675() {
	// TODO Auto-generated destructor stub
}

