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


#include "Interruptores/interruptores.h"

interruptores * Interrup;
interruptores * ElectroSondas;

void init_system() {

	//inicializa el hw
	fflush(stdout);
	init_hw();
	fflush(stdout);



	//interruptores
	Interrup = new interruptores(BUTTONS_INICIO_EMER_FINAL_CONTROL_BASE, 3);
	//Electro Sondas
	ElectroSondas = new interruptores(ELECTRO_CONTROL_BASE, 4);

}

int main(int argc, char *argv[]) {


	//inicializa el hw y lso perifericos
	init_system();


		printf("Testing-----Interuptores---------\n\n");
		printf("  Inicio=%d\n", Interrup->get_inicio());
		printf("  Final=%d\n", Interrup->get_final());
		printf("  Emergencia=%d\n", Interrup->get_emergencia());
		if (Interrup->inicio) {
			printf(" Inicio on---------\n");
			//sound_card->happy_birthday();
		}
		if (Interrup->final) {
			printf(" Final on---------\n");
			//sound_card->tetris_song();
		}
		Interrup->get_emergencia();

		printf("Testing-----Electrosondas---------\n\n");
		for (int i = 0; i < 4; i++) {
			printf("   Electrosondas[%d] =  %s---------\n", i,
					ElectroSondas->get(i) ? "Encendida" : "Apagada");
			usleep(1000000);
		}

	//close ports
	uninit_hw();

	return 0;
}

