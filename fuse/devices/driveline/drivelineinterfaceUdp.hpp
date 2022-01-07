#pragma once

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "drivelineinterface.hpp"

using namespace std;

class DrivelineInterfaceUdp : public DrivelineInterface
{
	protected:
		struct sockaddr_in _tx_addr;
		int _sockfd;
		struct sockaddr_in _rx_addr;
		int _sockrx;

	public:
		DrivelineInterfaceUdp();
		~DrivelineInterfaceUdp();
		bool init();
		bool txCmd(std::string source, unsigned char vLeft, unsigned char vRight) override;
		void doRx() override;
};