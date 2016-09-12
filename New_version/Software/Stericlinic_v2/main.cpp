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
#include "./Nextion/Nextion.h"
#include "./tasks/gui_task.hpp"
#include "./audio/audio.h"
#include "ADC/adcltc2308.h"
#include "MAX6675/max6675.h"
#include "rtc/rtc.h"
#include "PWM/pwm.h"
#include "Valves/valves.h"
#include "Interruptores/interruptores.h"
#include "Control/Fuzzy.h"
#include "Network/Network.h"
#include "Printer/printer.h"
#include "DataLog/DataLogger.h"

audio * sound_card;
adc_ltc2308 * sensores_presion;
max6675 * sensores_temperatura;
rtc * real_time_clock;
pwm * mosfets;
valves * Valvulas;
interruptores * Interrup;
interruptores * ElectroSondas;
Fuzzy * Control;
Network * Ethernet;
printer * impresora;
Nextion * LCD;

DataLogger * grabador;

void init_system() {

	//inicializa el hw
	fflush(stdout);
	init_hw();
	fflush(stdout);

	//init sound card, it is required to init_hw(), first
	sound_card = new audio(ALARM_DIV_32_BASE);

	//Sensores
	sensores_presion = new adc_ltc2308(ADC_SEL_CHANNEL_BASE,
	ADC_INPUT_DATA_BASE);
	sensores_temperatura = new max6675(SEL_MAX667_BASE, MAX6675_TEMP_BASE);

	//Mosfets
	mosfets = new pwm(MOSFET_EN_BASE, MOSFET_CONTROL_BASE);

	//Valves
	Valvulas = new valves(VALVES_CONTROL_BASE, 3);

	//interruptores
	Interrup = new interruptores(BUTTONS_INICIO_EMER_FINAL_CONTROL_BASE, 3);
	//Electro Sondas
	ElectroSondas = new interruptores(ELECTRO_CONTROL_BASE, 4);

	//control
	Control = new Fuzzy();

	//network
	Ethernet = new Network();

	//Printer
	impresora= new printer();

	//datalogger
	grabador= new DataLogger();

	//rtc
	real_time_clock = new rtc();

	//LCD
	LCD= new Nextion();

}





int main(int argc, char *argv[]) {


	//inicializa el hw y lso perifericos
	init_system();


	// test json para configuraciones iniciales
	grabador->load_init_configs();

	//inicializa los eventos de la GUI, y los task correspondientes a la GUI
	init_gui();

	while (1) { //bucle infinito

		usleep(1000000);

	}

	//close ports
	uninit_hw();
	/* Last thing that main() should do */
	pthread_exit(NULL);

	return 0;
}

