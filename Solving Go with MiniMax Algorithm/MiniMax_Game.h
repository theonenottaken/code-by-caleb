/*
 * MiniMaxGame.h
 *
 *  Created on: Dec 27, 2017
 *      Author: cal
 */

#ifndef MINIMAX_GAME_H_
#define MINIMAX_GAME_H_

#include <vector>
#include "Board.h"
#include "Value.h"
#include "Node.h"

typedef Value (*min_or_max) (Value, Value);

/*
 * This class takes care of running the minimax algorithm for both sides on a given board.
 */
class MiniMax_Game {
private:
	std::vector<Node> generateChildren(Node);
	Value minimax(Node n, int depth);
	Value minimax_help(Node n, int depth, Value def, min_or_max f);
	Loc chooseBestMove(Node n, int depth);
	Loc choose_help(Node n, int depth, Value def, min_or_max f);
public:
	char predictWinner(Board& b);
};

#endif /* MINIMAX_GAME_H_ */
