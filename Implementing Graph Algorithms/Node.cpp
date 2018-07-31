/*
 * Node.cpp
 *
 *  Created on: Dec 10, 2017
 *      Author: cal
 */

#include "Node.h"

/*
 * Constructor
 */
Node::Node(coord st, Node* p, std::string op, bool pass, char c){
	this->state = st;
	this->parent = p;
	this->op = op;
	passable = pass;
	character = c;
}

/*
 * Destructor
 */
Node::~Node() {
}

/*
 * Getter for parent node
 */
Node* Node::getParent() {
	return parent;
}

/*
 * Getter for operator string
 */
std::string Node::getOp() {
	return op;
}

/*
 * Getter for state coord
 */
coord Node::getState() {
	return state;
}

/*
 * Getter for passable boolean
 */
bool Node::isPassable() {
	return passable;
}

/*
 * Setter for passable boolean
 */
void Node::setPassable(bool b) {
	passable = b;
}

/*
 * Getter for cost. The cost is calculated according to the character in the map.
 */
int Node::getCost() {
	int cost;
	if (character == SOURCE || character == GOAL) {
		cost = 0;
	} else if (character == PAVED) {
		cost = PAVE_COST;
	} else if (character == NOT_PAVED) {
		cost = UNPAVE_COST;
	} else if (character == HILL) {
		cost = HILL_COST;
	} else { // type == WATER
		cost = WATER_COST;
	}
	return cost;
}
