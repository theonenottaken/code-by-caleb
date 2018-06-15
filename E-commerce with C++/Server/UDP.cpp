
/*******************************************************************************************
 * Student Name: Caleb Shere Benjmin Wexler
 * Exercise Name: Targil 5
 * File Description: UDP.cpp
 *******************************************************************************************/

#include "UDP.hpp"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <cstring>

/*******************************************************************************
 * Constructor.
 ******************************************************************************/
UDP::UDP() {
	// TODO Auto-generated constructor stub
}

/*******************************************************************************
 * Destructor.
 ******************************************************************************/
UDP::~UDP() {
	// TODO Auto-generated destructor stub
}

/*******************************************************************************
 * This function sends the given string to the client using the function
 * sendto().
 ******************************************************************************/
void UDP :: sendData(const std::string& data) {
	char* toSend = new char[data.length() + 1];
	std::strcpy(toSend, data.c_str());
	int length = strlen(toSend);
	int sent_bytes = sendto(sock, toSend, length, 0, (struct sockaddr *) &from, sizeof(from));
	if (sent_bytes < 0) {
		perror("error writing to socket");
	}
	delete toSend;
}

/*******************************************************************************
 * This function receives a string from the client. It returns the string it
 * receives.
 ******************************************************************************/
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

