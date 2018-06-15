
/*******************************************************************************************
 * Student Name: Caleb Shere Benjamin Wexler
 * Exercise Name: Targil 5
 * File Description: Movie.hpp
 *******************************************************************************************/

#ifndef Movie_hpp
#define Movie_hpp

#include <iostream>
#include <list>
#include "Genre.hpp"
#include "Professional.hpp"

class Professional;

class Movie {
    
private:
    std::string code;
    std::string title;
    std::string runTime;
    std::string yearOfRelease;
    std::string rating;
    std::list<const Genre*> genres;
    std::string summary;
    std::list<Professional*> professionals;
    int sortType;
    
public:
    /*********************************************************************************
     * Makes a new Movie object with the given information.
     *********************************************************************************/
    Movie(const std::string& c, const std::string& t, const std::string& time,
          const std::string& year, const std::string& rating, const std::string& summ);
    
    /*********************************************************************************
     * Copy constructor
     *********************************************************************************/
    Movie(const Movie& mov);

    /*********************************************************************************
     * Destroys this movie object, freeing its memory from the heap.
     *********************************************************************************/
    ~Movie();
    
    /*********************************************************************************
     * Adds the given Professional to this movie.
     *********************************************************************************/
    void addProff(Professional& p);
    
    /*********************************************************************************
     * Adds the given genre to this movie.
     *********************************************************************************/
    void addGenre(const Genre& g);
    
    /*********************************************************************************
     * Defines the way in which the cast of this movie should be printed.
     *********************************************************************************/
    void defineSort(const int type);
    
    /*********************************************************************************
     * Prints the information of each professional in this movie.
     *********************************************************************************/
    std::string printCast();
    
    /*********************************************************************************
     * Prints the information of this movie.
     *********************************************************************************/
    std::string print();
    
    /*********************************************************************************
     * Joins two movies together using the '+' operator.
     *********************************************************************************/
    Movie* operator + (const Movie& other);
    
    /*********************************************************************************
     * Deletes this movie from the system.
     *********************************************************************************/
    void fireAllProfessionals();
    
    /*********************************************************************************
     * Returns the professional with the given ID that is in this movie's cast. If the
     * professional is not in this movie's cast, returns null.
     *********************************************************************************/
    Professional* getProff(const std::string& id);
    
    /*********************************************************************************
     * Removes the given professional from this movie's cast.
     *********************************************************************************/
    void fireProfessional(Professional& proff);
    
    /*********************************************************************************
     * Sorts the professionals in this movie, according to the sort type.
     *********************************************************************************/
    void sortCast();

    /*********************************************************************************
     * Returns the list of professionals in this movie.
     *********************************************************************************/
    const std::list<Professional*>* getCast() const;
    
    /*********************************************************************************
     * Returns the code of this movie.
     *********************************************************************************/
    const std::string* getCode() const;
    
    /*********************************************************************************
     * Returns the title of this movie.
     *********************************************************************************/
    const std::string* getTitle() const;
    
    /*********************************************************************************
     * Returns the running time of this movie.
     *********************************************************************************/
    const std::string* getRunTime() const;
    
    /*********************************************************************************
     * Returns the year in which this movie was released.
     *********************************************************************************/
    const std::string* getYear() const;
    
    /*********************************************************************************
     * Returns the rating of this movie.
     *********************************************************************************/
    const std::string* getRating() const;
    
    /*********************************************************************************
     * Returns the list of this movie's genres.
     *********************************************************************************/
    const std::list<const Genre*>* getGenres() const;
    
    /*********************************************************************************
     * Returns the summary of this movie.
     *********************************************************************************/
    std::string* getSummary();

    /*********************************************************************************
     * Returns a list of the movie's genres in string form, with each genre separated
     * by a comma.
     *********************************************************************************/
    std::string genreString();
};

#endif /* Movie_hpp */
