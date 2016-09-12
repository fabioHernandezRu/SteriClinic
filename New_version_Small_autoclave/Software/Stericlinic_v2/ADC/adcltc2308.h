/*
 * adcltc2308.h
 *
 *  Created on: Aug 25, 2016
 *      Author: Holguer
 */

#ifndef ADCLTC2308_H_
#define ADCLTC2308_H_

class adc_ltc2308 {
public:
	unsigned long * baseport_ch;
	unsigned long * baseport_data;
	adc_ltc2308();
	adc_ltc2308(unsigned int address_ch,unsigned int address_data);

	float getVoltage(unsigned char channel);
	float getPSI(unsigned char channel);

	int getValue(unsigned char channel);

	virtual ~adc_ltc2308();
};

#endif /* ADCLTC2308_H_ */
