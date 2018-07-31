/*
 * BoardMaker.cpp
 *
 *  Created on: Dec 7, 2017
 *      Author: cal
 */

#include "Definitions.h"
#include <fstream>
#include <string>
#include <stdlib.h>
#include "Manager.h"

/*
 * Constructor
 */
Manager::Manager() {
	algo = NULL;
	board = NULL;
}

/*
 * Destructor
 */
Manager::~Manager() {
	if (algo)
		delete algo;
	if (board)
		delete board;
}

/*
 * Getter for algorithm object
 */
AlgorithmBase* Manager::getAlgo() {
	return algo;
}

/*
 * Getter for Board object
 */
Board* Manager::getBoard() {
	return board;
}

/*
 * Reads the input file and appropriately initializes algorithm and board objects
 */
void Manager::readFile(std::string file) {

	std::ifstream ifile (file.c_str(), std::ios::in);
	std::string algo_line;
	std::string size;
	if (!ifile.is_open()){
		std::cout << "ERROR: could not open file " << file;
		return;
	}

	// read first line, initialize algo object
	ifile >> algo_line;
	if (algo_line == "IDS") {
			this->algo = new IDSAlgo();
	} else if (algo_line == "A*") {
		this->algo = new AStarAlgo();
	}

	// read size of board, allocate memory for board
	ifile >> size;
	int size_int = atoi(size.c_str());
	char** board = new char*[size_int];
	for (int i = 0; i < size_int; i++) {
		board[i] = new char[size_int];
	}

	// read rest of file, fill board
	char currChar;
	int i = 0;
	int j;
	while (i < size_int) {
		j = 0;
		while (j < size_int) {
			ifile >> currChar;
			if (currChar != NEWLINE) {
				board[i][j] = currChar;
				j++;
			}
		}
		if (currChar != NEWLINE) {
			i++;
		}
	}

	/* Initialize Board object.
	 * To make the Board class more general, I had it receive the source and goal locations. But for the
	 *  purposes of this targil, I simply initialize the source and goal locations here as outlined in the
	 *  instructions.
	 */
	coord source;
	source.row = 0;
	source.col = 0;
	coord goal;
	goal.row = size_int - 1;
	goal.col = size_int - 1;
	this->board = new Board(board, size_int, source, goal);

	ifile.close();
}
