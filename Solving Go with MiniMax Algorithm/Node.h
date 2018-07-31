/*
 * Node.h
 *
 *  Created on: Dec 26, 2017
 *      Author: cal
 */

#ifndef NODE_H_
#define NODE_H_

#include "definitions.h"
#include "Loc.h"
#include "Value.h"
#include "Board.h"

/*
 * This class represents a Node in the execution of the minimax algorithm. Each node holds its own Board object,
 * which represents the current state at this node. Each node also holds the current player so that the minimax
 * function knows whether to maximize or minimize. And lastMove is needed so that the choose_help function in
 * MiniMax_Game can determine the move location that led to the generation of this Node (in case it is the optimal
 * move to make).
 */
class Node {
private:
	Board state;
	char player;
	Loc* lastMove;
public:
	Node(const Board& b, char p, Loc m);
	Node(const Board& b, char p);
	Node(const Node& other);
	~Node();
	Board& getState();
	char getPlayer();
	Value heuristic();
	Loc getLastMove();
};

#endif /* NODE_H_ */
