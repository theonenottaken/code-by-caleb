
/*******************************************************************************************
 * Student Name: Caleb Shere Benjmin Wexler
 * Exercise Name: Targil 5
 * File Description: System.hpp
 *******************************************************************************************/


#ifndef System_hpp
#define System_hpp

#include <iostream>
#include <list>
#include "Movie.hpp"
#include "Professional.hpp"
#include "Protocol.hpp"
#include <pthread.h>

class System {
    
private:
    std::list<Movie*> movies;
    std::list<Professional*> professionals;
    std::list<const Genre*> genres;
    static System* instance;
    static bool instantiated;
    static int lockInit;
    static pthread_mutex_t lock;
    System() { }
    
    /*********************************************************
     * Allows the user to input a movie into the system.
     *********************************************************/
    std::string inputMovie(std::string command);

	/**********************************************************
	 * Allows the user to input a professional into the system.
	 **********************************************************/
    std::string inputProfessional(std::string command);

	/***********************************************************
	 * Allows the user to add a professional to a movie already
	 * in the system.
	 ***********************************************************/
    std::string addProffToMovie(std::string command);

	/***********************************************************
	 * Allows the user to add a genre to a movie already in the
	 * system.
	 ***********************************************************/
    std::string addGenreToMovie(std::string command);

	/************************************************************
	 * Allows the user to define the sort type for a given movie
	 * in the system.
	 ************************************************************/
    std::string defineSortType(std::string command);

	/*************************************************************
	 * Allows the user to print the cast of a given movie in the
	 * system.
	 *************************************************************/
    std::string printCastOfMovie(std::string command);

	/*************************************************************
	 * Allows the user to print the information of a given movie
	 * in the system.
	 *************************************************************/
    std::string printMovie(std::string command);

	/*************************************************************
	 * Allows the user to join two movies together into one.
	 *************************************************************/
    std::string joinMovies(std::string command);

	/*************************************************************
	 * Allows the user to print all of the movies that a given
	 * professional works in.
	 *************************************************************/
    std::string printMoviesOfProff(std::string command);

	/*************************************************************
	 * Allows the user to delete a movie from the system.
	 *************************************************************/
    std::string deleteMovie(std::string command);

	/*************************************************************
	 * Allows the user to delete a professional from the system.
	 *************************************************************/
    std::string deleteProfessional(std::string command);

	/**************************************************************
	 * Allows the user to delete a given professional from the cast
	 * of a given movie.
	 **************************************************************/
    std::string deleteProffFromMovie(std::string command);

	/***************************************************************
	 * Allows the user to print the information of all of the movies
	 * in the system.
	 ***************************************************************/
    std::string printAllMovies();

	/***************************************************************
	 * Allows the user to print all of the professionals in the
	 * system.
	 ***************************************************************/
    std::string printAllProfessionals();

	/***************************************************************
	 * Allows the user to print all of the movies that are relevant
	 * to a given genre.
	 ***************************************************************/
    std::string printMoviesOfGenre(std::string command);

public:

    /*********************************************************
     * Starts the program and allows the user to input items.
     *********************************************************/
    void start(Protocol* conn, int clientSocket);

	/***************************************************************
	 * Returns the movie with the given code in the system. If the
	 * movie is not in the system, returns null.
	 ***************************************************************/
	Movie* findMovie(const std::string& code);

	/***************************************************************
	 * Returns the professional with the given ID in the system. If
	 * the professional is not in the system, returns null.
	 ***************************************************************/
	Professional* findProfessional(const std::string& id);

	/****************************************************************
	 * Returns the Genre with the given genre string in the system.
	 * If the requested genre is not in the system, returns null.
	 ****************************************************************/
	const Genre* findGenre(const std::string& genStr);
    
	/****************************************************************
	 * Returns the System's list of movies. Used for Google Testing.
	 ****************************************************************/
    std::list<Movie*>* getMovies();

	/****************************************************************
	 * Returns the System's list of Professionals. Used for Google
	 * Testing.
	 ****************************************************************/
    std::list<Professional*>* getProfessionals();

	/****************************************************************
	 * Returns the System's list of genres. Used for Google Testing.
	 ****************************************************************/
    std::list<const Genre*>* getGenres();
    
	/****************************************************************
	 * Returns the one and only instance of the System class. If
	 * there is no existing instance, this function makes one and
	 * returns it. Otherwise, it returns a pointer to the existing
	 * instance.
	 ****************************************************************/
    static System* getInstance();
};

#endif /* System_hpp */
