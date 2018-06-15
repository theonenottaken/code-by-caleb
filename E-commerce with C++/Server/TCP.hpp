
/*******************************************************************************************
 * Student Name: Caleb Shere Benjmin Wexler
 * Exercise Name: Targil 5
 * File Description: TCP.hpp
 *******************************************************************************************/

#ifndef TCP_HPP_
#define TCP_HPP_

#include "Protocol.hpp"
#include <iostream>

class TCP : public Protocol {
protected:
	int client_sock;
public:
	/***********************************************************************
	 * Constructor.
	 ***********************************************************************/
	TCP();

	/***********************************************************************
	 * Destructor.
	 ***********************************************************************/
	virtual ~TCP();

	/***********************************************************************
	 * Sends the given string to the client socket given by the parameter
	 * cSocket, which is the client socket descriptor.
	 ***********************************************************************/
	void sendData(const std::string& data, int cSocket);

	/***********************************************************************
	 * Receives a string from the given client socket descriptor, sent by
	 * by the client. Returns the received string.
	 ***********************************************************************/
	std::string receiveData(int cSocket);
};

#endif /* TCP_HPP_ */
