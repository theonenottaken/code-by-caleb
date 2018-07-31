/*
 * Cluster.h
 *
 *  Created on: Jan 25, 2018
 *      Author: cal
 */

#ifndef CLUSTER_H_
#define CLUSTER_H_

#include <vector>
#include "Point.h"

class Cluster {
private:
	std::vector<Point> points;
public:
	Cluster(Point p);
	void addPoint(Point p);
	std::vector<Point> getPoints();
	bool containsPoint(Point& p);
};

#endif /* CLUSTER_H_ */
