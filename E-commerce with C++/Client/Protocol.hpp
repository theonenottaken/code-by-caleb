/*
 * Protocol.hpp
 *
 *  Created on: Dec 31, 2015
 *      Author: caleb
 */

#ifndef PROTOCOL_HPP_
#define PROTOCOL_HPP_

#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#define UDP_CONN '0'
#define TCP_CONN '1'

class Protocol {
protected:
	int sock;
	char type;
	int port;
	char* ip;
	struct sockaddr_in sin;
public:
	Protocol();
	virtual ~Protocol();
	void makeSocket();
	void closeConnection();
	virtual void sendData(const std::string& d) { }
	virtual std::string receiveData() { return ""; }
	virtual void doConnection() { }
};

#endif /* PROTOCOL_HPP_ */
