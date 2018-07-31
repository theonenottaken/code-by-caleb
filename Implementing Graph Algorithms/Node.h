/*
 * Node.h
 *
 *  Created on: Dec 10, 2017
 *      Author: cal
 */

#ifndef NODE_H_
#define NODE_H_

#include <string>
#include "Definitions.h"

/*
 * This class defines a node used in the IDS algorithm. The A* algorithm uses a class that is
 * an expansion on this class.
 */
class Node {
private:
	Node* parent;
	std::string op;
	coord state;
	bool passable;
	char character;
public:
	Node(coord st, Node* p, std::string op, bool pass, char c);
	~Node();
	Node* getParent();
	std::string getOp();
	coord getState();
	bool isPassable();
	void setPassable(bool b);
	void setCharacter(char c);
	int getCost();
};

#endif /* NODE_H_ */
