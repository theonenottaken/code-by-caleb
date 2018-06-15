
/*******************************************************************************************
 * Student Name: Caleb Shere Benjamin Wexler
 * Exercise Name: Targil 5
 * File Description: Protocol.hpp
 *******************************************************************************************/

#ifndef PROTOCOL_HPP_
#define PROTOCOL_HPP_

#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include "definitions.h"

class Protocol {
protected:
	int sock;
	char type;
	int port;
	char* ip;
	struct sockaddr_in sin;
public:
	/*************************************************************************************
	 * Constructor. Will be called with the derived class's constructor.
	 *************************************************************************************/
	Protocol();

	/*************************************************************************************
	 * Destructor.
	 *************************************************************************************/
	virtual ~Protocol();

	/*************************************************************************************
	 * Makes the socket and sets the value of sock to be the socket descriptor
	 *************************************************************************************/
	void makeSocket();

	/*************************************************************************************
	 * Closes the socket
	 *************************************************************************************/
	void closeConnection();

	/*************************************************************************************
	 * Sends the given string to the client, using the given client socket
	 *************************************************************************************/
	virtual void sendData(const std::string& d, int cSock) { }

	/*************************************************************************************
	 * Receives a string sent from the client. Returns the string received.
	 *************************************************************************************/
	virtual std::string receiveData(int cSock) { return ""; }

	/*************************************************************************************
	 * Connects to the socket by using the bind() function.
	 *************************************************************************************/
	virtual void connectToSocket() { }

	/*************************************************************************************
	 * Waits and listens for a client to connect.
	 *************************************************************************************/
	virtual void listenForClient() { }

	/*************************************************************************************
	 * Accepts the connection from the client. Returns the client socket descriptor.
	 *************************************************************************************/
	virtual int acceptClient() { return -1; }

	/*************************************************************************************
	 * Makes a new thread to handle interactions with the newly connected client.
	 *************************************************************************************/
	virtual void makeNewThread(int c_sock) { }
};

#endif /* PROTOCOL_HPP_ */
