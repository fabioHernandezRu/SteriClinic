/*
 * adcltc2308.cpp
 *
 *  Created on: Aug 25, 2016
 *      Author: Holguer
 */

#include "adcltc2308.h"

extern "C" {
#include "../fpga_ports/fpga_ports.h"
}

adc_ltc2308::adc_ltc2308() {
	// TODO Auto-generated constructor stub
	this->baseport_ch=NULL;
	this->baseport_data=NULL;
}

adc_ltc2308::adc_ltc2308(unsigned int address_ch,unsigned int address_data){
	this->baseport_ch = open_lw(address_ch);
	this->baseport_data = open_lw(address_data);
}


int adc_ltc2308::getValue(unsigned char channel){
	channel=channel+1;

	*(unsigned int *) this->baseport_ch =channel;
	return *(unsigned int *) this->baseport_data;
}


float adc_ltc2308::getVoltage(unsigned char channel){

	int Value=0;
	float Voltage=0;


	Value=this->getValue(channel);

	Voltage= (float)Value/1000.0;

	return Voltage;

}


float adc_ltc2308::getPSI(unsigned char channel){
	float psi=0.0;
	float voltage;

	voltage= this->getVoltage(channel);

	psi=(float)(((voltage/5.0)-0.04)/0.0012858)*0.145038;

	return psi;
}


adc_ltc2308::~adc_ltc2308() {
	// TODO Auto-generated destructor stub
}

