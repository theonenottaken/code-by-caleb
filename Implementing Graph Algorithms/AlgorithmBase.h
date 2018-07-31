
// AlgorithmBase.h

#ifndef ALGORITHMBASE_H_
#define ALGORITHMBASE_H_

#include <iostream>
#include <vector>
#include "Board.h"
#include "Node.h"

/*
 * An abstract base class that both algorithms inherit from. It stores all members (a Board pointer)
 * and functions that will be used by both algorithm classes.
 */
class AlgorithmBase {
protected:
	const Board* board;
	std::string coordToString(coord c);
	void clear_stream(std::stringstream& ss);
	std::string generate_path(Node* n);
	std::string op_path(Node* n);
	int path_cost(Node* n);
	void delete_node_path(Node* n);
public:
	AlgorithmBase();

	/*
	 * Virtual destructor so that the child class destructors are also called. No need to free board
	 * here because it is freed by the Manager class.
	 */
	virtual ~AlgorithmBase() {}

	virtual std::string compute(const Board* b) = 0;
};

#endif /* ALGORITHMBASE_H_ */
