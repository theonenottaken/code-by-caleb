
/*******************************************************************************************
 * Student Name: Caleb Shere Benjamin Wexler
 * Exercise Name: Targi 5
 * File Description: Genre.hpp
 *******************************************************************************************/


#ifndef Genre_hpp
#define Genre_hpp

#include <iostream>

class Genre {
    
private:
    std::string genre;
    
public:
    /********************************************************************************
     * Makes a new genre.
     ********************************************************************************/
    Genre(const std::string& g);
    
    /********************************************************************************
     * Returns the name of the genre as a string.
     ********************************************************************************/
    std::string getGenre() const;
};

#endif /* Genre_hpp */
