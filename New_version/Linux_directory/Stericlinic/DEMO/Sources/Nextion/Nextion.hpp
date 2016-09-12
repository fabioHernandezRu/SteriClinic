/*
 * Nextion.hpp
 *
 *  Created on: Aug 18, 2016
 *      Author: Holguer
 */

#ifndef NEXTION_HPP_
#define NEXTION_HPP_

#define NEXTION_LEN 5

#include "../Nextion/HashTable.h"

extern "C" {
#include "../uart_fpga/fifo_control.h"
}

typedef struct Nextion_cmd_rx {
	unsigned char command[100];
	signed char lencommand;
} nextionRX;

void * update_events(void * shared);
char getNextionCmd_available();
char getNextionCmd();
void receiver();
void test_send(string comando);
void print_receiver(unsigned char * cmd, unsigned char len);
void nextion_debug(unsigned char * cmd, unsigned char len);
int SerialRead();
void sendNextioncmd(string cmd);

#endif /* NEXTION_HPP_ */
