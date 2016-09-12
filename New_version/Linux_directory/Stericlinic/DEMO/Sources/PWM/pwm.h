/*
 * pwm.h
 *
 *  Created on: Aug 25, 2016
 *      Author: Holguer
 */

#ifndef PWM_H_
#define PWM_H_

class pwm {
public:
	unsigned long * baseport_en;
	unsigned long * baseport_data;
	void enable(unsigned char en);
	void set_pwm(unsigned char channel, unsigned char duty);
	unsigned char get_pwm(unsigned char channel);
	pwm();
	pwm(unsigned int address_en,unsigned int address_data);
	virtual ~pwm();
};

#endif /* PWM_H_ */
