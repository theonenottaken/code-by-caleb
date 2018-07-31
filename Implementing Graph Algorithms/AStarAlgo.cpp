
// AStarAlgo.cpp

#include "AStarAlgo.h"
#include <sstream>

/*
 * Constructor
 */
AStarAlgo::AStarAlgo() : AlgorithmBase() {}

/*
 * Destructor
 */
AStarAlgo::~AStarAlgo() {}

/*
 * This function receives a pointer to the current execution's Board object and returns
 * the solution string to be printed in output.txt.
 */
std::string AStarAlgo::compute(const Board* b) {

	this->board = b;
	initHash();
	coord start = board->getSource();
	coord goal = board->getGoal();

	// initialize start node with null parent, empty operator string, passable=true, and character 'S'
	Node* node = new Node(start, NULL, "", true, SOURCE);
	// initialize f and g to be 0
	Node_AStar* start_node = new Node_AStar(node, 0, 0);

	open_list.push_back(start_node); // put the start node in the open list

	Node* sol = AStar(start_node, goal);

	std::string path = generate_path(sol);
	delete_AStar_nodes();
	return path;
}

/*
 * This function runs the A* algorithm. Finds the optimal path from the start node to goal.
 */
Node* AStarAlgo::AStar(Node_AStar* src, coord goal) {

	Node_AStar* node;
	while (!open_list.empty()) {
		node = getLowestF();
		std::vector<Node*> neighbors = getAdjList(node->getNode());
		for (unsigned int i = 0; i < neighbors.size(); i++) {
			Node* n = neighbors[i];
			if (n->getState() == goal) {
				return neighbors[i];
			}
			int g = n->getCost() + node->getG();
			int h = computeH(n->getState(), goal);
			int f = g + h;
			std::string str = coordToString(n->getState());
			// Only make a new node if a node at the same location and with lower f does not
			// already exist in the open list or closed list.
			if (!(lowerF_at_pos(n->getState(), f)
					|| (this->closed_hash[str] != NULL
							&& this->closed_hash[str]->getF() < f))) {

				Node_AStar* aNode = new Node_AStar(n, g, f);
				open_list.push_back(aNode);

			} else {
				delete n;
			}
		}
		// this node is now closed
		this->closed_hash[coordToString(node->getNode()->getState())] = node;
	}
	// if goal not found, return NULL
	return NULL;
}

/*
 * Initializes the hash map, which acts as a closed list. It hashes string representations of coords to
 * Node_AStar pointers. Throughout the program, the pointer at a certain coord is only replaced if the
 * replacement node has a lower f value.
 */
void AStarAlgo::initHash() {
	int size = this->board->getSize();
	coord c;
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			c.row = i;
			c.col = j;
			std::string str = coordToString(c);
			// initialize all values to NULL, indicating an empty "closed list."
			this->closed_hash.insert(
					std::pair<std::string, Node_AStar*>(str, NULL));
		}
	}
}

/*
 * Generates and returns a vector of legitimate neighbors to the current node
 */
std::vector<Node*> AStarAlgo::getAdjList(Node* node) {
	int r[8] = { 0, 1, 1, 1, 0, -1, -1, -1 }; // row changes
	int c[8] = { 1, 1, 0, -1, -1, -1, 0, 1 }; // column changes
	std::string ops[8] = { "R", "RD", "D", "LD", "L", "LU", "U", "RU" }; // operators

	std::vector<Node> v;
	coord state = node->getState();
	std::string op = node->getOp();
	char** boardMx = this->board->getMatrix();

	for (int i = 0; i < 8; i++) {
		coord co;
		co.row = state.row + r[i];
		co.col = state.col + c[i];
		// check if row and column is within the board boundaries
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
		if (boardMx[c.row][c.col] == WATER) {
			// if tile is located NOT on a diagonal...
			if (c.row == state.row || c.col == state.col) {
				// mark as impassable the "next" and "previous" tiles
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
 * Get the node in open list with lowest f value. Removes said node from the list.
 */
Node_AStar* AStarAlgo::getLowestF() {
	Node_AStar* lowestF = NULL;
	std::list<Node_AStar*>::iterator i;
	for (i = open_list.begin(); i != open_list.end(); i++) {
		if (lowestF == NULL || (*i)->getF() < lowestF->getF()) {
			lowestF = *i;
		}
	}
	open_list.remove(lowestF);
	return lowestF;
}

/*
 * Compute h, according to the instructed heuristic
 */
int AStarAlgo::computeH(coord c, coord goal) {
	return std::max(goal.row - c.row, goal.col - c.col);
}

/*
 * Deletes all remaining AStar_Nodes. Each AStar_Node in turn deletes the regular node that it holds.
 */
void AStarAlgo::delete_AStar_nodes() {
	std::map<std::string, Node_AStar*>::iterator i;
	for (i = closed_hash.begin(); i != closed_hash.end(); i++) {
		if (i->second != NULL) {
			delete i->second;
		}
	}

	std::list<Node_AStar*>::iterator i2;
	for (i2 = open_list.begin(); i2 != open_list.end(); i2++) {
		if ((*i2) != NULL) {
			delete *i2;
		}
	}
}

/*
 * Checks if a node at the given location with a lower f value exists in the open list
 */
bool AStarAlgo::lowerF_at_pos(coord c, int f) {
	std::list<Node_AStar*>::iterator i;
	for (i = open_list.begin(); i != open_list.end(); i++) {
		if ((*i)->getNode()->getState() == c) {
			if ((*i)->getF() < f) {
				return true;
			}
		}
	}
	return false;
}
