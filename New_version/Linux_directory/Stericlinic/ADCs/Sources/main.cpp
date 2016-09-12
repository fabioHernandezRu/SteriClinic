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

#include "ADC/adcltc2308.h"

adc_ltc2308 * sensores_presion;

void init_system() {

	//inicializa el hw
	fflush(stdout);
	init_hw();
	fflush(stdout);

	//Sensores
	sensores_presion = new adc_ltc2308(ADC_SEL_CHANNEL_BASE,
	ADC_INPUT_DATA_BASE);

}

int main(int argc, char *argv[]) {


	//inicializa el hw y lso perifericos
	init_system();


	printf("Testing-----ADCs---------\n\n");
	for (int i = 0; i < 8; i++) {
		printf("CH %d:  Voltage = %f %fpsi\n", i,
				sensores_presion->getVoltage(i),
				sensores_presion->getPSI(i));
	}


	//close ports
	uninit_hw();

	return 0;
}

