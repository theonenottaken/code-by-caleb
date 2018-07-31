/*
 * Board.h
 *
 *  Created on: Dec 7, 2017
 *      Author: cal
 */

#ifndef BOARD_H_
#define BOARD_H_

#include "Definitions.h"

/*
 * The purpose of the board class is to organize all of the information of the current problem's board
 * into one object. It consists of only members and getter functions.
 */
class Board {
private:
	char** board;
	int size;
	coord source;
	coord goal;

public:
	Board(char** b, int si, coord s, coord g);
	~Board();
	char** getMatrix() const;
	int getSize() const;
	coord getSource() const;
	coord getGoal() const;
};

#endif /* BOARD_H_ */
