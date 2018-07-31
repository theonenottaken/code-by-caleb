/*
 * Data.cpp
 *
 *  Created on: Jan 25, 2018
 *      Author: cal
 */

#include "Data.h"

Data::Data(int t, int cn, std::vector<Point> pts) : points(pts) {
	type = t;
	clust_num = cn;
}

int Data::getType() {
	return type;
}

int Data::getNumberOfClusters() {
	return clust_num;
}

std::vector<Point> Data::getPoints() {
	return points;
}

