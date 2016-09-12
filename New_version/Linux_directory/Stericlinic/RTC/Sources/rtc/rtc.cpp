/*
 * rtc.cpp
 *
 *  Created on: Aug 25, 2016
 *      Author: Holguer
 */

#include "rtc.h"

#include <linux/i2c.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <fcntl.h>





void rtc::rtc_time_get() {

	this->rtc_time_get(&this->yymmddhhmmss);
}

void rtc::rtc_time_set(){
	this->rtc_time_set(&this->yymmddhhmmss);
}

void rtc::rtc_time_get(FECHA* yymmddhhmmss) {
	unsigned char szBuf[7];
	unsigned char _readflag;

	int deviceHandle;
	int readBytes;
	char buffer[7];

	// open device on /dev/i2c-0
	if ((deviceHandle = open(DEVICE_NAME, O_RDWR)) < 0) {
		printf("Error: Couldn't open device! %d\n", deviceHandle);
		return;
	}

	// connect to DS1307 as i2c slave
	if (ioctl(deviceHandle, I2C_SLAVE, DEVICEI2C_ADDRESS) < 0) {
		printf("Error: Couldn't find device on address!\n");
		close(deviceHandle);
		return;
	}


	// begin transmission and request acknowledgement
	buffer[0]=0;
	readBytes = write(deviceHandle, buffer, 1);
	if (readBytes != 1) {
		printf("Error: Received no ACK-Bit, couldn't established connection!");
	} else {
		// read response
		readBytes = read(deviceHandle, szBuf, sizeof(szBuf));
		if (readBytes != sizeof(szBuf)) {
			printf("Error: Received no data!");
		} else {

  			    yymmddhhmmss->second=(unsigned char)((((0x70&szBuf[0])>>4)*10)+(0x0F&szBuf[0]));
			    yymmddhhmmss->minutes=(unsigned char)((((0x70&szBuf[1])>>4)*10)+(0x0F&szBuf[1]));
			    yymmddhhmmss->fmt=(unsigned char)((szBuf[2]>>6)&0x01);
			    yymmddhhmmss->am_pm=(unsigned char)((szBuf[2]>>5)&0x01);

			    if((szBuf[2]>>6)==0)//24h
			    {        yymmddhhmmss->hour=(unsigned char)(bcd2dec(szBuf[2]&0x3F));    }
			    else //12H
			    {    yymmddhhmmss->hour=(unsigned char)((((0x10&szBuf[2])>>4)*10)+(0x0F&szBuf[2]));    }

			    yymmddhhmmss->day=(unsigned char)(0x07&szBuf[3]);
			    yymmddhhmmss->date=(unsigned char)((((0x30&szBuf[4])>>4)*10)+(0x0F&szBuf[4]));
			    yymmddhhmmss->month=(unsigned char)((((0x10&szBuf[5])>>4)*10)+(0x0F&szBuf[5]));
			    yymmddhhmmss->year=(unsigned char)((((0xF0&szBuf[6])>>4)*10)+(0x0F&szBuf[6]));


				// and print results
				printf("Actual RTC-time:\n");
				printf("Date: %d-%d-%d\n", yymmddhhmmss->year, yymmddhhmmss->month, yymmddhhmmss->date);
				printf("Time: %d:%d:%d\n", yymmddhhmmss->hour, yymmddhhmmss->minutes, yymmddhhmmss->second);



		}
	}

	// close connection and return
	close(deviceHandle);

}

int rtc::rtc_time_set(FECHA* yymmddhhmmss) {
	unsigned char szBuf[7];
	unsigned char fmt;
	unsigned char am_pm;

	int deviceHandle;
	int readBytes;
	char buffer[7];

	fmt= yymmddhhmmss->fmt;
	am_pm= yymmddhhmmss->am_pm;
	szBuf[0] = yymmddhhmmss->second;
	szBuf[1] = yymmddhhmmss->minutes;
//
	  if((szBuf[0]>0x59)|(szBuf[1]>0x59)){return 0;}//error.valor fuera de rango
	    if(fmt==F12H)
	    {
	        if((yymmddhhmmss->hour)>0x12)
	        {return 0;}//error.valor fuera de rango
	        szBuf[2]=(yymmddhhmmss->hour)|(am_pm<<5)|(fmt<<6);
	    }
	    else if(fmt==F24H)
	    {
	        if((yymmddhhmmss->hour)>0x23)
	        {return 0;}//error.valor fuera de rango
	        szBuf[2]=yymmddhhmmss->hour;
	    }

	szBuf[3] = yymmddhhmmss->day;
	szBuf[4] = yymmddhhmmss->date;
	szBuf[5] = yymmddhhmmss->month;
	szBuf[6] = yymmddhhmmss->year;

	//AM PM
	unsigned char _writeflag;

	// open device on /dev/i2c-0
	if ((deviceHandle = open(DEVICE_NAME, O_RDWR)) < 0) {
		printf("Error: Couldn't open device! %d\n", deviceHandle);
		return 0;
	}

	// connect to DS1307 as i2c slave
	if (ioctl(deviceHandle, I2C_SLAVE, DEVICEI2C_ADDRESS) < 0) {
		printf("Error: Couldn't find device on address!\n");
		close(deviceHandle);
		return 0;
	}

	printf("seteando hora\n");
	buffer[0]=0;
//	// begin transmission and request acknowledgement
	readBytes = write(deviceHandle, buffer, 1);
	if (readBytes != 1) {
		printf("Error: Received no ACK-Bit, couldn't established connection!");
	} else {
		// read response
		readBytes = write(deviceHandle, szBuf, sizeof(szBuf));
		if (readBytes != sizeof(szBuf)) {
			printf("Error: Received no data!");
		} else {
			printf("Hora Seteada\n");
		}
	}


	// close connection and return
	close(deviceHandle);

	return 1;
}

int rtc::rtc_format_set(unsigned char format) {
	const unsigned char DeviceAddr = 0xD0;
	const unsigned char ControlAddr = 0x02;
	unsigned char ControlData = 0x00;
	unsigned char am_pm = 0;
	unsigned char _writeflag;

	int deviceHandle;
	int readBytes;
	char buffer[7];

// open device on /dev/i2c-0
	if ((deviceHandle = open(DEVICE_NAME, O_RDWR)) < 0) {
		printf("Error: Couldn't open device! %d\n", deviceHandle);
		return 0;
	}

// connect to DS1307 as i2c slave
	if (ioctl(deviceHandle, I2C_SLAVE, DEVICEI2C_ADDRESS) < 0) {
		printf("Error: Couldn't find device on address!\n");
		close(deviceHandle);
		return 0;
	}

	buffer[0]=0x02;
// begin transmission and request acknowledgement
	readBytes = write(deviceHandle, &buffer[0], 1);
	if (readBytes != 1) {
		printf("Error: Received no ACK-Bit, couldn't established connection!");
	} else {
		// read response
		readBytes = read(deviceHandle, &ControlData, 1);
		if (readBytes != 1) {
			printf("Error: Received no data!");
		} else {

			if ((ControlData == 0x12) & ((0x01 & (ControlData >> 5)) == 0)) {
				ControlData = 0;
			}

			if ((format & 0x01) == 1) //paso a 12
					{
				if ((0x01 & (ControlData >> 6)) == 0) //si viene de 24
						{
					ControlData = bcd2dec(0x3F & ControlData);
					if (ControlData > 12) //y es mayor de 12
							{
						ControlData = ControlData - 12;
						am_pm = 1;
					} //reste 12 y pm
					else if ((0x3F & ControlData) <= 12) //y es menor o igual a 12
							{
						am_pm = 0;
					}                           //am
					ControlData = dec2bcd(ControlData);
				}
				ControlData = (0x1F & ControlData) | (0x01 << 6) | (am_pm << 5);
			}

			else if ((format & 0x01) == 0)                           //paso a 24
					{
				if ((0x01 & (ControlData >> 6)) == 1)           //si viene de 12
						{
					if ((0x01 & (ControlData >> 5)) == 1)              //y es pm
							{
						ControlData = bcd2dec(0x1F & ControlData) + 12;
						ControlData = dec2bcd(ControlData);
					}
				}
				ControlData = (0x3F & ControlData);
			}

			_writeflag = write(deviceHandle, &ControlData, 1);

		}
	}

	// close connection and return
	close(deviceHandle);

	return _writeflag;

}

int rtc::rtc_ram_write(unsigned char szBuf[], unsigned char from_dir,
		unsigned char to_dir) {

	int deviceHandle;
	int readBytes;
	char buffer[7];

	const unsigned char size_range = (to_dir - from_dir + 1);
	unsigned char _writeflag;
	if ((sizeof(szBuf) / sizeof(szBuf[0])) > size_range) {

		return 0;
	}

	// open device on /dev/i2c-0
	if ((deviceHandle = open(DEVICE_NAME, O_RDWR)) < 0) {
		printf("Error: Couldn't open device! %d\n", deviceHandle);
		return 0;
	}

	// connect to DS1307 as i2c slave
	if (ioctl(deviceHandle, I2C_SLAVE, DEVICEI2C_ADDRESS) < 0) {
		printf("Error: Couldn't find device on address!\n");
		close(deviceHandle);
		return 0;
	}

	// begin transmission and request acknowledgement
	readBytes = write(deviceHandle,  &from_dir, 1);
	if (readBytes != 1) {
		printf("Error: Received no ACK-Bit, couldn't established connection!");
	} else {
		// read response
		readBytes = write(deviceHandle, szBuf, size_range);
		if (readBytes != size_range) {
			printf("Error: Received no data!");
		} else {

		}
	}

	// close connection and return
	close(deviceHandle);

	return 1;
}

int rtc::rtc_ram_read(unsigned char szBuf[], unsigned char from_dir,
		unsigned char to_dir) {

	int deviceHandle;
	int readBytes;
	char buffer[7];

	unsigned char _readflag;
	const unsigned char DeviceAddr = 0xD0;
	//const unsigned char ControlAddr = 0x08;
	const unsigned char size_range = (to_dir - from_dir + 1);

	// open device on /dev/i2c-0
	if ((deviceHandle = open(DEVICE_NAME, O_RDWR)) < 0) {
		printf("Error: Couldn't open device! %d\n", deviceHandle);
		return 0;
	}

	// connect to DS1307 as i2c slave
	if (ioctl(deviceHandle, I2C_SLAVE, DEVICEI2C_ADDRESS) < 0) {
		printf("Error: Couldn't find device on address!\n");
		close(deviceHandle);
		return 0;
	}

	// begin transmission and request acknowledgement
	readBytes = write(deviceHandle, &from_dir, 1);
	if (readBytes != 1) {
		printf("Error: Received no ACK-Bit, couldn't established connection!");
	} else {
		// read response
		readBytes = read(deviceHandle, szBuf, size_range);
		_readflag=readBytes;
		if (readBytes != size_range) {
			printf("Error: Received no data!");
		} else {

		}
	}

	// close connection and return
	close(deviceHandle);

	if (_readflag) {

		return 1;
	} else {

		return 0;
	}

}
int rtc::rtc_osf_get() {
	unsigned char szBuf;
	int deviceHandle;
	int readBytes;
	char buffer[7];

	// open device on /dev/i2c-0
	if ((deviceHandle = open(DEVICE_NAME, O_RDWR)) < 0) {
		printf("Error: Couldn't open device! %d\n", deviceHandle);
		return 0;
	}

	// connect to DS1307 as i2c slave
	if (ioctl(deviceHandle, I2C_SLAVE, DEVICEI2C_ADDRESS) < 0) {
		printf("Error: Couldn't find device on address!\n");
		close(deviceHandle);
		return 0;
	}

	buffer[0] = 0x0;
	// begin transmission and request acknowledgement
	readBytes = write(deviceHandle, &buffer[0], 1);
	if (readBytes != 1) {
		printf("Error: Received no ACK-Bit, couldn't established connection!");
	} else {
		// read response
		readBytes = read(deviceHandle, &szBuf, 1);
		if (readBytes != 1) {
			printf("Error: Received no data!");
		} else {

		}
	}

	// close connection and return
	close(deviceHandle);

	return ((szBuf >> 5) & 0x01);
}
int rtc::rtc_osf_clr() {
	int deviceHandle;
	int readBytes;
	char buffer[7];

	// open device on /dev/i2c-0
	if ((deviceHandle = open(DEVICE_NAME, O_RDWR)) < 0) {
		printf("Error: Couldn't open device! %d\n", deviceHandle);
		return 0;
	}

	// connect to DS1307 as i2c slave
	if (ioctl(deviceHandle, I2C_SLAVE, DEVICEI2C_ADDRESS) < 0) {
		printf("Error: Couldn't find device on address!\n");
		close(deviceHandle);
		return 0;
	}

	buffer[0] = 0x07;
	// begin transmission and request acknowledgement
	readBytes = write(deviceHandle, &buffer[0], 1);
	if (readBytes != 1) {
		printf("Error: Received no ACK-Bit, couldn't established connection!");
	} else {
		buffer[0] = 0;
		// read response
		readBytes = write(deviceHandle, &buffer[0], 1);
		if (readBytes != 1) {
			printf("Error: Received no data!");
		} else {

		}
	}

	// close connection and return
	close(deviceHandle);

	return readBytes;

}
void rtc::rtc_clk_halt(unsigned char value) {
	int deviceHandle;
	int readBytes;
	char buffer[7];

	unsigned char szBuf;
	unsigned char t;

	// open device on /dev/i2c-0
	if ((deviceHandle = open(DEVICE_NAME, O_RDWR)) < 0) {
		printf("Error: Couldn't open device! %d\n", deviceHandle);
		return;
	}

	// connect to DS1307 as i2c slave
	if (ioctl(deviceHandle, I2C_SLAVE, DEVICEI2C_ADDRESS) < 0) {
		printf("Error: Couldn't find device on address!\n");
		close(deviceHandle);
		return;
	}

	buffer[0] = 0;
	// begin transmission and request acknowledgement
	readBytes = write(deviceHandle, &buffer[0], 1);
	if (readBytes != 1) {
		printf("Error: Received no ACK-Bit, couldn't established connection!");
	} else {
		// read response
		readBytes = read(deviceHandle, &szBuf, 1);
		if (readBytes != 1) {
			printf("Error: Received no data!");
		} else {

		}
	}

	printf("value = %x\n", value);
	printf("szbuf1 = %x\n", szBuf);
	if (value == 1) {
		szBuf = (szBuf | 0x80);
	} else if (value == 0) {
		szBuf = (szBuf & 0x3F);
	}
	printf("szbuf2 = %x\n", szBuf);

	buffer[0] = 0;
// begin transmission and request acknowledgement
	readBytes = write(deviceHandle, &buffer[0], 1);
	if (readBytes != 1) {
		printf("Error: Received no ACK-Bit, couldn't established connection!");
	} else {
		// read response
		readBytes = write(deviceHandle, &szBuf, 1);
		if (readBytes != 1) {
			printf("Error: Received no data!");
		} else {

		}
	}

	// close connection and return
	close(deviceHandle);

}

int rtc::bcd2dec(char num) {
	char ans;
	ans = (num & 0x0F) + (((num & 0xF0) >> 4) * 10);
	return ans;
}
int rtc::dec2bcd(char num) {
	char ans;
	ans = ((num % 10) | ((num / 10) << 4));
	return ans;
}
int rtc::sizeofstring(unsigned char szBuf[]) {
	unsigned char num = 0;
	while (szBuf[num] != '\0') {
		num++;
	}
	return num;
}



rtc::rtc() {
	// TODO Auto-generated constructor stub
	// print infos
		printf("RTC DS1338\n");
		printf("========================================\n");

		int deviceHandle;
		int readBytes;
		char buffer[7];

		// initialize buffer
		buffer[0] = 0x00;

		// address of DS1307 RTC device
		int deviceI2CAddress = 0x68;

		// open device on /dev/i2c-0
		if ((deviceHandle = open("/dev/i2c-1", O_RDWR)) < 0) {
			printf("Error: Couldn't open device! %d\n", deviceHandle);

		}

		// connect to DS1307 as i2c slave
		if (ioctl(deviceHandle, I2C_SLAVE, deviceI2CAddress) < 0) {
			printf("Error: Couldn't find device on address!\n");

		}

		// begin transmission and request acknowledgement
		readBytes = write(deviceHandle, buffer, 1);
		if (readBytes != 1)
		{
			printf("Error: Received no ACK-Bit, couldn't established connection!");
		}
		else
		{
			// read response
			readBytes = read(deviceHandle, buffer, 7);
			if (readBytes != 7)
			{
				printf("Error: Received no data!");
			}
			else
			{
				// get data
				int seconds = buffer[0];	// 0-59
				int minutes = buffer[1];	// 0-59
				int hours = buffer[2];		// 1-23
				int dayOfWeek = buffer[3];	// 1-7
				int day = buffer[4];		// 1-28/29/30/31
				int month = buffer[5];		// 1-12
				int year = buffer[6];		// 0-99;

				// and print results
				printf("Actual RTC-time:\n");
				printf("Date: %x-%x-%x\n", year, month, day);
				printf("Time: %x:%x:%x\n", hours, minutes, seconds);
			}
		}

		// close connection and return
		close(deviceHandle);
}

rtc::~rtc() {
	// TODO Auto-generated destructor stub
}

