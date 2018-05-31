
/*******************************************************************************************
 * Student Name: Caleb Shere Benjamin Wexler
 * Exercise Name: Targil 5
 * File Description: NumOfMoviesComp.hpp
 *******************************************************************************************/

#ifndef NUMOFMOVIESCOMP_H_
#define NUMOFMOVIESCOMP_H_

#include "Professional.hpp"

class NumOfMoviesComp {
public:
	/*************************************************************************************************
	 * A comparator function. It compares two Professionals according to the number of movies that
	 * they appear in. If the first professional appears in more movies than the second professional,
	 * then it returns true, meaning that the first Professional should come before the second in the
	 * sorted list. Else, it returns false, meaning that the second should come before the first.
	 *************************************************************************************************/
	bool operator()(const Professional* first, const Professional* second) {
		unsigned int size1 = first->getMovies()->size();
		unsigned int size2 = second->getMovies()->size();
		if (size1 > size2)
			return true;
		else
			return false;
	}
	/**************************************************************************************************
	 * Constructor
	 **************************************************************************************************/
	NumOfMoviesComp() { }
	/**************************************************************************************************
	 * Destructor
	 **************************************************************************************************/
	virtual ~NumOfMoviesComp() { }
};

#endif /* NUMOFMOVIESCOMP_H_ */
