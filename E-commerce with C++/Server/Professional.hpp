
/*******************************************************************************************
 * Student Name: Caleb Shere Benjamin Wexler
 * Exercise Name: Targil 5
 * File Description: Professional.hpp
 *******************************************************************************************/

#ifndef Professional_hpp
#define Professional_hpp

#include <iostream>
#include <list>
#include "Movie.hpp"

class Movie;
class Professional {
    
protected:
    std::string iDNum;
    std::string name;
    std:: string specificJob;
    std::string age;
    std::string gender;
    std::list<Movie*> movies;
    
public:

    /***************************************************************
     * Constructor. Makes a new Professional with the given info.
     ***************************************************************/
    Professional(const std::string& id, const std::string& n, const std::string& job,
                 const std::string& a, const std::string& gen);

    /***************************************************************
     * Destructor
     ***************************************************************/
    virtual ~Professional() { }

    /***************************************************************
     * Returns a string describing each movie that this professional
     * works in.
     ***************************************************************/
    std::string printMovies();
    
    /***************************************************************
     * Removes this professional from all of the movies he works in
     ***************************************************************/
    void leaveAllMovies();
    
    /****************************************************************
     * Adds this professional to this movie's professional list
     ****************************************************************/
    void signOnToMovie(Movie& mov);

    /***************************************************************
     * Removes this professional from the given movie.
     ***************************************************************/
    void leaveMovie(Movie& mov);
    
    /***************************************************************
     * Returns the list of this professional's movies.
     ***************************************************************/
    const std::list<Movie*>* getMovies() const;
    
    /***************************************************************
     * Returns the ID number of this professional.
     ***************************************************************/
    const std::string* getID() const;
    
    /****************************************************************
     * Returns the age of this Professional
     ****************************************************************/
    const std::string* getAge() const;

    /***************************************************************
     * An abstract function that will be implemented by the derived
     * classes of this class.
     ***************************************************************/
    std::string virtual print() = 0;
};

#endif /* Professional_hpp */
