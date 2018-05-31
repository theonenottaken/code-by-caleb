
/*******************************************************************************************
 * Student Name: Caleb Shere Benjamin Wexler
 * Exercise Name: Targil 5
 * File Description: Producer.hpp
 *******************************************************************************************/

#ifndef Producer_hpp
#define Producer_hpp

#include <iostream>

#include "Professional.hpp"

class Producer : public Professional {
    
public:
    /************************************************************************************
     * Makes a new Producer with the given information.
     ************************************************************************************/
    Producer(const std::string& id, const std::string& name, const std::string& job,
             const std::string& age, const std::string& gender)
             : Professional(id, name, job, age, gender) { }

    /************************************************************************************
     * Destructor
     ************************************************************************************/
    ~Producer() {}

    /************************************************************************************
     * Returns the name of this producer.
     ************************************************************************************/
    std::string print();
};

#endif /* Producer_hpp */
