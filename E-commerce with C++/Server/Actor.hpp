
/*******************************************************************************************
 * Student Name: Caleb Shere Benjamin Wexler
 * Exercise Name: Targil 5
 * File Description: Actor.hpp
 *******************************************************************************************/

#ifndef Actor_hpp
#define Actor_hpp

#include <iostream>

#include "Professional.hpp"

class Actor : public Professional {
    
public:
    /********************************************************************************
     * Makes a new Actor with the given information.
     ********************************************************************************/
    Actor(const std::string& id, const std::string& name, const std::string& job,
          const std::string& age, const std::string& gender)
	      : Professional(id, name, job, age, gender) { }
    
    /*********************************************************************************
     * Destructor
     *********************************************************************************/
    ~Actor() { }

    /********************************************************************************
     * Prints the name and age of this Actor.
     ********************************************************************************/
    std::string print();
};

#endif /* Actor_hpp */
