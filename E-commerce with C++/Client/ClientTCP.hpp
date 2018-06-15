/*
 * ClientTCP.hpp
 *
 *  Created on: Dec 31, 2015
 *      Author: caleb
 */

#ifndef CLIENTTCP_HPP_
#define CLIENTTCP_HPP_

#include "TCP.hpp"

class ClientTCP : public TCP {
public:
	ClientTCP(char* ip_addr, int port_num);
	virtual ~ClientTCP();
	void doConnection();
};

#endif /* CLIENTTCP_HPP_ */
