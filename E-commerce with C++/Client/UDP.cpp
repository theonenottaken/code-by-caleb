/*
 * UDP.cpp
 *
 *  Created on: Dec 31, 2015
 *      Author: caleb
 */

#include "UDP.hpp"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <cstring>

UDP::UDP() { }

UDP::~UDP() { }

void UDP :: sendData(const std::string& data) {
	memset(&sin, 0, sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = inet_addr(ip);
	sin.sin_port = htons(port);

	char* toSend = new char[data.length() + 1];
	std::strcpy(toSend, data.c_str());
	int data_len = strlen(toSend);

	int	 sent_bytes = sendto(sock, toSend, data_len, 0, (struct sockaddr *) &sin, sizeof(sin));
	if (sent_bytes < 0) {
		perror("error writing to socket");
	}
	delete toSend;
}

std::string UDP :: receiveData() {
	unsigned int from_len = sizeof(struct sockaddr_in);
	char buffer[4096];
	memset(&buffer, 0, sizeof(buffer));
	int bytes = recvfrom(sock, buffer, sizeof(buffer), 0, (struct sockaddr *) &from, &from_len);
	if (bytes < 0) {
		perror("error reading from socket");
	}
	return buffer;
}

