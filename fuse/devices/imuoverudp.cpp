#include "imuoverudp.hpp"  
#include <yaml-cpp/yaml.h>
#include "shared/utils/sharedstrings.hpp"
#include "shared/system/sysevents.hpp"

#define CONFIG_SECTION_NAME "sensors_imu"

ImuOverUdp::ImuOverUdp()
:SensorBase("ImuOverUdp")
{
    
}

ImuOverUdp::~ImuOverUdp()
{

}

bool ImuOverUdp::init()
{
    _log->info("Initialization started.");

    SensorBase::init(CONFIG_SECTION_NAME);

    YAML::Node config = YAML::LoadFile(SharedStrings::get()->getVal("config-file"));

    if ((_sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0){
        _log->error("Unable to open datagram socket.");
        return false;
    }

    memset(&_rx_addr, 0, sizeof(_rx_addr));
    
    _rx_addr.sin_family = AF_INET;
    _rx_addr.sin_port = (in_port_t) htons(config[CONFIG_SECTION_NAME]["rxport"].as<int>());
    inet_aton(
        config[CONFIG_SECTION_NAME]["rxip"].as<std::string>().c_str(), 
        &_rx_addr.sin_addr
    );

    _log->info(
        "Listening on ip:port: [{}:{}]", 
        config[CONFIG_SECTION_NAME]["rxip"].as<std::string>(),
        config[CONFIG_SECTION_NAME]["rxport"].as<std::string>()
    );

    if ( ::bind(_sockfd, (const struct sockaddr *)&_rx_addr,  
            sizeof(_rx_addr)) < 0 ) 
    { 
        _log->error("Unable to bind socket for listening.");
        return false;
    } 

    _log->info("Initialization finished.");
    return true;

}

void ImuOverUdp::cleanup()
{
    _log->info("Cleanup started.");

    ::shutdown(_sockfd, SHUT_RDWR);
    ::close(_sockfd);
    
    _log->info("Cleanup completed.");
}


void ImuOverUdp::connecToSignalIMUData(const slot_imu &slot)
{
    _signalIMU.connect(slot);
}

void ImuOverUdp::thread_proc()
{
    _log->info("Rx thread started.");
    int data_size_expected = sizeof(TELEMETRY_IMU);
    struct sockaddr_in sender_address; 
    socklen_t sender_addr_len = sizeof(sockaddr_in);

    while(_keep_running)
    {
        std::shared_ptr<TELEMETRY_IMU> imu_data = std::make_shared<TELEMETRY_IMU>();

        recvfrom(_sockfd, (char *)imu_data.get(), data_size_expected,  
            MSG_WAITALL, ( struct sockaddr *) &sender_address, 
            &sender_addr_len);

        _signalIMU(imu_data);

        updateLastRxTime();
    }

    _log->info("Rx thread exited.");
}
