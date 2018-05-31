
/*******************************************************************************************
 * Student Name: Caleb Shere Benjamin Wexler
 * Exercise Name: Targil 5
 * File Description: AgeComparer.hpp
 *******************************************************************************************/

#ifndef AGECOMPARER_H_
#define AGECOMPARER_H_

#include "Professional.hpp"

class AgeComparer {
public:
	/***********************************************************************************************
	 * A comparator function. It compares two Professionals according to their ages. If the first
	 * professional's age is greater than the second professional's age, the function returns true,
	 * meaning that the first professional should come before the second in the sorted list. Else,
	 * it returns false, meaning that the second should come before the first.
	 ***********************************************************************************************/
	bool operator()(const Professional* first, const Professional* second) {
		std::string age1 = *(first->getAge());
		std::string age2 = *(second->getAge());
		//A number with more number places is obviously greater than one with fewer number places.
		if (age1.length() > age2.length())
			return true;
		else if (age2.length() > age1.length())
			return false;
		else { // The lengths are equal...
			unsigned int i;
			for (i = 0; i < age1.length() && i < age2.length(); i++) {
				if (age1[i] > age2[i])
					return true;
				else if (age2[i] > age1[i])
					return false;
			}
		}
		return true; // If you got to this point, the ages are equal so don't swap.
	}

	/**************************************************************************************************
	 * Constructor
	 **************************************************************************************************/
	AgeComparer() { }

	/**************************************************************************************************
	 * Destructor
	 **************************************************************************************************/
	virtual ~AgeComparer() { }
};

#endif /* AGECOMPARER_H_ */
