/*
 * Network.cpp
 *
 *  Created on: Aug 31, 2016
 *      Author: Holguer
 */

#include "Network.h"

#include <stdio.h>
#include <unistd.h>
#include <string.h> /* for strncpy */

Network::Network() {
	// TODO Auto-generated constructor stub
	this->ip = "x.x.x.x";
	this->status=0;
}

int Network::GetIp(char * interface_name){
	 int fd;


	 fd = socket(AF_INET, SOCK_DGRAM, 0);

	 /* I want to get an IPv4 IP address */
	 this->ifr.ifr_addr.sa_family = AF_INET;

	 /* I want IP address attached to "eth0" */
	 strncpy(this->ifr.ifr_name, "eth0", IFNAMSIZ-1);

	 ioctl(fd, SIOCGIFADDR, &this->ifr);
	 int rv = ioctl(fd, SIOCGIFFLAGS, &this->ifr);

	 close(fd);


	 /* display result */
	 printf("%s\n", inet_ntoa(((struct sockaddr_in *)&this->ifr.ifr_addr)->sin_addr));
	 //Enviar comando
	 char buffer[100];
	 snprintf(buffer,sizeof(buffer),"%s",inet_ntoa(((struct sockaddr_in *)&this->ifr.ifr_addr)->sin_addr));
	 this->ip=buffer;
	 this->status=(this->ifr.ifr_flags & IFF_UP) && (this->ifr.ifr_flags & IFF_RUNNING);
	 return this->status;

}


Network::~Network() {
	// TODO Auto-generated destructor stub
}

