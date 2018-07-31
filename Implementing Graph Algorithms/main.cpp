/*
 * main.cpp
 *
 *  Created on: Dec 7, 2017
 *      Author: cal
 */

#include "Definitions.h"
#include <iostream>
#include <fstream>
#include "Manager.h"

int main(int argc, char* argv[]) {

	std::string iFile = "input.txt";
	Manager* m = new Manager();
	m->readFile(iFile);

	AlgorithmBase* algo = m->getAlgo();
	Board* board = m->getBoard();

	std::string path = algo->compute(board);
	std::fstream ofile ("output.txt", std::ios::in | std::ios::out | std::ios::trunc);
	if (ofile.is_open()) {
		ofile << path;
		ofile.close();
	} else {
		std::cout << "ERROR opening output file" << std::endl;
	}
	ofile.close();

	delete m;
}



