/*
 * Node.cpp
 *
 *  Created on: Dec 26, 2017
 *      Author: cal
 */

#include "Node.h"

/*
 * Constructor. I use a pointer for lastMove so that I can set it to NULL for the first Node.
 */
Node::Node(const Board& b, char p, Loc m) :
		state(b), player(p) {
	lastMove = new Loc(m);
}

/*
 * Constructor, if lastMove should be NULL.
 */
Node::Node(const Board& b, char p) :
		state(b), player(p) {
	lastMove = NULL;
}

/*
 * Copy Constructor. A deep copy is needed for lastMove.
 */
Node::Node(const Node& other) : state(other.state), player(other.player) {
	if (other.lastMove != NULL)
		lastMove = new Loc(*(other.lastMove));
	else
		lastMove = NULL;
}

/*
 * Destructor. Deletes lastMove.
 */
Node::~Node() {
	delete lastMove;
}

/*
 * Returns the Node's state.
 */
Board& Node::getState() {
	return state;
}

/*
 * Return's player.
 */
char Node::getPlayer() {
	return player;
}

/*
 * Returns the last move that led to the current state
 */
Loc Node::getLastMove() {
	return *lastMove;
}

/*
 * Returns the node's heuristic. In the event that the minimax algorithm has reached a depth of 3
 * without the board becoming full, it computes an approximation as described in the instructions. Otherwise,
 * if the board is full, it returns positive or negative infinity based on the current player.
 *
 */
Value Node::heuristic() {
	Value val(0);
	if (state.isFull()) {
		char w = state.getWinner();
		if (w == BLACK)
			val = Value(POSITIVE_INF);
		else
			val = Value(NEGATIVE_INF);
	} else {
		int num = (state.numOfColor(BLACK) - state.numOfColor(WHITE))
				+ (state.numOnEdge(BLACK) - state.numOnEdge(WHITE));
		val = Value(num);
	}
	return val;
}
