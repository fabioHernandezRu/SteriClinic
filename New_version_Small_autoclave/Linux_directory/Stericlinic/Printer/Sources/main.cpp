/*
 * main.cpp/
 *
 *  Created on: Aug 11, 2016
 *      Author: Holguer
 */

extern "C" {
#include "hpss.h"
#include <stdio.h>
}

#include "Printer/printer.h"

printer * impresora;

void init_system() {

	//Printer
	impresora = new printer();

}

int main(int argc, char *argv[]) {

	init_system();

	printf("Testing-----Printer---------\n\n");
	if (impresora->getStatus()) {
		puts("Imprimiendo...\n");
		impresora->print("/home/root/file.txt");
	} else {
		puts("impresora no conectada\n");

	}

	return 0;
}

