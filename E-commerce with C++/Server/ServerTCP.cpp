
/*******************************************************************************************
 * Student Name: Caleb Shere Benjamin Wexler
 * Exercise Name: Targil 5
 * File Description: ServerTCP.cpp
 *******************************************************************************************/

#include "ServerTCP.hpp"
#include <iostream>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include "System.hpp"
#include "Protocol.hpp"

/********************************************************************************************
 * This is a class to store all of the information (Protocol and client socket) that needs
 * to be passed to the doAConnection function when each thread starts.
 ********************************************************************************************/
class Connection {
public:
	int clientSock;
	Protocol* proto;
	Connection(Protocol* p, int cs) {
		clientSock = cs;
		proto = p;
	}
};

/******************************************************************************************
 * Prototype of the function to be passed to pthread_create(). See below.
 ******************************************************************************************/
void* doAConnection(void* conn);

/******************************************************************************************
 * Constructor. Makes a new ServerTCP with the given type and port number. Also calls
 * constructors of parent classes.
 ******************************************************************************************/
ServerTCP::ServerTCP(int p) {
	type = TCP_CONN;
	port = p;
}

/******************************************************************************************
 * Destructor.
 ******************************************************************************************/
ServerTCP::~ServerTCP() {
	// TODO Auto-generated destructor stub
}

/******************************************************************************************
 * Binds to the socket, given by sock member.
 ******************************************************************************************/
void ServerTCP :: connectToSocket() {
	memset(&sin, 0, sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = INADDR_ANY;
	sin.sin_port = htons(port);

	if (bind(sock, (struct sockaddr *) &sin, sizeof(sin)) < 0) {
		perror("error binding socket");
	}
}

/******************************************************************************************
 * Waits and listens for a client to connect.
 ******************************************************************************************/
void ServerTCP :: listenForClient() {
	if (listen(sock, 5) < 0) {
		perror("error listening to a socket");
	}
}

/******************************************************************************************
 * Accepts the client, and returns the client's socket descriptor.
 ******************************************************************************************/
int ServerTCP :: acceptClient() {
	struct sockaddr_in client_sin;
	unsigned int addr_len = sizeof(client_sin);
	int c_sock = accept(sock, (struct sockaddr *) &client_sin,  &addr_len);

	if (c_sock < 0) {
		perror("error accepting client");
	}
	return c_sock;
}

/******************************************************************************************
 * Makes a new thread to handle the interactions with the newly connected client. The
 * starting point of each thread will be the doAConnection function.
 ******************************************************************************************/
void ServerTCP :: makeNewThread(int c_sock) {
	pthread_t thread_id;
	Connection* conn = new Connection(this, c_sock);
	if (pthread_create(&thread_id, NULL, doAConnection, (void*) conn) != 0) {
		perror("failed to create thread");
	}
}

/******************************************************************************************
 * Every thread starts at this function. It gets the one instance of the System
 * (using Singleton) and calls System::start() with this connection protocol and the client
 * socket descriptor that the makeNewThread function received.
 ******************************************************************************************/
void* doAConnection(void* conn) {
	System* s = System::getInstance();
	Connection* c = (Connection*) conn;
	s->start(c->proto, c->clientSock);
	return NULL;
}
