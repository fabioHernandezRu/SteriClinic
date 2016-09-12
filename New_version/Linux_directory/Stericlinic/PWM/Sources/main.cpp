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


#include "PWM/pwm.h"


pwm * mosfets;


void init_system() {

	//inicializa el hw
	fflush(stdout);
	init_hw();
	fflush(stdout);


	//Mosfets
	mosfets = new pwm(MOSFET_EN_BASE, MOSFET_CONTROL_BASE);


}

int main(int argc, char *argv[]) {


	//inicializa el hw y lso perifericos
	init_system();




		printf("Testing-----MOSFETs---------\n\n");
		mosfets->enable(1);
		for (int i = 0; i < 8; i++) {
			mosfets->set_pwm(0, 1 << i);
			mosfets->set_pwm(1, 1 << i);
			mosfets->set_pwm(2, 1 << i);
			mosfets->set_pwm(3, 1 << i);
			usleep(100000);
		}
		for (int i = 0; i < 8; i++) {
			mosfets->set_pwm(0, 0x80 >> i);
			mosfets->set_pwm(1, 0x80 >> i);
			mosfets->set_pwm(2, 0x80 >> i);
			mosfets->set_pwm(3, 0x80 >> i);
			usleep(100000);
		}
		mosfets->set_pwm(0, 0);
		mosfets->set_pwm(1, 0);
		mosfets->set_pwm(2, 0);
		mosfets->set_pwm(3, 0);
		mosfets->enable(0);


	//close ports
	uninit_hw();


	return 0;
}

