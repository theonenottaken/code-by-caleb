
/* 89-210-05 2493276919 Caleb Shere */
/* 89-210-05 337955744  Benjamin Wexler */

#include <iostream>
#include <list>
#include <string>
#include "Genre.hpp"
#include "Movie.hpp"
#include "System.hpp"
#include "Protocol.hpp"
#include "ServerTCP.hpp"
#include <string.h>
#include <iostream>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>

/*********************************************************
 * Program Name: Targ5
 * The Operation: Provides a system for storing and
 * retrieving movies and cast members. The user inputs the 
 * information for movies and cast members into the system,
 * and the system stores the items in a structured format
 * that allows the user to manipulate and read the
 * information of each item, as well as the relationships
 * between movies and cast members.
 *********************************************************/
int main(int argc, char * argv[]) {
	if (argc < 2)
		return 1;

	char* portArg = argv[1];

	int port_num = 0;
	int numberPlace = 1;
	int i;
	for (i = strlen(portArg) - 1; i >= 0; i--) {
		int num = portArg[i] - 48; // Convert from ASCII value to decimal value
		port_num += numberPlace * num;
		numberPlace *= 10;
	}
	Protocol* conn = new ServerTCP(port_num);
	conn->makeSocket();
	conn->connectToSocket();

	// Stay running until a human being exits the window
	while (true) {
		conn->listenForClient();
		int c_sock = conn->acceptClient();
		conn->makeNewThread(c_sock);
	}
    conn->closeConnection();
    return 0;
}
