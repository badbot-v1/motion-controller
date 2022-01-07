#pragma once

//https://blog.mbedded.ninja/programming/operating-systems/linux/linux-serial-ports-using-c-cpp/

#include <fcntl.h> // Contains file controls like O_RDWR
#include <errno.h> // Error integer and strerror() function
#include <termios.h> // Contains POSIX terminal control definitions
#include <unistd.h> // write(), read(), close()
#include "drivelineinterface.hpp"


using namespace std;

class DrivelineInterfaceUart : public DrivelineInterface
{
	protected:
		std::string _portName;
		int _fdPort;
	
	protected:
		void doRx() override;
		void onCleanup() override;

	public:
		DrivelineInterfaceUart();
		~DrivelineInterfaceUart();
		bool init();
		bool txCmd(std::string source, unsigned char vLeft, unsigned char vRight) override;
};