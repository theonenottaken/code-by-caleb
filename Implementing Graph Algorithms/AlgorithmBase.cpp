
// AlgorithmBase.cpp

#include <sstream>
#include "AlgorithmBase.h"

/*
 * Constructor
 */
AlgorithmBase::AlgorithmBase() {
	board = NULL;
}

/*
 * Converts a coord to a string representation, for the purpose of being used in the hash map.
 */
std::string AlgorithmBase::coordToString(coord c) {
	std::stringstream ss;
	ss << c.row;
	std::string row = ss.str();
	clear_stream(ss);
	ss << c.col;
	std::string col = ss.str();
	// no need to clear stream because it's about to go out of scope
	return row + "-" + col;
}

/*
 * Clears the stringstream so that it can be used again without hiccups.
 */
void AlgorithmBase::clear_stream(std::stringstream& ss) {
	ss.str(std::string());
	ss.clear();
}

/*
 * Generates the string representation of the solution path, given the solution Node sol.
 * sol will always either be a Node storing the location of the goal or be NULL if there was
 * no solution path available.
 */
std::string AlgorithmBase::generate_path(Node* sol) {
	std::stringstream ss;
	std::string path;
	if (sol != NULL) {
		path = op_path(sol);
		path = path.substr(1); // slice off the preceding '-'
		int cost = path_cost(sol);
		ss << cost;
		path = path + " " + ss.str();
		// no need to clear stream because it's about to go out of scope.
	} else {
		path = "no path";
	}
	return path;
}

/*
 * A recursive function that gets the string of operators that were performed from the first node to the given
 * node. The function that calls this function, generate_path(Node*) checks if the given node is NULL, so there
 * is no need to do it here.
 */
std::string AlgorithmBase::op_path(Node* n) {
	Node* np = n->getParent();
	if (np == NULL) {
		return "";
	} else {
		return op_path(np) + "-" + n->getOp();
	}
}

/*
 * Similar to op_path, this recursive function computes the total cost of the path to the given node.
 * The function that calls this function, generate_path(Node*) checks if the given node is NULL, so there
 * is no need to do it here.
 */
int AlgorithmBase::path_cost(Node* n) {
	Node* np = n->getParent();
	if (np == NULL) {
		return 0;
	} else {
		int c = n->getCost();
		return c + path_cost(np);
	}
}

/*
 * Cpp here, so we have to free memory. This function just frees the Nodes on the solution path.
 * The other Nodes generated in the program are freed in other places.
 */
void AlgorithmBase::delete_node_path(Node* n) {
	if (n == NULL)
		return;
	else {
		Node* np = n->getParent();
		delete n;
		if (np == NULL) {
			return;
		} else {
			delete_node_path(np);
		}
	}
}
