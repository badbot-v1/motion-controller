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
#include "shared/system/sensors_state.hpp"

#include "fuse/devices/imuoverudp.hpp"

#include "videoframe.pb.h"
#include "imudata.pb.h"
#include "gpsdata.pb.h"
#include "message.pb.h"

using namespace std;

void Fuse::on_follower_SignalDrivelineCmd(std::string source, unsigned char vLeft, unsigned char vRight)
{
    _driveline_if.txCmd(source, vLeft, vRight);
    tele_txDrivelineData(vLeft, vRight);
}


void Fuse::onTeleMove(const BadMessage *msg)
{
    if(_op_mode != OperationalMode::TELEOP)
    {
        return;
    }

    auto cmd = msg->cmdvel();
    _ctrlr_teleop.setVelocity(cmd.vx(), cmd.vy());

}

void Fuse::onImuDataRx(std::shared_ptr<TELEMETRY_IMU> data)
{

    //update sensors store with latest data
    SensorsState::setImuHeading(data->yaw);

    //send telemetry message
    BadMessage teleMsg;
    
    teleMsg.set_msgtype(MessageType::TELE_IMU);
    badbot::messages::ImuData *imuData = new badbot::messages::ImuData();
    teleMsg.set_allocated_imudata(imuData);
    
    //set fields
    badbot::messages::Tuple *acceleration = new badbot::messages::Tuple();
    acceleration->set_x(data->ax);
    acceleration->set_y(data->ay);
    acceleration->set_z(data->az);
    imuData->set_allocated_acceleration(acceleration);

    badbot::messages::Tuple *orientation = new badbot::messages::Tuple();
    orientation->set_x(data->yaw);
    orientation->set_y(data->pitch);
    orientation->set_z(data->roll);
    imuData->set_allocated_orientation(orientation);

    imuData->set_temperature(data->temperature);
    imuData->set_pressure(data->pressure);
    imuData->set_altitude(data->altitude);

    _messaging.txMsg(&teleMsg);
}

void Fuse::onLidarScanAvailable(badbot::messages::LidarScan* lidarScan, bool isPointsOfInterestScan)
{
    BadMessage teleMsg;
    
    if(!isPointsOfInterestScan)
    {
        teleMsg.set_msgtype(MessageType::TELE_LIDAR);
    }else
    {
        teleMsg.set_msgtype(MessageType::TELE_LIDAR_POI);
    }
    teleMsg.set_allocated_lidarscan(lidarScan);

    _messaging.txMsg(&teleMsg);
}

void Fuse::onGpsDataRx(badbot::messages::GpsData *data)
{
    BadMessage teleMsg;
    
    teleMsg.set_msgtype(MessageType::TELE_GPS);
    teleMsg.set_allocated_gpsdata(data);

    _messaging.txMsg(&teleMsg);
}
