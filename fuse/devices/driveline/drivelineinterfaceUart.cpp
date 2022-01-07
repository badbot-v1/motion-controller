#include "drivelineinterfaceUart.hpp"  
#include <yaml-cpp/yaml.h>
#include <sharedstorage/sharedstrings.hpp>

#define CONFIG_SECTION_NAME "drivelineUart"

DrivelineInterfaceUart::DrivelineInterfaceUart()
:DrivelineInterface("DrivelineInterfaceUart")
{

}

DrivelineInterfaceUart::~DrivelineInterfaceUart()
{

}

bool DrivelineInterfaceUart::init()
{
    _log->info("Initialization started.");

    if(!DrivelineInterface::init(CONFIG_SECTION_NAME))
    {
        return false;
    }

    if(!_enabled){
        _log->info("Completed with no initialization as set in config.");
        return true;
    }
    
    YAML::Node config = YAML::LoadFile(SharedStrings::get()->getVal("config-file"));
    _portName = config[CONFIG_SECTION_NAME]["comPort"].as<std::string>();
    _log->info("Using port [{}]", _portName);

    _fdPort = open(_portName.c_str(), O_RDWR);
    if(_fdPort < 0)
    {
        _log->error("Unable to open [{}] for R/W due to error [{}] [{}]", _portName, errno, strerror(errno));
        return false;
    }

    struct termios tty;
    memset(&tty, 0, sizeof tty);

    if(tcgetattr(_fdPort, &tty) != 0) 
    {
        _log->error("Unable to read existing port configuration due to error [{}] [{}]", errno, strerror(errno));
        close(_fdPort);
        return false;
    }

    tty.c_cflag &= ~PARENB; // Clear parity bit, disabling parity (most common)
    tty.c_cflag &= ~CSTOPB; // Clear stop field, only one stop bit used in communication (most common)
    tty.c_cflag |= CS8;     // 8 bits per byte (most common)
    tty.c_cflag &= ~CRTSCTS;// Disable RTS/CTS hardware flow control (most common)
    tty.c_cflag |= CREAD | CLOCAL; // Turn on READ & ignore ctrl lines (CLOCAL = 1)
    tty.c_lflag &= ~ICANON;
    tty.c_lflag &= ~ECHO; // Disable echo
    tty.c_lflag &= ~ISIG; // Disable interpretation of INTR, QUIT and SUSP
    tty.c_iflag &= ~(IXON | IXOFF | IXANY); // Turn off s/w flow ctrl
    tty.c_iflag &= ~(IGNBRK|BRKINT|PARMRK|ISTRIP|INLCR|IGNCR|ICRNL); // Disable any special handling of received bytes
    tty.c_oflag &= ~OPOST; // Prevent special interpretation of output bytes (e.g. newline chars)
    tty.c_oflag &= ~ONLCR; // Prevent conversion of newline to carriage return/line feed
    // tty.c_oflag &= ~OXTABS; // Prevent conversion of tabs to spaces (NOT PRESENT IN LINUX)
    // tty.c_oflag &= ~ONOEOT; // Prevent removal of C-d chars (0x004) in output (NOT PRESENT IN LINUX)
    tty.c_cc[VTIME] = 0;    // return immediately with whatever is available
    tty.c_cc[VMIN] = 0;
    // Set in/out baud rate to be 9600
    cfsetispeed(&tty, B115200);
    cfsetospeed(&tty, B115200);

    if (tcsetattr(_fdPort, TCSANOW, &tty) != 0) 
    {
        _log->error("Unable to write port configuration due to error [{}] [{}]", errno, strerror(errno));
        close(_fdPort);
        return false;
    }

    _log->info("Initialization finished.");
    return true;

}

bool DrivelineInterfaceUart::txCmd(std::string source, unsigned char vLeft, unsigned char vRight)
{
    vLeft  &= 0xF7;
    vRight &= 0xF7;

    _driveline_history_left.push_back(vLeft);
    _driveline_history_right.push_back(vRight);

    if(_driveline_history_left.size() > _telemetry_frame_height)
    {
        _driveline_history_left.pop_front();
        _driveline_history_right.pop_front();
    }

    uint8_t driveline_packet[2] = {vLeft, vRight};

    if(!_enabled){
        return true;
    }

    if(_extra_trace_enabld)
    {
        _log->trace("[{}] L[{}] R[{}]", source, driveline_packet[0], driveline_packet[1]);
    }

    int writeCount = write(_fdPort, driveline_packet, sizeof(driveline_packet));
    if(writeCount == -1)
    {
        _log->error("Error writing to port.");
        return false;
    }
    
    return true;
}


void DrivelineInterfaceUart::doRx()
{
    
}

void DrivelineInterfaceUart::onCleanup()
{
    close(_fdPort);
}