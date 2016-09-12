/*
 * valves.cpp
 *
 *  Created on: Aug 25, 2016
 *      Author: Holguer
 */

#include "valves.h"


extern "C" {
#include "../fpga_ports/fpga_ports.h"
}

valves::valves() {
	// TODO Auto-generated constructor stub
	this->baseport = NULL;
	this->number_valves=0;
}


valves::valves(unsigned int address,unsigned char numer_of_valves){
	this->baseport = open_lw(address);

	*(unsigned int *) this->baseport = 0;

	this->number_valves=numer_of_valves;
}

void valves::turn_on(unsigned char channel){
	channel=channel%this->number_valves;

	unsigned int data=*(unsigned int *) this->baseport;
	unsigned int valve_d= 1<<channel;
	*(unsigned int *) this->baseport = data | valve_d;


}

void valves::turn_off(unsigned char channel){

	channel=channel%this->number_valves;

	unsigned int data=*(unsigned int *) this->baseport;
	unsigned int valve_d= 1<<channel;
	valve_d= ~valve_d;
	*(unsigned int *) this->baseport = data & valve_d;

}

void valves::toggle(unsigned char channel){

	channel=channel%this->number_valves;
	unsigned int data=*(unsigned int *) this->baseport;
	unsigned int valve_d= 1<<channel;
	*(unsigned int *) this->baseport = data ^ valve_d;

}

unsigned char valves::get(unsigned char channel){

	channel=channel%this->number_valves;
	unsigned int data=*(unsigned int *) this->baseport;

	data=(data >>channel) & 1;

	return (unsigned char)data;


}

valves::~valves() {
	// TODO Auto-generated destructor stub
}

