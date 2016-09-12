#include"uart.h"


Uart::Uart(unsigned int bau) :
    baurate(bau),nBits(8),nEvent('N'),nStop(1)
    {
    }

void Uart::setBaurate(int bau)
{
    baurate=bau;
}

void Uart::setDevice( std::string dev)
{
    device = dev;
}

bool Uart::openDevice(void)
{
    fd= open(device.c_str(), O_RDWR|O_NOCTTY|O_NDELAY);
    if (fd == -1){
        return false;
    }
    return true;
}

int Uart::setOpt(void)
{
    struct termios newtio,oldtio;
	if  ( tcgetattr( fd,&oldtio)  !=  0) { 
		perror("SetupSerial 1");
		return -1;
	}
	bzero( &newtio, sizeof( newtio ) );
	newtio.c_cflag  |=  CLOCAL | CREAD;
	newtio.c_cflag &= ~CSIZE;

	switch( nBits )
	{
	case 7:
		newtio.c_cflag |= CS7;
		break;
	case 8:
		newtio.c_cflag |= CS8;
		break;
	}

	switch( nEvent )
	{
	case 'O':
		newtio.c_cflag |= PARENB;
		newtio.c_cflag |= PARODD;
		newtio.c_iflag |= (INPCK | ISTRIP);
		break;
	case 'E': 
		newtio.c_iflag |= (INPCK | ISTRIP);
		newtio.c_cflag |= PARENB;
		newtio.c_cflag &= ~PARODD;
		break;
	case 'N':  
		newtio.c_cflag &= ~PARENB;
		break;
	}

	switch( baurate)
	{
	case 2400:
		cfsetispeed(&newtio, B2400);
		cfsetospeed(&newtio, B2400);
		break;
	case 4800:
		cfsetispeed(&newtio, B4800);
		cfsetospeed(&newtio, B4800);
		break;
	case 9600:
		cfsetispeed(&newtio, B9600);
		cfsetospeed(&newtio, B9600);
		break;
	case 115200:
		cfsetispeed(&newtio, B115200);
		cfsetospeed(&newtio, B115200);
		break;
	case 460800:
		cfsetispeed(&newtio, B460800);
		cfsetospeed(&newtio, B460800);
		break;
	default:
		cfsetispeed(&newtio, B9600);
		cfsetospeed(&newtio, B9600);
		break;
	}
	if( nStop == 1 )
		newtio.c_cflag &=  ~CSTOPB;
	else if ( nStop == 2 )
	newtio.c_cflag |=  CSTOPB;
	newtio.c_cc[VTIME]  = 0;//重要
	newtio.c_cc[VMIN] = 100;//返回的最小值  重要
	tcflush(fd,TCIFLUSH);
	if((tcsetattr(fd,TCSANOW,&newtio))!=0)
	{
		perror("com set error");
		return -1;
	}
	return 0;
}


bool Uart::readUart( bool flag )
{
    int nread;
    char buffer[400];
    nread = read(fd, buffer, 400);
    if(nread<0){
        return false;
    }
    else{
        if(flag){
            return true;
        }
        else{
            buffer[nread]='\0';
            readBuffer.assign(buffer);
            return true;
        }
    }
}


bool Uart::writeUart(std::string bufferWrite)
{
    int nread;
    nread = write(fd,bufferWrite.c_str(),bufferWrite.size());
 //   for(int i = 0 ;i<5;i++)
    if(nread<0){
//        readUart( 1);
        return false;
    }
    else{
        readUart(0 );
        return true;
    }
}

bool Uart::writeUart(unsigned char bufferWrite)
{
    int nread;
    unsigned char buffer[2];
    buffer[0]=bufferWrite;
    buffer[1]='\0';
    nread = write(fd,buffer,1);
    if(nread<0){
  //      readUart(0);
       return false;
    }
    else{
        readUart( 1);
        return true;
    }
}


void Uart::sendToLCD(int type,std::string index, std::string cmd)
{
     if (type == 1 ){
        writeUart(index);
        writeUart(".txt=");
        writeUart("\"");
        writeUart(cmd);
        writeUart("\"");
    }
    else if (type == 2){
        writeUart(index);
        writeUart(".val=");
        writeUart(cmd);
    }
    else if (type == 3){
        writeUart(index);
        writeUart(".pic="); 
        writeUart(cmd);
    }
    else if (type ==4 ){
        writeUart("page ");
        writeUart(cmd);
    }
    
     writeUart(0xff);
     writeUart(0xff);
     writeUart(0xff);
    
}





std::string Uart::getReadBuffer(void)
{
     return readBuffer;
}


