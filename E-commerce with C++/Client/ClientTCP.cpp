/*
 * ClientTCP.cpp
 *
 *  Created on: Dec 31, 2015
 *      Author: caleb
 */

#include "ClientTCP.hpp"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>
#include <stdio.h>
#include <string.h>

ClientTCP::ClientTCP(char* ip_addr, int port_num) {
	type = TCP_CONN;
	ip = ip_addr;
	port = port_num;
}

ClientTCP::~ClientTCP() { }

void ClientTCP :: doConnection() {
	memset(&sin, 0, sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = inet_addr(ip);
	sin.sin_port = htons(port);

	if (connect(sock, (struct sockaddr *) &sin, sizeof(sin)) < 0) {
		perror("error connecting to server");
	}
}

