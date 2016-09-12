/*
 * max6675.h
 *
 *  Created on: Aug 25, 2016
 *      Author: Holguer
 */

#ifndef MAX6675_H_
#define MAX6675_H_

class max6675 {
public:
	unsigned long * baseport_ch;
	unsigned long * baseport_data;
	max6675();
	max6675(unsigned int address_ch,unsigned int address_data);

	unsigned int getValue(unsigned int address_ch);
	double readCelsius(unsigned int address_ch);
	virtual ~max6675();
};

#endif /* MAX6675_H_ */
