
/*******************************************************************************************
 * Student Name: Caleb Shere Benjmin Wexler
 * Exercise Name: Targil 5
 * File Description: TCP.cpp
 *******************************************************************************************/

#include "TCP.hpp"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <cstring>

/************************************************************************************
 * Constructor.
 ************************************************************************************/
TCP::TCP() {
	client_sock = -1;

}

/************************************************************************************
 * Destructor.
 ************************************************************************************/
TCP::~TCP() {
	// TODO Auto-generated destructor stub
}

/************************************************************************************
 * This function sends the given string to the client socket given by the socket
 * descriptor parameter cSocket.
 ************************************************************************************/
void TCP :: sendData(const std::string& data, int cSocket) {
	char* toSend = new char[data.length() + 1];
	std::strcpy(toSend, data.c_str());
	int length = strlen(toSend);
	int sent_bytes = send(cSocket, toSend, length, 0);

	if (sent_bytes < 0) {
		perror("error sending to client");
	}
	delete toSend;
}

/************************************************************************************
 * This function receives a string from the given client socket, sent by the client.
 * It returns the string it received.
 ************************************************************************************/
std::string TCP :: receiveData(int cSocket) {
	char buffer[4096];
	memset(&buffer, 0, sizeof(buffer));
	int expected_data_len = sizeof(buffer);
	int read_bytes = recv(cSocket, buffer, expected_data_len, 0);
	if (read_bytes == 0) {
	// connection is closed
	}
	else if (read_bytes < 0) {
		perror("error reading from socket");
	}
	return buffer;
}
