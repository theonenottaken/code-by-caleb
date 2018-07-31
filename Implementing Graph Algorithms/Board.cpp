/*
 * Board.cpp
 *
 *  Created on: Dec 7, 2017
 *      Author: cal
 */

#include "Board.h"
/*
 * Constructor. Initializes members.
 */
Board::Board(char** b, int si, coord s, coord g) {
	board = b;
	size = si;
	source = s;
	goal = g;

}

/*
 * Destructor. Frees the character matrix stored in board.
 */
Board::~Board() {
	for (int i = 0; i < size; i++) {
		delete board[i];
	}
	delete board;
}

/*
 * Getter for source coord
 */
coord Board::getSource() const {
	return source;
}

/*
 * Getter for goal coord
 */
coord Board::getGoal() const {
	return goal;
}

/*
 * Getter for size (size == number of rows == number of columns)
 */
int Board::getSize() const {
	return size;
}

/*
 * Getter for char matrix
 */
char** Board::getMatrix() const {
	return board;
}

