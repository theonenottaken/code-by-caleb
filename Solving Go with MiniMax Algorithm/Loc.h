/*
 * Loc.h
 *
 *  Created on: Dec 26, 2017
 *      Author: cal
 */

#ifndef LOC_H_
#define LOC_H_

/*
 * This class usually represents a location on the board. However, in Board::update(Loc, char), it also
 * represents a direction to move on the board.
 */
class Loc {
public:
	int row;
	int col;
	Loc(int r, int c);
	Loc operator+(const Loc& other) const;
};

#endif /* LOC_H_ */
