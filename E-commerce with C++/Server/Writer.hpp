
/*******************************************************************************************
 * Student Name: Caleb Shere
 * Exercise Name: Targil 5
 * File Description: Writer.hpp
 *******************************************************************************************/

#ifndef Writer_hpp
#define Writer_hpp

#include <iostream>

#include "Professional.hpp"

class Writer : public Professional {
    
public:
    /********************************************************************************
     * Makes a new writer with the given information.
     ********************************************************************************/
    Writer(const std::string& id, const std::string& name, const std::string& job,
           const std::string& age, const std::string& gender)
           : Professional(id, name, job, age, gender) { }
    
    /********************************************************************************
     * Destructor
     ********************************************************************************/
    ~Writer() {}

    /********************************************************************************
     * Returns the name and specific job description of this writer.
     ********************************************************************************/
    std::string print();
};

#endif /* Writer_hpp */
