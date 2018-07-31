/*
 * NodeAStar.h
 *
 *  Created on: Dec 13, 2017
 *      Author: cal
 */

#ifndef NODE_ASTAR_H_
#define NODE_ASTAR_H_

#include "Node.h"

/*
 * This class defines a node that is used for the A* algorithm. It stores a regular Node object and
 * adds the fields g and f, which are used in the A* algo.
 */
class Node_AStar {
private:
	Node* node;
	int g;
	int f;
public:
	Node_AStar(Node* n, int g, int f);
	~Node_AStar();
	Node* getNode();
	int getG();
	int getF();
};

#endif /* NODE_ASTAR_H_ */
