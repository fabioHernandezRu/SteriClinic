/*
 * main.cpp/
 *
 *  Created on: Aug 11, 2016
 *      Author: Holguer
 */

extern "C" {
#include "hpss.h"
#include "./fpga_ports/fpga_ports.h"

}

#include <pthread.h>
#include "MAX6675/max6675.h"

max6675 * sensores_temperatura;

void init_system() {

	//inicializa el hw
	fflush(stdout);
	init_hw();
	fflush(stdout);

	sensores_temperatura = new max6675(SEL_MAX667_BASE, MAX6675_TEMP_BASE);

}

int main(int argc, char *argv[]) {

	//inicializa el hw y lso perifericos
	init_system();

	printf("Testing-----THERMOCOUPLEs---------\n\n");
	printf("State of ThremoCouple %d, Value %04x, Celcius %f\xb0 C\n", 0,
			sensores_temperatura->getValue(0),
			sensores_temperatura->readCelsius(0));
	printf("State of ThremoCouple %d, Value %04x, Celcius %f\xb0 C\n", 1,
			sensores_temperatura->getValue(1),
			sensores_temperatura->readCelsius(1));

	//close ports
	uninit_hw();

	return 0;
}

