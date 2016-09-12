/*
 * rtc.h
 *
 *  Created on: Aug 25, 2016
 *      Author: Holguer
 */

#ifndef RTC_H_
#define RTC_H_

#define SUNDAY 1
#define MONDAY 2
#define TUESDAY 3
#define WEDNESDAY 4
#define THURSDAY 5
#define FRIDAY 6
#define SATURDAY 7

#define DEBUG_TIME_SET 0
#define DEBUG_FORMAT_SET 0
#define DEBUG_RAM_WRITE 0
#define DEBUG_RAM_READ 0
#define F24H 0
#define F12H 1
#define AM 0
#define PM 1

#define DEVICEI2C_ADDRESS 0x68

#define DEVICE_NAME "/dev/i2c-0"

typedef struct calendario_struct{
    unsigned char  year;/**/
    unsigned char  month;/*mes*/
    unsigned char  day;/*dia de la semana*/
    unsigned char  date;/*fecha*/
    unsigned char  hour; /*hora*/
    unsigned char  minutes;/*minutos*/
    unsigned char  second;/*segundos*/
    unsigned char  am_pm;/*horario*/
    unsigned char  fmt;/*formato de hora*/
}FECHA;


class rtc {
public:
	FECHA yymmddhhmmss;
	/*SE ESCRIBE EN HEXA LOS NUMEROS, al setear*/
	void rtc_time_get();
	void rtc_time_set();
	/*SE ESCRIBE EN HEXA LOS NUMEROS, al setear*/
	void rtc_time_get(FECHA* yymmddhhmmss);
	//Funcion : obtener los valores de fecha del rtc, en una estructura de tipo FECHA
	//Retorno : 1 si la lectura fue satisfactoria, de lo contrario 0
	int rtc_time_set(FECHA* yymmddhhmmss);
	//Funcion : establecer los valores de fecha del rtc, usando una estructura de tipo FECHA
	//Retorno : 1 si la escritura fue satisfactoria , de lo contrario 0
	int rtc_format_set(unsigned char format);
	//Funcion : establecer el formato de hora del rtc, puede ser F24H o F12H
	//Retorno : 1 si se establecio el formato correctamente, de lo contrario 0
	int rtc_ram_write(unsigned char szBuf[],unsigned char from_dir,unsigned char to_dir);
	//Funcion : escribir valores en la ram del rtc, usando un vector
	//Retorno : 1 si la escritura fue satisfactoria , de lo contrario 0
	int rtc_ram_read(unsigned char szBuf[],unsigned char from_dir,unsigned char to_dir);
	//Funcion : leer valores desde la ram del rtc, usando un vector
	//Retorno : 1 si la lectura fue satisfactoria , de lo contrario 0
	int bcd2dec(char num);
	//Funcion complementaria, convierte de bcd a decimal, regresa el valor en decimal
	int dec2bcd(char num);
	//Funcion complementaria, convierte de decimal a bcd, regresa el valor en bcd
	int sizeofstring(unsigned char num[]);
	//Funcion complementaria, halla el tamaño de un string terminado en NULL ('/0')
	int rtc_osf_get();
	int rtc_osf_clr();
	void rtc_clk_halt(unsigned char value);
	rtc();
	virtual ~rtc();
};

#endif /* RTC_H_ */
