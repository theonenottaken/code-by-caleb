/*
 * NodeAStar.cpp
 *
 *  Created on: Dec 13, 2017
 *      Author: cal
 */

#include "Node_AStar.h"

/*
 * Constructor
 */
Node_AStar::Node_AStar(Node* n, int g, int f) {
	node = n;
	this->g = g;
	this->f = f;
}

/*
 * Destructor
 */
Node_AStar::~Node_AStar() {
	if (node != NULL) {
		delete node;
	}
}

/*
 * Getter for Node object
 */
Node* Node_AStar::getNode() {
	return node;
}

/*
 * Getter for g
 */
int Node_AStar::getG() {
	return g;
}

/*
 * Getter for f
 */
int Node_AStar::getF() {
	return f;
}
