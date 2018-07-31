/*
 * Board.cpp
 *
 *  Created on: Dec 26, 2017
 *      Author: cal
 */

#include "Board.h"

/*
 * Constructor. b is a pointer to a char matrix.
 */
Board::Board(char** b) {
	board = b;
}

/*
 * Copy constructor (performs a deep copy). Boards are copied many times in the program, as each Node
 * stores its own copy representing the current state at that Node.
 */
Board::Board(const Board& other) {
	this->board = new char*[ROWS];
	for (int i = 0; i < ROWS; i++) {
		this->board[i] = new char[COLS];
	}

	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLS; j++) {
			this->board[i][j] = other.board[i][j];
		}
	}
}

/*
 * Destructor. The Board object is responsible the dynamically allocated char matrix.
 */
Board::~Board() {
	for (int i = 0; i < ROWS; i++) {
		delete board[i];
	}
	delete board;
}

/*
 * Determines whether there are no more empty spots on the board. This function tells the minimax algorithm
 * when it should stop recursing.
 */
bool Board::isFull() {
	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLS; j++) {
			if (board[i][j] == EMPTY) {
				return false;
			}
		}
	}
	return true;
}

/*
 * Finds and returns all of the playable spots in the current board. A playable spot is an empty spot
 * that is adjacent to a non-empty spot.
 */
std::vector<Loc> Board::playableSpots() {
	int r[8] = { 0, -1, -1, -1, 0, 1, 1, 1 };
	int c[8] = { 1, 1, 0, -1, -1, -1, 0, 1 };
	std::vector<Loc> spots;
	// iterate over rows
	for (int i = 0; i < ROWS; i++) {
		// iterate over columns
		for (int j = 0; j < COLS; j++) {
			if (board[i][j] == EMPTY) {
				Loc place(i, j);
				//iterate over neighbors to see if it is adjacent to another piece
				for (int k = 0; k < 8; k++) {
					Loc neigh = place + Loc(r[k], c[k]);
					if (inBoard(neigh)
							&& (board[neigh.row][neigh.col] != EMPTY)) {
						spots.push_back(place);
						break;
					}
				}
			}
		}
	}
	return spots;
}

/*
 * Updates the board, given the latest move by player.
 */
void Board::update(Loc move, char player) {
	board[move.row][move.col] = player;
	Loc next = move;
	Loc dirs[8] = { Loc(0, 1), Loc(-1, 1), Loc(-1, 0), Loc(-1, -1), Loc(0, -1),
			Loc(1, -1), Loc(1, 0), Loc(1, 1) };
	std::vector<Loc> toChange;
	for (int i = 0; i < 8; i++) {
		next = next + dirs[i]; // move one spot ahead in the current direction
		while (inBoard(next) && board[next.row][next.col] == opponent(player)) { // opponent function in functions.cpp
			toChange.push_back(next);
			next = next + dirs[i];
		}
		/*
		 * after reaching the end of the opposing player's pieces, make sure
		 * we are now at a piece belonging to the current player. If so, that means
		 * we change the color of the opposing pieces that were in betweeen.
		 */
		if (inBoard(next) && board[next.row][next.col] == player) {
			for (unsigned int j = 0; j < toChange.size(); j++) {
				Loc changer = toChange[j];
				board[changer.row][changer.col] = player;
			}
		}
		toChange.clear();
		next = move;
	}
}

/*
 * Returns whether the given location is inside the board.
 */
bool Board::inBoard(Loc loc) {
	if (loc.row >= 0 && loc.row < ROWS && loc.col >= 0 && loc.col < COLS)
		return true;
	else
		return false;
}

/*
 * Returns the winner of the game by seeing which color has more pieces. The function assumes that the
 * board is full.
 */
char Board::getWinner() {
	if (numOfColor(BLACK) > numOfColor(WHITE))
		return BLACK;
	else
		return WHITE;
}

/*
 * Returns the number of pieces belonging to the given color on the board
 */
int Board::numOfColor(char c) {
	int num = 0;
	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLS; j++) {
			if (board[i][j] == c)
				num++;
		}
	}
	return num;
}

/*
 * Returns the number of pieces belonging to the given color on the edges of the board
 */
int Board::numOnEdge(char c) {
	int num = 0;
	//top
	for (int j = 0; j < COLS; j++) {
		if (board[TOP_EDGE][j] == c)
			num++;
	}
	//right edge. Avoid counting the corner twice.
	for (int i = 1; i < ROWS - 1; i++) {
		if (board[i][RIGHT_EDGE] == c)
			num++;
	}
	//bottom
	for (int j = 0; j < COLS; j++) {
		if (board[BOTTOM_EDGE][j] == c)
			num++;
	}
	//left edge. Avoid counting the corner twice.
	for (int i = 1; i < ROWS - 1; i++) {
		if (board[i][LEFT_EDGE] == c)
			num++;
	}
	return num;
}
