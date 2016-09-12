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

#include "./audio/audio.h"

audio * sound_card;

void init_system() {

	//inicializa el hw
	fflush(stdout);
	init_hw();
	fflush(stdout);

	//init sound card, it is required to init_hw(), first
	sound_card = new audio(ALARM_DIV_32_BASE);


}

int main(int argc, char *argv[]) {


	//inicializa el hw y lso perifericos
	init_system();



		printf("Testing-----SONG---------\n\n");
		sound_card->star_wars_song();


	//close ports
	uninit_hw();


	return 0;
}

