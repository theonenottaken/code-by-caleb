
/*******************************************************************************************
 * Student Name: Caleb Shere Benjamin Wexler
 * Exercise Name: Targi 5
 * File Description: IDComparer.hpp
 *******************************************************************************************/

#ifndef IDCOMPARER_H_
#define IDCOMPARER_H

#include "Professional.hpp"

class IDComparer {
public:
	/*******************************************************************************************
	 * A comparator function. Compares two Professionals according to their ID numbers. If the
	 * first professional's ID number is less than the second professional's ID number, the
	 * function returns true, meaning that the first professional should come before the second
	 * in the sorted list. Else, it returns false, meaning that the second should come before
	 * the first.
	 *******************************************************************************************/
	bool operator()(const Professional* first, const Professional* second) {
		std::string id1 = *(first->getID());
		std::string id2 = *(second->getID());
		unsigned int length1 = id1.length();
		unsigned int length2 = id2.length();
		unsigned int i;
		for (i = 0; i < length1 && i < length2; i++) {
			if (id1[i] < id2[i]) {
				return true;
			} else if (id2[i] < id1[i]) {
				return false;
			}
		}
		if (length1 < length2) // just in case there are ID numbers of different lengths
			return true;
		else
			return false;
	}

	/*********************************************************************************************
	 * Constructor
	 *********************************************************************************************/
	IDComparer() { }

	/*********************************************************************************************
	 * Destructor
	 *********************************************************************************************/
	virtual ~IDComparer() { }
};

#endif /* IDCOMPARER_H_ */
