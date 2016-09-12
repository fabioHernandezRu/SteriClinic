#ifndef  _UART_H
#define  _UART_H


#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<termios.h>
#include<string.h>
#include<string>
#include<iostream>
class Uart  {

    public:
    Uart(unsigned int bau);
    bool readUart(bool flag=false);
    bool writeUart(std::string bufferWrite );
    bool writeUart(unsigned char bufferWrite);
    bool openDevice(void);
    int setOpt(void);
    void setBaurate(int bau);
    void setDevice(std::string dev);
    std::string getReadBuffer(void);
    void sendToLCD(int type,std::string index, std::string cmd);
    private:

    int baurate;
   // char readBuffer[1024];
    std::string readBuffer;
    std::string device;
    int fd;
    int nBits;
    char nEvent;
    int nStop;
} ;


#endif
