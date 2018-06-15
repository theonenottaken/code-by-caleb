/*
 * TCP.cpp
 *
 *  Created on: Dec 31, 2015
 *      Author: caleb
 */

#include "TCP.hpp"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <cstring>

TCP::TCP() { }

TCP::~TCP() { }

void TCP :: sendData(const std::string& data) {
	char* toSend = new char[data.length() + 1];
	std::strcpy(toSend, data.c_str());
	int data_len = strlen(toSend);
	int sent_bytes = send(sock, toSend, data_len, 0);

	if (sent_bytes < 0) {
		perror("error writing to socket");
	}
	delete toSend;
}

std::string TCP :: receiveData() {
	char buffer[4096];
	memset(&buffer, 0, sizeof(buffer));
	int expected_data_len = sizeof(buffer);
	int read_bytes = recv(sock, buffer, expected_data_len, 0);
	if (read_bytes < 0) {
		perror("error reading from socket");
	}
	return buffer;
}

