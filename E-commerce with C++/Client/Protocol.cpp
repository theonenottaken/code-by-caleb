/*
 * Protocol.cpp
 *
 *  Created on: Dec 31, 2015
 *      Author: caleb
 */

#include "Protocol.hpp"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>
#include <stdio.h>
#include <string.h>

Protocol::Protocol() {
	type = UDP_CONN; // default is UDP
	ip = NULL;
	port = -1;
	sock = -1;
}

Protocol::~Protocol() { }

void Protocol :: makeSocket() {
	if (type == UDP_CONN) {
		sock = socket(AF_INET, SOCK_DGRAM, 0);
		if (sock < 0) {
			perror("error creating socket");
		}
	}
	else {  // type is TCP
		sock = socket(AF_INET, SOCK_STREAM, 0);
		if (sock < 0) {
			perror("error creating socket");
		}
	}
}

void Protocol :: closeConnection() {
	close(sock);
}
