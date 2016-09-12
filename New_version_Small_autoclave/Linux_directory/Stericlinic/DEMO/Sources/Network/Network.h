/*
 * Network.h
 *
 *  Created on: Aug 31, 2016
 *      Author: Holguer
 */

#ifndef NETWORK_H_
#define NETWORK_H_

#include <string>/* for strncpy */
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <net/if.h>
#include <arpa/inet.h>

#define NET_OKAY "10"
#define NET_MISSING "9"

class Network {
private:
	struct ifreq ifr;
public:
	std::string  ip;
	char status=0;
	Network();
	int GetIp(char * interface_name);
	virtual ~Network();
};

#endif /* NETWORK_H_ */
