
/*******************************************************************************************
 * Student Name: Caleb Shere Benjamin Wexler
 * Exercise Name: Targil 5
 * File Description: Movie.cpp
 *******************************************************************************************/

#include "Movie.hpp"
#include <sstream>
#include <iostream>
#include "AgeComparer.hpp"
#include "IDComparer.hpp"
#include "NumOfMoviesComp.hpp"
#define BY_ID 1
#define BY_AGE 2
#define BY_NUM_OF_MOVIES 3

/******************************************************************************************
 * Constructor. Creates a movie with the given information.
 ******************************************************************************************/
Movie :: Movie(const std::string& c, const std::string& t, const std::string& time,
               const std::string& year, const std::string& r, const std::string& summ) {
	code = c;
	title = t;
	runTime = time;
	yearOfRelease = year;
	rating = r;
	summary = summ;
    sortType = BY_ID; // default sort type.
}

/********************************************************************************************
 * Copy constructor. Creates a movie that is a copy of the parameter movie.
 ********************************************************************************************/
Movie :: Movie(const Movie& mov) {
	code = mov.code;
	title = mov.title;
	runTime = mov.runTime;
	yearOfRelease = mov.yearOfRelease;
	rating = mov.rating;
	summary = mov.summary;
	sortType = BY_ID; // default sort type.

	std::list<Professional*>::const_iterator proffIter;
	for (proffIter = mov.professionals.begin(); proffIter != mov.professionals.end(); proffIter++) {
		professionals.push_back(*proffIter);
	}
	std::list<const Genre*>::const_iterator genreIter;
	for (genreIter = mov.genres.begin(); genreIter != mov.genres.end(); genreIter++) {
		genres.push_back(*genreIter);
	}
}

/******************************************************************************************
 * Destructor. Deletes the movie.
 ******************************************************************************************/
Movie :: ~Movie() {
    
}

/******************************************************************************************
 * This function uses the C++ class list push_back function to add the given professional
 * to this movie's list of professionals.
 ******************************************************************************************/
void Movie :: addProff(Professional& p) {
    professionals.push_back(&p);
}

/******************************************************************************************
 * This function uses the list push_back function to add the given genre to this movie's
 * list of genres.
 ******************************************************************************************/
void Movie :: addGenre(const Genre& g) {
    genres.push_back(&g);
}

/******************************************************************************************
 * This function simply sets the value of the Movie's sortType member to either 1,
 * 2, or 3, signifying the 3 different ways of sorting the movie's cast.
 ******************************************************************************************/
void Movie :: defineSort(const int type) {
    sortType = type;
}

/******************************************************************************************
 * This function first calls sortCast(), and then iterates through this movie's list of 
 * professionals and prints each one.
 ******************************************************************************************/
std::string Movie :: printCast() {
	std::string finalList;
	sortCast();
    std::list<Professional*>::iterator iter = professionals.begin();
    while (iter != professionals.end()) {
    	Professional* proff = *iter;
    	finalList += proff->print();
    	iter++;
    }
    return finalList;
}

/******************************************************************************************
 * This function prints the information of this movie, line by line.
 ******************************************************************************************/
std::string Movie :: print() {
	std::string finalMovie;
	finalMovie = code + " " + title + " " + runTime + " " +
			yearOfRelease + " " + rating + " ";
	if (!genres.empty()) {
		finalMovie += genreString() + " ";
	}
	finalMovie += summary + "\n";
	finalMovie += printCast();
	return finalMovie;
}

/******************************************************************************************
 * This function does operator overloading on the operator '+'. It defines the addition of 
 * two movies to mean copying all the information (except genres and cast) from the longer 
 * movie and then combining the cast and genres of both movies. All of this data is assigned
 * to the members of a new Movie object, which the function returns.
 ******************************************************************************************/
Movie* Movie :: operator + (const Movie& other) {
	Movie* copy = new Movie(other);
	Movie* longer = this;
	int time1, time2;
	std::stringstream convert1(this->runTime);
	convert1 >> time1;
	std::stringstream convert2(copy->runTime);
	convert2 >> time2;
	if (time2 > time1)
		longer = copy;
	std::string newCode = this->code + '_' + copy->code;
	Movie* newMovie = new Movie(newCode, longer->title, longer->runTime,
				      longer->yearOfRelease, longer->rating, longer->summary);
	std::list<Professional*>::iterator proffIter1;
	std::list<Professional*>::iterator proffIter2;
	bool duplicate = false;
	bool addedOneList = false;
	for (proffIter1 = this->professionals.begin();
			proffIter1 != this->professionals.end(); proffIter1++) {
		Professional* proff1 = *proffIter1;
		for (proffIter2 = copy->professionals.begin();
				proffIter2 != copy->professionals.end(); ) {
			Professional* proff2 = *proffIter2;
			if (!addedOneList) {
				newMovie->addProff(*proff2);
				proff2->signOnToMovie(*newMovie);
			}
			if (proff1 == proff2) {
				duplicate = true;
				proffIter2 = copy->professionals.erase(proffIter2);
			} else
				proffIter2++;
		}
		addedOneList = true;
		if (!duplicate) {
			newMovie->addProff(*proff1);
			proff1->signOnToMovie(*newMovie);
		}
		duplicate = false;
	}

	addedOneList = false;
	std::list<const Genre*>::iterator genreIter1;
	std::list<const Genre*>::iterator genreIter2;
	for (genreIter1 = this->genres.begin();
			genreIter1 != this->genres.end(); genreIter1++) {
		const Genre* genre1 = *genreIter1;
		for (genreIter2 = copy->genres.begin(); genreIter2 != copy->genres.end();) {
			const Genre* genre2 = *genreIter2;
			if (!addedOneList)
				newMovie->addGenre(*genre2);
			if (genre1->getGenre() == genre2->getGenre()) {
				duplicate = true;
				genreIter2 = copy->genres.erase(genreIter2);
			} else
				genreIter2++;
		}
		addedOneList = true;
		if (!duplicate)
			newMovie->addGenre(*genre1);
		duplicate = false;
	}
	delete copy;
	return newMovie;
}

/******************************************************************************************
 * This function iterates through this movie's list of professionals, and for each
 * professional, removes this movie from that professional's movie list.
 ******************************************************************************************/
void Movie :: fireAllProfessionals() {
    std::list<Professional*>::iterator iter = professionals.begin();
    while (iter != professionals.end()) {
    	Professional* proff = *iter;
    	proff->leaveMovie(*this);
    	iter++;
    }
    professionals.clear();
}

/******************************************************************************************
 * This function returns the Professional with the given ID, provided that the requested 
 * Professional is found in the Movie's list of Professionals. If it is not found, this 
 * function returns null.
 ******************************************************************************************/
Professional* getProff(const std::string& id) {
    return NULL;
}

/******************************************************************************************
 * Remove Professional with the given ID from this Movie's list of Professionals.
 * If the Professional is not in this Movie's list, this function does nothing.
 ******************************************************************************************/
void Movie :: fireProfessional(Professional& proff) {
    professionals.remove(&proff);
}

/******************************************************************************************
 * Uses a switch-case to implement three different sorts for each possible value of
 * sortType. In each case, the function calls the sort function of std::list with the
 * appropriate comparing function as the parameter.
 ******************************************************************************************/
void Movie :: sortCast() {
	AgeComparer ageCmp;
	IDComparer iDCmp;
	NumOfMoviesComp moviesCmp;
	switch (sortType) {

	case BY_ID:
		professionals.sort(iDCmp);
		break;
	case BY_AGE:
		professionals.sort(ageCmp);
		break;
	case BY_NUM_OF_MOVIES:
		professionals.sort(moviesCmp);
		break;
	/*
	 * The defineSortType function in class System will ensure that the default case
	 * will never occur.
	 */
	default:
		break;
	}
}

/******************************************************************************************
 * This function returns the cast of this movie. That is, the list of Professionals stored
 * in the Movie object.
 ******************************************************************************************/
const std::list<Professional*>* Movie :: getCast() const {
    return &professionals;
}

/******************************************************************************************
 * Return the code member of this movie.
 ******************************************************************************************/
const std::string* Movie :: getCode() const {
    return &code;
}

/******************************************************************************************
 * Return the title member of this movie.
 ******************************************************************************************/
const std::string* Movie :: getTitle() const {
	return &title;
}

/******************************************************************************************
 * Return the runTime member of this movie.
 ******************************************************************************************/
const std::string* Movie :: getRunTime() const {
	return &runTime;
}

/******************************************************************************************
 * Return the year member of this movie.
 ******************************************************************************************/
const std::string* Movie :: getYear() const {
    return &yearOfRelease;
}

/******************************************************************************************
 * Return the rating member of this movie.
 ******************************************************************************************/
const std::string* Movie :: getRating() const {
    return &rating;
}

/******************************************************************************************
 * Return the list<Genre*> member of this movie.
 ******************************************************************************************/
const std::list<const Genre*>* Movie :: getGenres() const {
    return &genres;
}

/******************************************************************************************
 * Return the summary member of this movie.
 ******************************************************************************************/
std::string* Movie :: getSummary() {
    return &summary;
}

/******************************************************************************************
 * Returns a list of the movie's genres in string form, with each genre separated
 * by a comma.
 ******************************************************************************************/
std::string Movie :: genreString() {
	std::string genreString = "";
	std::list<const Genre*>::iterator iter = genres.begin();
	if (iter != genres.end()) {
		genreString = (*iter)->getGenre();
		iter++;
	}
	while (iter != genres.end()) {
		genreString = genreString + "," + (*iter)->getGenre();
		iter++;
	}
	return genreString;
}
