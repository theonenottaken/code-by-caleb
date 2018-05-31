/*
 * main.cpp
 *
 *  Created on: Dec 22, 2015
 *      Author: caleb
 */

#include "ClientTCP.hpp"
#include <string.h>
#include <iostream>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

int main(int argc, char * argv[]) {

	if (argc < 3)
		return 1;
	char* ipArg = argv[1];
	char* portArg = argv[2];

	int port_num = 0;
	int numberPlace = 1;
	int i;
	for (i = strlen(portArg) - 1; i >= 0; i--) {
		int num = portArg[i] - 48; // Convert from ASCII value to decimal value
		port_num += numberPlace * num;
		numberPlace *= 10;
	}
	Protocol* conn = new ClientTCP(ipArg, port_num);
	conn->makeSocket();
	conn->doConnection();

	std::string command_to;
	std::string command_from;
	while (command_to != "-1") {
		std::getline(std::cin, command_to);
		conn->sendData(command_to);
		if (command_to != "-1") {
			command_from = conn->receiveData();
			std::cout << command_from;
		}
	}
	conn->closeConnection();

	return 0;
}



