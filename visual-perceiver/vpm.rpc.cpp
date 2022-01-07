#include "vpm.hpp"
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


void VisualPerceptionModule::on_rpc_msg(const BadMessage *msg)
{
    switch(msg->msgtype())
    {
        case MessageType::HEARTBEAT_RC:
        {
            //do nothing
        }
        break;

        case MessageType::CMD_TOGGLE:
        {
            _log->info("Toggling [{}] with [{}]", Devices_Name(msg->togglecmd().device()), msg->togglecmd().enable());
            switch(msg->togglecmd().device())
            {
                case Devices::OBJECT_DETECTION:
                    
                    if(msg->togglecmd().enable())
                    {
                        _kalman.reset(0.5f, 5.0f); //estimating the person to follow is in front
                    }
                    
                    _kalman.setActive(msg->togglecmd().enable());
                    _object_detection_enabled = msg->togglecmd().enable();

                    _log->debug("Toggled object detection to [{}]", _object_detection_enabled);
                break;

                default:
                    _log->warn("Unhandled toggle device.");
            }
        }
        break;

        default:
            _log->info("received ws message, not implemented");
        break;
    }

}
