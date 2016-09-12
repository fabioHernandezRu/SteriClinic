/*
 * pwm.cpp
 *
 *  Created on: Aug 25, 2016
 *      Author: Holguer
 */

#include "pwm.h"

extern "C" {
#include "../fpga_ports/fpga_ports.h"
}

pwm::pwm() {
	// TODO Auto-generated constructor stub
	this->baseport_en = NULL;
	this->baseport_data =NULL;

}

void pwm::enable(unsigned char en) {
	*(unsigned int *) this->baseport_en = en;
}

void pwm::set_pwm(unsigned char channel, unsigned char duty) {
	unsigned int receive = *(unsigned int *) this->baseport_data;
	unsigned int data = 0xff << (channel * 8);
	data = ~data;

	receive = data & receive;
	data = receive | (duty << (channel * 8));

	*(unsigned int *) this->baseport_data = data;

}

unsigned char pwm::get_pwm(unsigned char channel) {

	unsigned char data = 0;
	unsigned int receive = *(unsigned int *) this->baseport_data;

	data = (receive >> (channel * 8)) & 0xff;

	return data;
}

pwm::pwm(unsigned int address_en, unsigned int address_data) {
	this->baseport_en = open_lw(address_en);
	this->baseport_data = open_lw(address_data);

	*(unsigned int *) this->baseport_en = 0;
}

pwm::~pwm() {
	// TODO Auto-generated destructor stub
}

