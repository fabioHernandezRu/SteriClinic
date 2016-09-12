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

#include "Network/Network.h"

Network * Ethernet;

void init_system() {

	//network
	Ethernet = new Network();

}

int main(int argc, char *argv[]) {

	init_system();
	//

	printf("Testing-----Ethernet---------\n\n");
	printf("Network State %s\n", Ethernet->GetIp("eth0") ? "Up" : "Down");

	return 0;
}

