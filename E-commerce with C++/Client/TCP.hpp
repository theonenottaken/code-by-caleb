/*
 * TCP.hpp
 *
 *  Created on: Dec 31, 2015
 *      Author: caleb
 */

#ifndef TCP_HPP_
#define TCP_HPP_

#include "Protocol.hpp"
#include <iostream>

class TCP : public Protocol {
public:
	TCP();
	virtual ~TCP();
	void sendData(const std::string& data);
	std::string receiveData();
};

#endif /* TCP_HPP_ */
