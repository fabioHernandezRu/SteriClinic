/*
 * main.cpp/
 *
 *  Created on: Aug 11, 2016
 *      Author: Holguer
 */

#include <stdio.h>
extern "C" {
#include "hpss.h"
}

#include "rtc/rtc.h"

rtc * real_time_clock;

void init_system() {

	//	//RTC
	real_time_clock = new rtc();
	real_time_clock->yymmddhhmmss.date = 17;
	real_time_clock->yymmddhhmmss.second = 7;
	real_time_clock->yymmddhhmmss.day = THURSDAY;
	real_time_clock->yymmddhhmmss.hour = 4;
	real_time_clock->yymmddhhmmss.minutes = 5;
	real_time_clock->yymmddhhmmss.month = 2;
	real_time_clock->yymmddhhmmss.year = 6;
	real_time_clock->yymmddhhmmss.fmt = F24H;

	real_time_clock->rtc_time_set();
}

int main(int argc, char *argv[]) {

	//inicializa el hw y lso perifericos
	init_system();

	puts("Testing-----RTC---------\n\n");
	real_time_clock->rtc_time_get();

	return 0;
}

