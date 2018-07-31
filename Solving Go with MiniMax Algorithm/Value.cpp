/*
 * Value.cpp
 *
 *  Created on: Dec 26, 2017
 *      Author: cal
 */

#include "Value.h"

/*
 * Constructor for when the value is just a number.
 */
Value::Value(int v) {
	val = v;
	pos_inf = false;
	neg_inf = false;
}

/*
 * Constructor for when the value is positive or negative infinity.
 */
Value::Value(std::string str) {
	if (str == POSITIVE_INF) {
		pos_inf = true;
		neg_inf = false;
	} else if (str == NEGATIVE_INF) {
		neg_inf = true;
		pos_inf = false;
	}
	val = 0; // just to get rid of the warning that I didn't initialize val
}

/*
 * Overrides the < operator. Allows for comparison with infinity.
 */
bool Value::operator<(const Value& other) const {
	if (this->pos_inf || other.neg_inf) {
		return false;
	} else if (this->neg_inf || other.pos_inf) {
		return true;
	} else {
		return (this->val < other.val);
	}
}

/*
 * Overrides the == operator. Positive infinity is considered equal to positive infinity, and so too
 * with negative infinity.
 */
bool Value::operator==(const Value& other) const {
	if (this->pos_inf || other.pos_inf)
		return (this->pos_inf == other.pos_inf);
	else if (this->neg_inf || other.neg_inf)
		return this->neg_inf == other.neg_inf;
	else
		return this->val == other.val;
}
