/*
 * Loc.cpp
 *
 *  Created on: Dec 26, 2017
 *      Author: cal
 */

#include "Loc.h"

/*
 * Constructor
 */
Loc::Loc(int r, int c) {
	row = r;
	col = c;
}

/*
 * When performing this operation, the Loc other is viewed as a direction to move in (move other.row
 * rows and other.col columns from this Loc)
 */
Loc Loc::operator+(const Loc& other) const {
	int row = this->row + other.row;
	int col = this->col + other.col;
	return Loc(row, col);
}
