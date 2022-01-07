#include "drivelineinterfaceUdp.hpp"
#include <yaml-cpp/yaml.h>
#include "shared/utils/sharedstrings.hpp"

#define CONFIG_SECTION_NAME "drivelineUdp"

DrivelineInterfaceUdp::DrivelineInterfaceUdp()
:DrivelineInterface("DrivelineInterfaceUdp")
{

}

DrivelineInterfaceUdp::~DrivelineInterfaceUdp()
{

}

bool DrivelineInterfaceUdp::init()
{
    _log->info("Initialization started.");

    
    YAML::Node config = YAML::LoadFile(SharedStrings::get()->getVal("config-file"));

    if ((_sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0){
        _log->error("Unable to open datagram socket.");
        return false;
    }

    if ((_sockrx = socket(AF_INET, SOCK_DGRAM, 0)) < 0){
        _log->error("Unable to open datagram socket.");
        return false;
    }

    memset(&_tx_addr, 0, sizeof(_tx_addr));
    _tx_addr.sin_family = AF_INET;
    _tx_addr.sin_port = (in_port_t) htons(config[CONFIG_SECTION_NAME]["motorDriverPort"].as<int>());
    inet_aton(
        config[CONFIG_SECTION_NAME]["motorDriverIp"].as<std::string>().c_str(), 
        &_tx_addr.sin_addr
    );

    memset(&_rx_addr, 0, sizeof(_rx_addr));
    _rx_addr.sin_family = AF_INET;
    _rx_addr.sin_port = (in_port_t) htons(config[CONFIG_SECTION_NAME]["heartbeatPort"].as<int>());
    inet_aton(
        "0.0.0.0", 
        &_rx_addr.sin_addr
    );

    if (bind(_sockrx, (struct sockaddr *) &_rx_addr, sizeof(_rx_addr))) 
    {
        _log->error("Unable to bind for heartbeat socket.");
        return false;
    }

    _log->info("Motor Driver Host: [{}]", config[CONFIG_SECTION_NAME]["motorDriverIp"].as<std::string>());
    _log->info("Motor Driver Port: [{}]", config[CONFIG_SECTION_NAME]["motorDriverPort"].as<int>());
    _log->info("Heartbeat listen Port: [{}]", config[CONFIG_SECTION_NAME]["heartbeatPort"].as<int>());


    if(!DrivelineInterface::init(CONFIG_SECTION_NAME))
    {
        return false;
    }

    _log->info("Initialization finished.");
    return true;

}

bool DrivelineInterfaceUdp::txCmd(std::string source, unsigned char vLeft, unsigned char vRight)
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

    if (sendto(_sockfd, driveline_packet, 2, 0,
                   (struct sockaddr*) &_tx_addr, sizeof(_tx_addr)) < 0)
    {
        _log->error("Unable to send packet.");
        return false;
    }
    return true;
}

void DrivelineInterfaceUdp::doRx()
{
    _log->debug("Entered heartbeat RX task.");

    char data[100];
    int data_size_expected = sizeof(data);
    struct sockaddr_in sender_address; 
    socklen_t sender_addr_len = sizeof(sockaddr_in);

    while(_keep_running)
    {
        if(isDataAvailableForRead(_sockrx) == 0)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            continue;
        }
         
        memset(data,0,sizeof(data));
        if(read(_sockrx, data, sizeof(data)) > 0)
        {           
            data[100] = 0; //ensure we have null termination...

            //_log->trace("Received heartbeat [{}]", data);
            updateLastRxTime();
        }else{
            _log->error("Error reding from socket, Rx thread exiting.");
            break;
        }
    }
    _log->debug("Exiting heartbeat RX task.");
}