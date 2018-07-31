/*
 * Definitions.h
 *
 *  Created on: Dec 7, 2017
 *      Author: cal
 */

#ifndef DEFINITIONS_H_
#define DEFINITIONS_H_

/*
 * This file contains all of the definitions I use, to avoid the use of "magic numbers."
 * It also contains the definition of struct coord, which represents a coordinate position
 * (row, col) on the board.
 */

#define SOURCE 'S'
#define PAVED 'R'
#define NOT_PAVED 'D'
#define HILL 'H'
#define WATER 'W'
#define GOAL 'G'
#define PAVE_COST 1
#define UNPAVE_COST 3
#define HILL_COST 10
#define WATER_COST -9999
#define NEWLINE 10
#define SURROUNDING_TILES 8

typedef struct coord {
	int row;
	int col;

	bool operator==(const coord& other) const {
		return row == other.row && col == other.col;
	}
} coord;

#endif /* DEFINITIONS_H_ */
