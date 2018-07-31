/*
 * IDSAlgo.cpp
 *
 *  Created on: Dec 7, 2017
 *      Author: cal
 */

#include "IDSAlgo.h"
#include <stdlib.h>
#include <string>
#include <sstream>

/*
 * Constructor
 */
IDSAlgo::IDSAlgo() : AlgorithmBase() {}

/*
 * Destructor
 */
IDSAlgo::~IDSAlgo() {}

/*
 * Initializes the hash map, which acts as a closed list. It maps string representations of coords to
 * boolean. A value of true indicates this node has already been visited on the current path (and shouldn't
 * be visited again). A value of false indicates otherwise.
 */
void IDSAlgo::initHash() {
	int size = board->getSize();
	coord c;
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			c.row = i;
			c.col = j;
			std::string str = coordToString(c);
			this->hash.insert(std::pair<std::string, bool>(str, false));
		}
	}
}

/*
 * This function receives a pointer to the current execution's Board object and returns
 * the solution string to be printed in output.txt.
 */
std::string IDSAlgo::compute(const Board* b) {

	this->board = b;
	initHash();

	int size = board->getSize();
	int max_depth = size * size;
	coord start = board->getSource();
	coord goal = board->getGoal();

	Node* start_node = new Node(start, NULL, "", true, SOURCE);
	Node* sol = IDS(start_node, goal, max_depth);

	std::string path = generate_path(sol);

	delete_node_path(sol);
	return path;
}

/*
 * This is a helper function for the IDS algorithm. It runs a depth-first-search, but only up
 * to the given limit.
 */
Node* IDSAlgo::limitedDFS(Node* source, coord goal, int limit) {
	if (source->getState() == goal) {
		return source;
	}
	if (limit <= 0) {
		return NULL;
	}
	std::vector<Node*> v = generateAdjList(source);
	this->hash[coordToString(source->getState())] = true; // this coord has now been visited
	for (unsigned int i = 0; i < v.size(); i++) {
		Node* n = limitedDFS(v[i], goal, limit - 1);
		if (n != NULL) {
			// delete all nodes in the adjacency vector except for the node in the solution path
			clear_node_vector(v, i);
			return n;
		}
	}
	this->hash[coordToString(source->getState())] = false; // allow future paths to visit this node
	clear_node_vector(v); // if no solution found, clear the whole vector
	return NULL;
}

/*
 * This function executes the IDS algorithm
 */
Node* IDSAlgo::IDS(Node* src, coord goal, int max_depth) {
	for (int i = 0; i <= max_depth; i++) {
		reset_hash();
		Node* n = limitedDFS(src, goal, i);
		if (n != NULL) {
			return n;
		}
	}
	return NULL;
}

/*
 * Resets all values in the hash map to false, meaning that every node can be visited. Used in function
 * IDS between calls to limitedDFS
 */
void IDSAlgo::reset_hash() {
	std::map<std::string, bool>::iterator i;
	for (i = this->hash.begin(); i != hash.end(); ++i) {
		i->second = false;
	}
}

/*
 * Generates and returns a vector of legitimate neighbors to the current node
 */
std::vector<Node*> IDSAlgo::generateAdjList(Node* node) {

	int r[8] = { 0, 1, 1, 1, 0, -1, -1, -1 }; // row changes
	int c[8] = { 1, 1, 0, -1, -1, -1, 0, 1 }; // column changes
	std::string ops[8] = { "R", "RD", "D", "LD", "L", "LU", "U", "RU" };

	std::vector<Node> v;
	coord state = node->getState();
	std::string op = node->getOp();
	char** boardMx = this->board->getMatrix();

	for (int i = 0; i < 8; i++) {
		coord co;
		co.row = state.row + r[i];
		co.col = state.col + c[i];
		// if location is outside board boundaries...
		if (co.row < 0 || co.col < 0 || co.row > this->board->getSize() - 1
				|| co.col > this->board->getSize() - 1) {
			// this Node is a junk Node and will be deleted later. I do this because it makes it far easier
			// to later eliminate the proper tiles blocked by water
			Node n(co, node, ops[i], false, 'Z');
			v.push_back(n);
		} else {
			Node n(co, node, ops[i], true, boardMx[co.row][co.col]);
			v.push_back(n);
		}
	}

	// remove impassable tiles
	for (unsigned int i = 0; i < v.size(); i++) {
		if (!v[i].isPassable())
			continue;
		coord c = v[i].getState();
		// mark as impassable the tiles on the diagonal if a non-diagonal tile is water
		if (boardMx[c.row][c.col] == WATER) {
			if (c.row == state.row || c.col == state.col) {
				int prev;
				int next;
				prev = i - 1;
				if (prev < 0) {
					prev = v.size() - 1;
				}
				next = (i + 1) % v.size();
				v[prev].setPassable(false);
				v[next].setPassable(false);
			}
			v[i].setPassable(false);
			continue;
		}
		// do not revisit a node already visited on the current path
		if (this->hash[coordToString(c)] == true) {
			v[i].setPassable(false);
		}
	}

	// only keep passable tiles
	std::vector<Node*> v2;
	for (unsigned int i = 0; i < v.size(); i++) {
		if (v[i].isPassable()) {
			Node* n = new Node(v[i]);
			v2.push_back(n);
		}
	}
	return v2;
}

/*
 * deletes nodes in the node vector, except for the node at the given index.
 * If except is -1, then deletes all of the nodes
 */
void IDSAlgo::clear_node_vector(std::vector<Node*>& v, int except) {
	unsigned int exc;
	if (except == -1) {
		exc = v.size(); // a value that i will never be equal to
	} else {
		exc = except; // if not -1, then except is certainly a positive number
	}
	for (unsigned int i = 0; i < v.size(); i++) {
		if (i != exc) {
			if (v[i] != NULL) {
				delete v[i];
				v[i] = NULL;
			}
		}
	}
}
