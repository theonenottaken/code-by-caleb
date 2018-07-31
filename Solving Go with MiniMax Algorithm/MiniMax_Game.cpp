/*
 * MiniMaxGame.cpp
 *
 *  Created on: Dec 27, 2017
 *      Author: cal
 */

#include "MiniMax_Game.h"
#include <iostream>

/*
 * Generates and returns the Node children of the given Node
 */
std::vector<Node> MiniMax_Game::generateChildren(Node n) {
	Board b(n.getState());
	std::vector<Loc> spots = b.playableSpots();
	std::vector<Node> children;
	for (unsigned int i = 0; i < spots.size(); i++) {
		b.update(spots[i], n.getPlayer());
		children.push_back(Node(b, opponent(n.getPlayer()), spots[i]));
	}
	return children;
}

/*
 * The minimax algorithm is executed by two functions: this one and minimax(Node, int) below.
 * The Value def is either positive and negative infinity and represents the default value to
 * assign to bestVal before we have recursively run on any of the children. The min_or_max f
 * is a function pointer to either min(Value, Value) or max(Value, Value) found in functions.cpp.
 */
Value MiniMax_Game::minimax_help(Node n, int depth, Value def, min_or_max f) {
	if (depth == 0 || n.getState().isFull()) {
		return n.heuristic();
	}
	std::vector<Node> children = generateChildren(n);
	Value bestVal = def;
	for (unsigned int i = 0; i < children.size(); i++) {
		Value v = minimax(children[i], depth - 1);
		bestVal = f(bestVal, v);
	}
	return bestVal;
}

/*
 * This function passes the correct arguments to minimax_help, based on whether the current player is
 * white or black.
 */
Value MiniMax_Game::minimax(Node n, int depth) {
	if (n.getPlayer() == BLACK)
		return minimax_help(n, depth, Value(NEGATIVE_INF), max);
	else
		return minimax_help(n, depth, Value(POSITIVE_INF), min);
}

/*
 * In order to choose the best move for a Node, we run the minimax algorithm on the Node's
 * children and choose the child that outputted the best value. The nature of the parameters here is
 * the same as in minimax_help.
 */
Loc MiniMax_Game::choose_help(Node n, int depth, Value def, min_or_max f) {
	std::vector<Node> moves = generateChildren(n);
	Value bestVal(def);
	Loc bestMove = moves[0].getLastMove();
	for (unsigned int i = 0; i < moves.size(); i++) {
		Value v = minimax(moves[i], depth - 1);
		Value val_copy = bestVal;
		bestVal = f(bestVal, v);
		// if bestVal was changed, update bestMove
		if (!(bestVal == val_copy))
			bestMove = moves[i].getLastMove();
	}
	return bestMove;
}

/*
 * This function passes the correct arguments to choose_help, based on whether the current player is white
 * or black.
 */
Loc MiniMax_Game::chooseBestMove(Node n, int depth) {
	if (n.getPlayer() == BLACK)
		return choose_help(n, depth, Value(NEGATIVE_INF), max);
	else
		return choose_help(n, depth, Value(POSITIVE_INF), min);
}

/*
 * Predicts the winner of the game, given the current board. It does not change the Board parameter.
 */
char MiniMax_Game::predictWinner(Board& b) {
	Board board(b);
	char player = BLACK; // Black starts
	while (!board.isFull()) {
		Node n = Node(board, player);
		Loc move = chooseBestMove(n, DEPTH);
		board.update(move, player);
		player = opponent(player); // opponent function found in functions.cpp
	}
	return board.getWinner();
}
