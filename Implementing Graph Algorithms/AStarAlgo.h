/*
 * AStarAlgo.h
 *
 *  Created on: Dec 7, 2017
 *      Author: cal
 */

#ifndef ASTARALGO_H_
#define ASTARALGO_H_

#include "AlgorithmBase.h"
#include <map>
#include <list>
#include "Node_AStar.h"

/*
 * A class for the A* algorithm. The key function is compute, which takes a board and returns the solution
 * path to be printed to output.txt. All the other functions are private functions called from the execution
 * of compute(Board*). It also inherits from AlgorithmBase and uses its Board* member and functions.
 */
class AStarAlgo: public AlgorithmBase {
public:
	AStarAlgo();
	virtual ~AStarAlgo();
	std::string compute(const Board* b);
private:
	std::list<Node_AStar*> open_list;
	std::map<std::string, Node_AStar*> closed_hash;
	void initHash();
	bool open_list_empty();
	Node* AStar(Node_AStar* src, coord goal);
	Node_AStar* getLowestF();
	std::vector<Node*> getAdjList(Node* node);
	int computeH(coord c, coord goal);
	void delete_AStar_nodes();
	bool lowerF_at_pos(coord c, int f);
};

#endif /* ASTARALGO_H_ */
