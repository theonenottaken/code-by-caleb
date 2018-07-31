/*
 * Value.h
 *
 *  Created on: Dec 26, 2017
 *      Author: cal
 */

#ifndef VALUE_H_
#define VALUE_H_

#include <string>
#include "definitions.h"

/*
 * This class represents a value, like a number, only this value can also be positive or negative infinity.
 * This way, I can perform comparisons throughout the program using infinity.
 */
class Value {
private:
	bool pos_inf;
	bool neg_inf;
	int val;

public:
	Value(int);
	Value(std::string);
	bool operator<(const Value& other) const;
	bool operator ==(const Value& other) const;
};

#endif /* VALUE_H_ */
