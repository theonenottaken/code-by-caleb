
/*******************************************************************************************
 * Student Name: Caleb Shere Benjamin Wexler
 * Exercise Name: Targil 5
 * File Description: Professional.cpp
 *******************************************************************************************/

#include "Professional.hpp"

/*******************************************************************************
 * Constructor. Makes a new Professional with the given information.
 *******************************************************************************/
Professional :: Professional(const std::string& id, const std::string& n,
							 const std::string& job, const std::string& a,
							 const std::string& gen) {
	iDNum = id;
	name = n;
	specificJob = job;
	age = a;
	gender = gen;
}

/********************************************************************
 * This function iterates through the movies in this Professional's
 * list of movies and prints each movie.
 ********************************************************************/
std::string Professional :: printMovies() {
	std::string movieList;
    std::list<Movie*>::iterator iter = movies.begin();
    while (iter != movies.end()) {
    	Movie* mov = *iter;
    	movieList += mov->print();
    	iter++;
    }
    return movieList;
}

/*********************************************************************
 * This function first iterates through this professional's list of 
 * movies, and for each movie, deletes this professional from the 
 * movie's list of professionals. Then it deletes this professional 
 * from the heap.
 *********************************************************************/
void Professional :: leaveAllMovies() {
    std::list<Movie*>::iterator iter = movies.begin();
    while (iter != movies.end()) {
    	Movie* mov = *iter;
    	mov->fireProfessional(*this);
    	iter++;
    }
    movies.clear();
}

/**************************************************************************
 * This function adds the given movie to this professional's list of
 * movies.
 **************************************************************************/
void Professional :: signOnToMovie(Movie& mov) {
	movies.push_back(&mov);
}

/*********************************************************************
 * This function finds the movie with the given code in this 
 * Professional's list of movies. It then removes this professional 
 * from that movie's list of professionals. If the Movie with the given
 * code is not found in this Professionals list of movies, this 
 * function does nothing.
 *********************************************************************/
void Professional :: leaveMovie(Movie& mov) {
    movies.remove(&mov);
}

/*********************************************************************
 * This function returns this professional's list of Movies. That is,
 * all of the Movies that this Professional is working in.
 *********************************************************************/
const std::list<Movie*>* Professional :: getMovies() const {
    return &movies;
}

/*********************************************************************
 * Returns the iDNum member of this professional.
 *********************************************************************/
const std::string* Professional :: getID() const {
    return &iDNum;
}

/**********************************************************************
 * Returns the age of this professional.
 **********************************************************************/
const std::string* Professional :: getAge() const {
	return &age;
}
