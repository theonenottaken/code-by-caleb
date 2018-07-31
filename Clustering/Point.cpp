/*
 * Point.cpp
 *
 *  Created on: Jan 25, 2018
 *      Author: cal
 */

#include "Point.h"
#include <math.h>

Point::Point(int x, int y) {
	this->x = x;
	this->y = y;
}

double Point::distance(const Point& other) {
	return sqrt(pow((this->y - other.y), 2) + pow((this->x - other.x), 2));
}

int Point::getX() {
	return x;
}

int Point::getY() {
	return y;
}

bool Point::operator==(const Point& other) {
	return (this->x == other.x && this->y == other.y);
}
