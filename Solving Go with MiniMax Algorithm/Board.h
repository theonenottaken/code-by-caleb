
#ifndef BOARD_H_
#define BOARD_H_

#include <vector>
#include "Loc.h"
#include "definitions.h"

/*
 * This class contains the board - that is, a char matrix representing the state of the game. It also
 * contains all of the gameplay logic and any functions that are executed exclusively on the board data.
 */
class Board {
private:
	char** board;
	bool inBoard(Loc l);
public:
	Board(char** b);
	Board(const Board& other);
	~Board();
	bool isFull();
	std::vector<Loc> playableSpots();
	void update(Loc move, char player);
	int numOfColor(char c);
	int numOnEdge(char c);
	char getWinner();
};

#endif /* BOARD_H_ */
