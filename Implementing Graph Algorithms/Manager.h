/*
 * FileReader.h
 *
 *  Created on: Dec 7, 2017
 *      Author: cal
 */

#ifndef MANAGER_H_
#define MANAGER_H_

#include "AStarAlgo.h"
#include "IDSAlgo.h"
#include "Board.h"

/*
 * The manager class essentially sets up everything so that the appropriate Algorithm object
 * can do its work. It reads the input file, gathers all necessary information, and stores pointers
 * to the two essential objects of the program - an AlgorithmBase object that executes the appropriate
 * algorithm, and a Board object that stores all the relevant information of the current execution's
 * board. It is also responsible for deleting these two objects.
 */
class Manager {
private:
	AlgorithmBase* algo;
	Board* board;
public:
	Manager();
	~Manager();
	void readFile(std::string file);
	AlgorithmBase* getAlgo();
	Board* getBoard();
};

#endif /* MANAGER_H_ */
