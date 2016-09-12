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

#include "Valves/valves.h"


valves * Valvulas;

void init_system() {

	//inicializa el hw
	fflush(stdout);
	init_hw();
	fflush(stdout);



	//Valves
	Valvulas = new valves(VALVES_CONTROL_BASE, 3);


}

int main(int argc, char *argv[]) {


	//inicializa el hw y lso perifericos
	init_system();


		printf("Testing-----VALVES---------\n\n");
		for (int i = 0; i < 3; i++) {
			printf("   Turning on-----VALVE %d---------\n", i);
			Valvulas->turn_on(i);
			usleep(1000000);
		}
		for (int i = 0; i < 6; i++) {
			printf("   toggling on-----VALVE %d---------\n", i % 3);
			Valvulas->toggle(i % 3);
			usleep(1000000);
		}

		for (int i = 0; i < 3; i++) {
			printf("   Turning off-----VALVE %d---------\n", i);
			Valvulas->turn_off(i % 3);
			usleep(1000000);
		}


	//close ports
	uninit_hw();

	return 0;
}

