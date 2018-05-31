
/*******************************************************************************************
 * Student Name: Caleb Shere Benjamin Wexler
 * Exercise Name: Targil 5
 * File Description: Director.hpp
 *******************************************************************************************/

#ifndef Director_hpp
#define Director_hpp

#include <iostream>

#include "Professional.hpp"

class Director : public Professional {
    
public:
    /************************************************************************************
     * Makes a new Director with the given information.
     ************************************************************************************/
    Director(const std::string& id, const std::string& name, const std::string& job,
             const std::string& age, const std::string& gender)
			 : Professional(id, name, job, age, gender) { }
    
    ~Director() {}

    /************************************************************************************
     * Returns the name of this Director.
     ************************************************************************************/
    std::string print();
};

#endif /* Director_hpp */
