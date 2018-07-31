
#ifndef DEFINITIONS_H_
#define DEFINITIONS_H_

#define DEPTH 3
#define BLACK 'B'
#define WHITE 'W'
#define EMPTY 'E'
#define ROWS 5
#define COLS 5
#define TOP_EDGE 0
#define BOTTOM_EDGE 4
#define RIGHT_EDGE 4
#define LEFT_EDGE 0
#define POSITIVE_INF "pos inf"
#define NEGATIVE_INF "neg inf"
#define NEWLINE 10

class Value;

/*
 * These are 3 useful functions that it didn't make sense to put in any class
 */
Value max(Value v1, Value v2);
Value min(Value v1, Value v2);
char opponent(char p);

#endif /* DEFINITIONS_H_ */
