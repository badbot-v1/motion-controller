#include "fuse.hpp"
#include <iostream>
#include <iostream>
#include <string>
#include <iomanip>
#include <algorithm>
#include <cctype>
#include <yaml-cpp/yaml.h>
#include "shared/utils/sharedstrings.hpp"
#include "shared/system/sysevents.hpp"
#include "videoframe.pb.h"

using namespace std;

Fuse::Fuse()
:BadBotLogger("Fuse"),
_messaging("ExternalMessaging"),
_internal_messaging("InternalMessaging")
{
}


int Fuse::main(int argc, char **argv)
{

    SysEvents::getInstance()->connectToSignalShutdown(boost::bind(&Fuse::onSysShutdown, this));

    if(!init(argc,argv))
    {
        return -2;
    }
    
    loop();

    return 0;
}

bool Fuse::init(int argc, char **argv)
{

    YAML::Node config = YAML::LoadFile(SharedStrings::get()->getVal("config-file"));
    _follower_min_dist = config["fuse"]["follower_min_dist"].as<int>();
    _follower_max_dist = config["fuse"]["follower_max_dist"].as<int>();
    _telemetry_publish_interval_ms = config["fuse"]["telemetry_publish_interval_ms"].as<int>();
    
    _log->info("follower_min_dist [{}]", _follower_min_dist);
    _log->info("follower_max_dist [{}]", _follower_max_dist);
    _log->info("telemetry_publish_interval_ms [{}]", _telemetry_publish_interval_ms);
    
    _log->info("Initializing IMU");
    if(_imu.init())
    {
        _imu.connecToSignalIMUData(
            boost::bind(&Fuse::onImuDataRx, this, _1)
        );
        _log->info("IMU initialized successfully.");
    }else
    {
        _log->error("Unable to init IMU. Exiting");
        return false;
    }

    _log->info("Initializing GPS");
    if(_gps.init())
    {
        _gps.connecToSignalGps(
            boost::bind(&Fuse::onGpsDataRx, this, _1)
        );
        _log->info("GPS initialized successfully.");
    }else
    {
        _log->error("Unable to init GPS. Exiting");
        return false;
    }

    _log->info("Initializing LIDAR");
    _lidar = Lidar::instance();
    if(!_lidar->init(argc,argv))
    {
        _log->error("Unable to init lidar. Exiting");
        return false;
    }else{
        _lidar->connecToSignalLidarScanReady(
            boost::bind(&Fuse::onLidarScanAvailable, this, _1, _2)
        );
    }

    _log->info("Initializing Driveline Interface");
    if(!_driveline_if.init())
    {
        return false;
    }

    _log->info("Initializing Follow me controller");
    if(!_ctrlr_followme.init())
    {
        return false;
    }

    _log->info("Initializing Teleop controller");
    if(!_ctrlr_teleop.init())
    {
        return false;
    }
    //by default this is the active controller
    _ctrlr_teleop.setActive(true);

    _ctrlr_followme
        .connectToSignalDrivelineCmd(
            boost::bind(&Fuse::on_follower_SignalDrivelineCmd, this, _1, _2, _3)
        );

    _ctrlr_teleop
        .connectToSignalDrivelineCmd(
            boost::bind(&Fuse::on_follower_SignalDrivelineCmd, this, _1, _2, _3)
        );

    _log->info("Initializing messaging.");
    _messaging.init("external_messaging");
    _messaging.connectToSignalMessage(
        boost::bind(&Fuse::on_rpc_msg, this, _1)
    );

    _log->info("Initializing Internal messaging.");
    _internal_messaging.init("internal_messaging");
    _internal_messaging.connectToSignalMessage(
        boost::bind(&Fuse::on_rpc_msg, this, _1)
    );

    _telemetry_last_published_at = std::chrono::system_clock::now();
    
    _keep_running = true;

    return true;
}

void Fuse::onSysShutdown()
{
    _log->info("Shut down started.");

    _keep_running = false;

    _log->info("Shut down completed.");
}


void Fuse::setObjectDetectionEnabled(bool enabled)
{
    BadMessage msg;
    msg.set_msgtype(badbot::messages::MessageType::CMD_TOGGLE);
    
    CommandToggle *tog = new CommandToggle();
    msg.set_allocated_togglecmd(tog);

    tog->set_device(badbot::messages::Devices::OBJECT_DETECTION);
    tog->set_enable(enabled);

    _internal_messaging.txMsg(&msg);

    _log->debug("Changed object detection to [{}].", enabled);
}

bool Fuse::objDetContainsClass(int objClass, const BadMessage *msg)
{
    auto objCoords = msg->objcoords();
    for(int i=0; i<objCoords.coordinates_size();i++)
    {
        const badbot::messages::Coords& coords = objCoords.coordinates(i);
        if(coords.objid() == objClass)
        {
            return true;
        }
    }    

    return false;
}