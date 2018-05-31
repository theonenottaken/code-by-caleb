
/*******************************************************************************************
 * Student Name: Caleb Shere Benjamin Wexler
 * Exercise Name: Targil 5
 * File Description: System.cpp
 *******************************************************************************************/

#include "System.hpp"
#include "Actor.hpp"
#include "Director.hpp"
#include "Producer.hpp"
#include "Writer.hpp"
#include <iostream>
#include <string>
#include <sstream>
#include <limits>
#include <pthread.h>
#include <stdio.h>
#include "definitions.h"

/*
 * Initialization of static members to be used in the static function getInstance().
 * This function and these members satisfy the Singleton design for this program
 * and will ensure that there is always at most one instance of the System class.
 */
System* System::instance = NULL;
bool System::instantiated = false;
pthread_mutex_t System::lock;
int System::lockInit = pthread_mutex_init(&System::lock, NULL);

/*******************************************************************
 * This function "starts" the program. It will ask the user what he 
 * wants to do, and then call the other functions in class System in 
 * order to do it.
 *******************************************************************/
void System :: start(Protocol* conn, int clientSocket) {
	/*
	 * Make commandNum 0 here just so that it will be initialized when we reach
	 * the beginning of the while loop. When we first reach the while loop,
	 * commandNum is 0 so obviously it is not equal to -1. Following that, it
	 * will be set according to what is entered into cin.
	 */
	int commandNum = 0;
	std::string commandNumStr;
	std::string command;
	std::string commandResult;
	while (true) {
		command = conn->receiveData(clientSocket);
		std::string::size_type position = command.find (' ');
		commandNumStr = command.substr(0, position);
		command = command.substr(position + 1);
		std::stringstream convert(commandNumStr);
		convert >> commandNum;
		switch (commandNum) {
		case INPUT_MOVIE:
			commandResult = inputMovie(command);
			break;
		case INPUT_PROFF:
			commandResult = inputProfessional(command);
			break;
		case ADD_PROFF_TO_MOVIE:
			commandResult = addProffToMovie(command);
			break;
		case ADD_GENRE_TO_MOVIE:
			commandResult = addGenreToMovie(command);
			break;
		case DEFINE_SORT:
			commandResult = defineSortType(command);
			break;
		case PRINT_CAST_OF_MOVIE:
			commandResult = printCastOfMovie(command);
			break;
		case PRINT_MOVIE:
			commandResult = printMovie(command);
			break;
		case JOIN_MOVIES:
			commandResult = joinMovies(command);
			break;
		case PRINT_MOVIES_OF_PROFF:
			commandResult = printMoviesOfProff(command);
			break;
		case DELETE_MOVIE:
			commandResult = deleteMovie(command);
			break;
		case DELETE_PROFF:
			commandResult = deleteProfessional(command);
			break;
		case DELETE_PROFF_FROM_MOVIE:
			commandResult = deleteProffFromMovie(command);
			break;
		case PRINT_ALL_MOVIES:
			commandResult = printAllMovies();
			break;
		case PRINT_ALL_PROFFS:
			commandResult = printAllProfessionals();
			break;
		case PRINT_MOVIES_OF_GENRE:
			commandResult = printMoviesOfGenre(command);
			break;
		case TERMINATE:
			return;
		default:
			break;
		}
		if (commandNum != -1)
			conn->sendData(commandResult, clientSocket);
	}
}

/***********************************************************************
 * This function asks the user to input the information for a movie.
 * It then makes a new Movie object with that information and adds the
 * Movie to the List of Movies in class System.
 ************************************************************************/
std::string System :: inputMovie(std::string command) {
    std::string code;
    std::string title;
    std::string runTime;
    std::string year;
    std::string rating;
    std::string summary;

	std::string::size_type position = command.find (' ');
	code = command.substr(0, position);
	command = command.substr(position + 1);

	position = command.find (' ');
	title = command.substr(0, position);
	command = command.substr(position + 1);

	position = command.find (' ');
	runTime = command.substr(0, position);
	command = command.substr(position + 1);

	position = command.find (' ');
	year = command.substr(0, position);
	command = command.substr(position + 1);

	position = command.find (' ');
	rating = command.substr(0, position);
	command = command.substr(position + 1);

	summary = command;

    if (runTime[0] == '-' || year[0] == '-' || rating[0] == '-') {
    	return "Failure\n";
    }
    Movie* mov = findMovie(code);
    if (mov != NULL) {
    	return "Failure\n";
    }

    mov = new Movie(code, title, runTime, year, rating, summary);
    movies.push_back(mov);
    	return "Success\n";
}

/*******************************************************************
 * This function asks the user to input the information of a
 * professional. It then makes a new Professional object with
 * that information and adds the Professional to the list of
 * Professionals in class System.
 *******************************************************************/
std::string System :: inputProfessional(std::string command) {
    std::string typeStr;
    std::string id;
    std::string age;
    std::string job;
    std::string gender;
    std::string name;
    int type;
    bool fail = false;

	std::string::size_type position = command.find (' ');
	typeStr = command.substr(0, position);
	command = command.substr(position + 1);
    std::stringstream convert(typeStr);
    convert >> type;

	position = command.find (' ');
	id = command.substr(0, position);
	command = command.substr(position + 1);

	position = command.find (' ');
	age = command.substr(0, position);
	command = command.substr(position + 1);
    if (age[0] == '-') // negative age
    	fail = true;

	position = command.find (' ');
	job = command.substr(0, position);
	command = command.substr(position + 1);

	position = command.find (' ');
	gender = command.substr(0, position);
	command = command.substr(position + 1);

	name = command;

    Professional* proff = findProfessional(id);
    if (proff != NULL) { // There already exists a Professional with this ID.
    	fail = true;
    } else if (!fail) { // Only if fail is still false at this point...

    	switch (type) {
    	case 0:
    		proff = new Director(id, name, job, age, gender);
    		break;
    	case 1:
    		proff = new Actor(id, name, job, age, gender);
    		break;
    	case 2:
    		proff = new Writer(id, name, job, age, gender);
    		break;
    	case 3:
    		proff = new Producer(id, name, job, age, gender);
    		break;
    	default:
    		fail = true;
    		break;
    	}
    }
    if (!fail) {
    	professionals.push_back(proff);
    	return "Success\n";
    }
    else
    	return "Failure\n";
}

/*******************************************************************
 * This function asks the user to input the ID of a Professional
 * and the code of a Movie. It then calls findMovie() to find the
 * movie, and calls Movie :: addProff() to add the Professional to
 * that Movie.
 *******************************************************************/
std::string System :: addProffToMovie(std::string command) {
    std::string movieCode;
    std::string proffID;

	std::string::size_type position = command.find (' ');
	movieCode = command.substr(0, position);
	command = command.substr(position + 1);

    proffID = command;

    Professional* proff = findProfessional(proffID);
    Movie* mov = findMovie(movieCode);
    if (proff != NULL && mov != NULL) {
    	mov->addProff(*proff);
    	proff->signOnToMovie(*mov);
    	return "Success\n";
    } else { // Either the professional or the movie doesn't exist.
    	return "Failure\n";
    }
}

/*******************************************************************
 * This function asks the user to input a movie code and a genre.
 * It then calls findMovie(), makes a new Genre object of the given
 * genre, and then calls Movie :: addGenre() to add the genre to the
 * movie.
 *******************************************************************/
std::string System :: addGenreToMovie(std::string command) {
    std::string movieCode;
    std::string genreStr;

	std::string::size_type position = command.find (' ');
	movieCode = command.substr(0, position);
	command = command.substr(position + 1);

	genreStr = command;

    Movie* mov = findMovie(movieCode);
    if (mov != NULL) {
    	const Genre* genre = new Genre(genreStr);
    	mov->addGenre(*genre);
    	genres.push_back(genre);
    	return "Success\n";
    }
    else { // The movie does not exist.
    	return "Failure\n";
    }
}

/*******************************************************************
 * This function asks the user to input a movie code and a sort
 * type. Then it finds the movie and calls Movie :: defineSort()
 * to define the sort type for that movie.
 *******************************************************************/
std::string System :: defineSortType(std::string command) {
    std::string sortTypeStr;
    std::string movieCode;

	std::string::size_type position = command.find (' ');
	movieCode = command.substr(0, position);
	command = command.substr(position + 1);

	sortTypeStr = command;

    int sortType;
    std::stringstream convert(sortTypeStr);
    convert >> sortType;
    if (sortType < BY_ID || sortType > BY_NUM_OF_MOVIES) { // Undefined sort type
    	return "Failure\n";
    }
    Movie* mov = findMovie(movieCode);
    if (mov != NULL) {
    	mov->defineSort(sortType);
    	return "Success\n";
    } else // The movie does not exist.
    	return "Failure\n";
}

/*******************************************************************
 * This function asks the user to input a movie code. It uses
 * the code to find the movie, and then calls Movie :: printCast()
 * to print the Movie's cast.
 *******************************************************************/
std::string System :: printCastOfMovie(std::string command) {
    std::string movieCode;
	movieCode = command;

    Movie* mov = findMovie(movieCode);
    if (mov != NULL) {
    	return mov->printCast();
    } else // The movie does not exist.
    	return "Failure\n";
}

/*******************************************************************
 * This function asks the user to input a movie code. It then
 * finds the movie and calls Movie :: print() to print its information.
 *******************************************************************/
std::string System :: printMovie(std::string command) {
    std::string movieCode;
	movieCode = command;

    Movie* mov = findMovie(movieCode);
    if (mov != NULL) {
    	return mov->print();
    } else // The movie does not exist.
    	return "Failure\n";
}

/*******************************************************************
 * This function asks the user to input the codes of the movies
 * that are to be joined. It finds the movies, and then makes a
 * new movie that is the union of all these movies by using the '+' 
 * operator, which is defined accordingly in class Movie.
 *******************************************************************/
std::string System :: joinMovies(std::string command) {
    std::string firstCode;
    std::string secondCode;
    Movie* mov1;
    Movie* mov2;
    Movie* mov3;
    char nextChar;
    bool success = false;
    while ((nextChar = command[0]) != ',') {
    	firstCode += nextChar; // The first code is everything before the first comma.
    	command = command.substr(1);
    }
    command = command.substr(1);
    mov1 = findMovie(firstCode);
    if (mov1 != NULL) {
    	Movie* mid = NULL;
    	Movie* originalFirst = mov1;
    	while ((nextChar = command[0]) != '\0') {
    		if (nextChar == ',') {
    			mov2 = findMovie(secondCode);
    			if (mov2 != NULL) {
    				mov3 = *mov1 + *mov2;
    				mid = mov1;
    				mov1 = mov3;
    				if (mid != originalFirst) {
    					/*
    					 * When there are two movies being joined, one or more intermediate
    					 * movies will be made before the final result. So we have to delete
    					 * them once we're finished using them.
    					 */
    					delete mid;
    					mid = NULL;
    				}
    				secondCode.clear();
    			} else
    				break; // Leaves the while loop with secondCode unchanged
    		} else {
    			secondCode += nextChar;
    		}
    		command = command.substr(1);
    	}
    	mov2 = findMovie(secondCode);
    	if (mov2 != NULL) {
    		mov3 = *mov1 + *mov2;
    		movies.push_back(mov3);
    		success = true;
    		return "Success\n";
    	}
    }
    if (!success)
    	return "Failure\n";
}

/*******************************************************************
 * This function asks the user to input the ID of a Professional. 
 * It then calls the function findProfessional() to find the 
 * Professional and calls Professional :: printMovies() to print 
 * that Professional's Movies.
 *******************************************************************/
std::string System :: printMoviesOfProff(std::string command) {
    std::string proffID;
	proffID = command;

    Professional* proff = findProfessional(proffID);
    if (proff != NULL) {
    	return proff->printMovies();
    } else // Professional does not exist.
    	return "Failure\n";
}

/*******************************************************************
 * This function asks the user to input a movie code. It then finds 
 * that movie, and for each Professional in the cast of that movie, 
 * it calls Professional :: leaveMovie(), and then deletes this movie 
 * from the heap.
 *******************************************************************/
std::string System :: deleteMovie(std::string command) {
    std::string movieCode;
	movieCode = command;

    Movie* mov = findMovie(movieCode);
    if (mov != NULL) {
    	mov->fireAllProfessionals();
    	movies.remove(mov);
    	delete mov;
    	return "Success\n";
    } else // Movie does not exist.
    	return "Failure\n";
}

/*******************************************************************
 * This function asks the user to input the ID of a Professional. It
 * finds the Professional, and for each Movie in this Professional's 
 * list of Movies, it calls Movie :: deleteProff(), and then deletes
 * this Professional from the heap.
 *******************************************************************/
std::string System :: deleteProfessional(std::string command) {
    std::string proffID;
    proffID = command;
    Professional* proff = findProfessional(proffID);
    if (proff != NULL) {
    	proff->leaveAllMovies();
    	professionals.remove(proff);
    	delete proff;
    	return "Success\n";
    } else // Professional does not exist.
    	return "Failure\n";
}

/*******************************************************************
 * This function asks the user to input a movie code and the ID of 
 * a professional. It then finds the movie, tells the movie to find
 * that professional in its list of professionals, tells that
 * professional to leave the movie, and then deletes the professional
 * from the heap.
 *******************************************************************/
std::string System :: deleteProffFromMovie(std::string command) {
    std::string movieCode;
    std::string proffID;

	std::string::size_type position = command.find (' ');
	movieCode = command.substr(0, position);
	command = command.substr(position + 1);

	proffID = command;

    Professional* proff = findProfessional(proffID);
    Movie* mov = findMovie(movieCode);
    if (proff != NULL && mov != NULL) {
    	mov->fireProfessional(*proff);
    	proff->leaveMovie(*mov);
    	return "Success\n";
    } else // Movie or professional does not exist.
    	return "Failure\n";
}

/*******************************************************************
 * This function iterates the System's list of movies, and for each 
 * movie, calls Movie :: print().
 *******************************************************************/
std::string System :: printAllMovies() {
	std::string movieList;
    std::list<Movie*>::iterator iter = movies.begin();
    while (iter != movies.end()) {
    	Movie* mov = *iter;
    	movieList += mov->print();
    	iter++;
    }
    return movieList;
}

/*******************************************************************
 * This function iterates the System's list of Professionals and for
 * each Professional, calls Professional :: print().
 *******************************************************************/
std::string System :: printAllProfessionals() {
	std::string professionalsList;
    std::list<Professional*>::iterator iter = professionals.begin();
    while (iter != professionals.end()) {
    	Professional* proff = *iter;
    	professionalsList += proff->print();
    	iter++;
    }
    return professionalsList;
}

/******************************************************************************
 * This function prints all of the movies in the system that are relevant to
 * a given genre. The genre is received as input, and then the function
 * iterates through the system's list of movies, and for each one, checks if
 * the given genre is in that movie's genre list. It it is, print the movie.
 ******************************************************************************/
std::string System :: printMoviesOfGenre(std::string command) {
	std::string moviesOfGenreList;
	std::string genre;

	genre = command;

	std::list<Movie*>::iterator movieIter = movies.begin();
	while (movieIter != movies.end()) {
		Movie* mov = *movieIter;
		const std::list<const Genre*>* genreList = mov->getGenres();
		std::list<const Genre*>::const_iterator genreIter = genreList->begin();
		while (genreIter != genreList->end()) {
			const Genre* thisGenre = *genreIter;
			if (thisGenre->getGenre() == genre) {
				moviesOfGenreList += mov->print();
				break;
			}
			genreIter++;
		}
		movieIter++;
	}
	return moviesOfGenreList;
}

/*******************************************************************
 * This function iterates through the System's list of Movies and 
 * returns the Movie whose code matches the parameter code.
 *******************************************************************/
Movie* System :: findMovie(const std::string& code) {
	Movie* mov = NULL;
    std::list<Movie*>::iterator iter = movies.begin();
    while (iter != movies.end()) {
    	Movie* thisMov = *iter;
    	std::string currCode = *(thisMov->getCode());
    	if (currCode == code) {
    		mov = *iter;
    		break;
    	}
    	iter++;
    }
    return mov;
}

/*******************************************************************
 * This function iterates through the System's list of Professionals
 * and returns the Professional whose ID matches the parameter ID.
 *******************************************************************/
Professional* System :: findProfessional(const std::string& id) {
    Professional* proff = NULL;
    std::list<Professional*>::iterator iter = professionals.begin();
    while (iter != professionals.end()) {
    	Professional* thisProff = *iter;
    	std::string thisID = *(thisProff->getID());
    	if (thisID == id) {
    		proff = *iter;
    		break;
    	}
    	iter++;
    }
    return proff;
}

/**********************************************************************
 * This function iterates through the System's list of Genres and
 * returns the Genre that matches the given string parameter.
 **********************************************************************/
const Genre* System :: findGenre(const std::string& genStr) {
	const Genre* genre = NULL;
	std::list<const Genre*>::iterator iter;
	for (iter = genres.begin(); iter != genres.end(); iter++) {
		const Genre* thisGenre = *iter;
		std::string thisString = thisGenre->getGenre();
		if (thisString == genStr) {
			genre = *iter;
			break;
		}
	}
	return genre;
}

/**********************************************************************
 * This function returns the System's list of movies. It is used for
 * the google testing.
 **********************************************************************/
std::list<Movie*>* System :: getMovies() {
	return &movies;
}

/***********************************************************************
 * This function returns the list of professionals. It is used for the
 * google testing.
 ***********************************************************************/
std::list<Professional*>* System :: getProfessionals() {
	return &professionals;
}

/************************************************************************
 * This function returns the list of genres. It is used for the google
 * testing.
 ************************************************************************/
std::list<const Genre*>* System :: getGenres() {
	return &genres;
}

/*************************************************************************
 * This function returns a pointer to the one and only instance of the
 * System class. The first time it is called, it will make a new System
 * and return a pointer to it. On all subsequent calls, it will return a
 * pointer to the one existing instance.
 *************************************************************************/
System* System :: getInstance() {
	if (lockInit != 0)
		perror("lock failed to initialize");
	if (!instantiated) {
		pthread_mutex_lock(&lock);
		if (!instantiated) {
			instance = new System();
			instantiated = true;
		}
		pthread_mutex_unlock(&lock);
	}
	return instance;
}
