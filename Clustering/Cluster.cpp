/*
 * Cluster.cpp
 *
 *  Created on: Jan 25, 2018
 *      Author: cal
 */

#include "Cluster.h"
#include <algorithm>

Cluster::Cluster(Point p) {
	points.push_back(p);
}

void Cluster::addPoint (Point p) {
	points.push_back(p);
}

std::vector<Point> Cluster::getPoints() {
	return points;
}

bool Cluster::containsPoint(Point& p) {
	return (std::find(points.begin(), points.end(), p) != points.end());
}

