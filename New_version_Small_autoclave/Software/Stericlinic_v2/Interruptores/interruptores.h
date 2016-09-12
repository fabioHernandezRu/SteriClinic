/*
 * interruptores.h
 *
 *  Created on: Aug 25, 2016
 *      Author: Holguer
 */

#ifndef INTERRUPTORES_H_
#define INTERRUPTORES_H_

class interruptores {
public:
	unsigned long * baseport;
	unsigned char number_int;
	unsigned char inicio,emergencia,final;
	interruptores();
	interruptores(unsigned int address,unsigned int number_int);
	unsigned char get(unsigned char channel);
    unsigned char get();
    unsigned char get_inicio();
    unsigned char get_final();
    unsigned char get_emergencia();
	virtual ~interruptores();
};

#endif /* INTERRUPTORES_H_ */
