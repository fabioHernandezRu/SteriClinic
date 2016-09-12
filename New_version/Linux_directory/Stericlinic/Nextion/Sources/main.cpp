/*
 * main.cpp/
 *
 *  Created on: Aug 11, 2016
 *      Author: Holguer
 */

extern "C" {
#include "hpss.h"
#include "./fpga_ports/fpga_ports.h"
#include "./uart_fpga/fifo_control.h"
}

#include <pthread.h>
#include "./Nextion/Nextion.hpp"
#include "./tasks/gui_task.hpp"


void init_system() {

	//inicializa el hw
	fflush(stdout);
	init_hw();
	fflush(stdout);

}

int main(int argc, char *argv[]) {


	//inicializa el hw y lso perifericos
	init_system();

	//inicializa los eventos de la GUI, y los task correspondientes a la GUI
	init_gui();

	while (1) { //bucle infinito


	}

	//close ports
	uninit_hw();
	/* Last thing that main() should do */
	pthread_exit(NULL);

	return 0;
}

