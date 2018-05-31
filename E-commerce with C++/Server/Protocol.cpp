
/*******************************************************************************************
 * Student Name: Caleb Shere Benjamin Wexler
 * Exercise Name: Targil 5
 * File Description: Protocol.cpp
 *******************************************************************************************/

#include "Protocol.hpp"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>
#include <stdio.h>
#include <string.h>

/******************************************************************************************
 * Constructor. Will be called when the derived class's constructor is called.
 * Initializes these members to the following values.
 ******************************************************************************************/
Protocol::Protocol() {
	type = 0;
	ip = NULL;
	port = -1;
	sock = -1;
}

/******************************************************************************************
 * Destructor.
 ******************************************************************************************/
Protocol::~Protocol() {
	// TODO Auto-generated destructor stub
}

/******************************************************************************************
 * Depending on the connection type (UDP or TCP), this function makes an appropriate
 * socket and saves the socket descriptor to the sock member.
 ******************************************************************************************/
void Protocol :: makeSocket() {
	if (type == UDP_CONN) { // UDP
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

/*********************************************************************************************
 * This function closes the socket.
 *********************************************************************************************/
void Protocol :: closeConnection() {
	close(sock);
}
