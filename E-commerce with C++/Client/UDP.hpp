/*
 * UDP.hpp
 *
 *  Created on: Dec 31, 2015
 *      Author: caleb
 */

#ifndef UDP_HPP_
#define UDP_HPP_

#include "Protocol.hpp"

class UDP : public Protocol {
protected:
	struct sockaddr_in from;

public:
	UDP();
	virtual ~UDP();
	void sendData(const std::string& data);
	std::string receiveData();
};

#endif /* UDP_HPP_ */
