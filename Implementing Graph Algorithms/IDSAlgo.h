/*
 * IDSAlgo.h
 *
 *  Created on: Dec 7, 2017
 *      Author: cal
 */

#ifndef IDSALGO_H_
#define IDSALGO_H_

#include "AlgorithmBase.h"
#include <vector>
#include "Node.h"
#include <map>

/*
 * A class for the IDS algorithm. The key function is compute, which takes a board and returns the solution
 * path to be printed to output.txt. All the other functions are private functions called from the execution
 * of compute(Board*). It also inherits from AlgorithmBase and uses its Board* member and functions.
 */
class IDSAlgo: public  AlgorithmBase{
public:
	IDSAlgo();
	~IDSAlgo();
	std::string compute (const Board* b);

private:
	std::map<std::string, bool> hash;
	void initHash();
	Node* limitedDFS(Node* source, coord goal, int limit);
	Node* IDS(Node* src, coord goal, int max_depth);
	std::vector<Node*> generateAdjList(Node* node);
	void reset_hash();
	void clear_node_vector(std::vector<Node*>& v, int except = -1);
};

#endif /* IDSALGO_H_ */
