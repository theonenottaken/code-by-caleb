/*
 * Point.h
 *
 *  Created on: Jan 25, 2018
 *      Author: cal
 */

#ifndef POINT_H_
#define POINT_H_

class Point {
private:
	int x;
	int y;
public:
	Point(int x, int y);
	double distance(const Point& other);
	bool operator==(const Point& other);
	int getX();
	int getY();
};

#endif /* POINT_H_ */
