/*
 * valves.h
 *
 *  Created on: Aug 25, 2016
 *      Author: Holguer
 */

#ifndef VALVES_H_
#define VALVES_H_

class valves {
public:
	unsigned long * baseport;
	unsigned char number_valves=0;
	valves();
	valves(unsigned int address,unsigned char numer_of_valves);
	void turn_on(unsigned char channel);
	void turn_off(unsigned char channel);
	void toggle(unsigned char channel);
	unsigned char get(unsigned char channel);
	virtual ~valves();
};

#endif /* VALVES_H_ */
