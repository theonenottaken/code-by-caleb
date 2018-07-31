#include "definitions.h"
#include "Value.h"

/* These are the implementations of the three non-class functions */

/*
 * Returns the maximum of the two given Values
 */
Value max(Value v1, Value v2) {
	if (v1 < v2)
		return v2;
	else
		return v1;
}

/*
 * Returns the minimum of the two given Values
 */
Value min(Value v1, Value v2) {
	if (v1 < v2)
		return v1;
	else
		return v2;
}

/*
 * Returns the opponent color of p. (If black, then white. If white, then black.)
 */
char opponent(char p) {
	if (p == WHITE)
		return BLACK;
	else
		return WHITE;
}
