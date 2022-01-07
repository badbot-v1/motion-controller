#include "fuse.hpp"
#include <iostream>
#include <iostream>
#include <string>
#include <iomanip>
#include <algorithm>
#include <sys/sysinfo.h>
#include <cctype>
#include <yaml-cpp/yaml.h>
#include <sharedstorage/sharedstrings.hpp>
#include "shared/system/sysevents.hpp"
#include "videoframe.pb.h"

using namespace std;

void Fuse::telemetry_proc()
{

    auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::system_clock::now() - _telemetry_last_published_at
    );
    
    if(
        milliseconds.count()
        < 
        _telemetry_publish_interval_ms
    )
    {
        return;
    }

    _telemetry_last_published_at = std::chrono::system_clock::now();

    BadMessage teleMsg;
    
    teleMsg.set_msgtype(MessageType::STATUS_BOT);
    BotStatus *botStatus = new BotStatus();
    teleMsg.set_allocated_status(botStatus);
    
    botStatus->set_mode(_op_mode);
    botStatus->set_lidarenabled(_lidar->getEnabled());
    botStatus->set_lidarrecordingenabled(_lidar->isRecording());
    botStatus->set_appsrcenabled(false);
    botStatus->set_wsvideoenabled(false);
    botStatus->set_telemetryenabled(_telemetry_enabled);
    botStatus->set_imuhealthy(_imu.isHealthy());
    botStatus->set_gpshealthy(_gps.isHealthy());
    botStatus->set_motorcontrollerhealthy(_driveline_if.isHealthy());

    tele_getCpuLoadAverage(botStatus);

    _messaging.txMsg(&teleMsg);
}


void Fuse::tele_getCpuLoadAverage(BotStatus *botStatus)
{
    badbot::messages::SystemLoadAvg *loadAvg = new badbot::messages::SystemLoadAvg();
    botStatus->set_allocated_sysloadavg(loadAvg);

    double sysCpuLoadAverages[3] = {0.0, 0.0, 0.0};
    getloadavg(sysCpuLoadAverages, 3);

    loadAvg->set_onemin(static_cast<float>(sysCpuLoadAverages[0]));
    loadAvg->set_fivemin(static_cast<float>(sysCpuLoadAverages[1]));
    loadAvg->set_fifteenmin(static_cast<float>(sysCpuLoadAverages[2]));

    struct sysinfo sinfo;
    sysinfo(&sinfo);
    loadAvg->set_numcores(std::thread::hardware_concurrency());
    loadAvg->set_totalram(sinfo.totalram);
    loadAvg->set_freeram(sinfo.freeram);
    loadAvg->set_totalswap(sinfo.totalswap);
    loadAvg->set_freeswap(sinfo.freeswap);
}

//Note to faisal - implement the driveline telemetry tx

void Fuse::tele_txDrivelineData(unsigned char vLeft, unsigned char vRight)
{
    BadMessage teleMsg;
    
    teleMsg.set_msgtype(MessageType::TELE_DRIVELINE_STATUS);
    DrivelineStatus *status = new DrivelineStatus();
    teleMsg.set_allocated_drivelinestatus(status);

    status->set_vleft(vLeft);
    status->set_vright(vRight);

    _messaging.txMsg(&teleMsg);
}