/*
 * Data.h
 *
 *  Created on: Jan 25, 2018
 *      Author: cal
 */

#ifndef DATA_H_
#define DATA_H_

#include <vector>
#include "Point.h"

class Data {
private:
	int type;
	int clust_num;
	std::vector<Point> points;
public:
	Data(int t, int cn, std::vector<Point> pts);
	int getType();
	int getNumberOfClusters();
	std::vector<Point> getPoints();
};

#endif /* DATA_H_ */
