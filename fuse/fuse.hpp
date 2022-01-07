#pragma once

#include <mtlog/badbotlogger.hpp>
#include <thread>
#include <atomic>
#include <memory>
#include "fuse/devices/driveline/drivelineinterfaceUdp.hpp"  
#include "fuse/devices/driveline/drivelineinterfaceUart.hpp"  
#include "lidar.hpp"
#include "fuse/controllers/followme.hpp"
#include "fuse/controllers/teleop.hpp"
#include "consts.pb.h"
#include "message.pb.h"

#include "fuse/devices/imuoverudp.hpp"
#include "fuse/devices/gps.hpp"

#include "shared/messaging/messaging_server.hpp"
#include "shared/messaging/cppsrc/obj_det_coords.pb.h"

using namespace badbot::messages;
using namespace std;

class Fuse : BadBotLogger
{
public:
    Fuse();
    int main(int argc, char** argv);
    void on_follower_SignalDrivelineCmd(std::string source, unsigned char vLeft, unsigned char vRight);
    void on_rpc_msg(const BadMessage *msg);


protected:
    bool _keep_running = false;
    bool _telemetry_enabled = false;
    int _telemetry_publish_interval_ms = 1000;
    int _follower_min_dist = 3; //overridden by config
    int _follower_max_dist = 7; //overridden by config
    int _cnn_dist_target = 0; //set by calling lidar to get distance in follower _op_mode

    //when did we last receive an object detection report?
    //used with follow me mode
    std::chrono::time_point<std::chrono::system_clock> _vpm_last_rx_at;
    badbot::messages::ObjectDetectionCoords _objCoords;
    

    /**
     * 
     * used in telemetry publishing to determine if an update should be sent
     * 
     */
    std::chrono::time_point<std::chrono::system_clock> _telemetry_last_published_at;

    OperationalMode _op_mode = OperationalMode::IDLE;

    DrivelineInterfaceUdp _driveline_if;
    MessagingServer _messaging;
    MessagingServer _internal_messaging;
    Lidar *_lidar;
    FollowMeController _ctrlr_followme;
    TeleopController _ctrlr_teleop;
    ImuOverUdp _imu;
    GpsSensor _gps;

protected:
    void telemetry_proc();
    void onSysShutdown();
    bool validateOptions(int argc, char **argv);
    bool init(int argc, char **argv);
    void loop();
    void onTeleMove(const BadMessage *msg);
    void onImuDataRx(std::shared_ptr<TELEMETRY_IMU> data);
    void onGpsDataRx(badbot::messages::GpsData *data);
    void onLidarScanAvailable(badbot::messages::LidarScan* lidarScan, bool isPointsOfInterestScan);
    void tele_getCpuLoadAverage(BotStatus *botStatus);
    void tele_txDrivelineData(unsigned char vLeft, unsigned char vRight);

    void setObjectDetectionEnabled(bool enabled);

    bool objDetContainsClass(int objClass, const BadMessage *msg);
};