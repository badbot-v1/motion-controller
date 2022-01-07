#include "fuse.hpp"
#include <iostream>
#include <iostream>
#include <string>
#include <iomanip>
#include <algorithm>
#include <cctype>
#include <yaml-cpp/yaml.h>
#include <sharedstorage/sharedstrings.hpp>
#include "shared/system/sysevents.hpp"
#include "shared/system/sensors_state.hpp"

using namespace std;

void Fuse::loop()
{
    while (_keep_running)
    {
        telemetry_proc();

        if(_op_mode == OperationalMode::FOLLOW_ME)
        {
            int targetAtAngle = SensorsState::getAngleToTarget();
            if(targetAtAngle != CONTROLLER_INVALID_VALUE)
            {
                SensorsState::setDistToTarget
                (
                    _lidar->getDistanceToRoi
                    (
                        targetAtAngle-10,
                        targetAtAngle+10,
                        _follower_min_dist, 
                        _follower_max_dist,
                        10
                    )
                );
            }
        }
        
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}