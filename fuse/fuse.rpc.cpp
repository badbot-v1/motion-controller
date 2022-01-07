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


void Fuse::on_rpc_msg(const BadMessage *msg)
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
                case Devices::LIDAR:
                    _lidar->setLaserState(msg->togglecmd().enable());
                break;

                case Devices::LIDAR_RECORD:
                    _lidar->toggleRecording(msg->togglecmd().enable());
                break;

                // case Devices::APPSRC:
                //     _appSrc.toggleEnabled(msg->togglecmd().enable());
                // break;

                // case Devices::WS_VIDEO:
                //     // _media_conversion.toggleEnabled(msg->togglecmd().enable());
                //     _ws_video_enabled = msg->togglecmd().enable();
                // break;

                case Devices::TELEMETRY:
                    _telemetry_enabled = msg->togglecmd().enable();
                break;

                default:
                    _log->warn("Unhandled toggle device.");
            }
        }
        break;

        case MessageType::CMD_TELEOP_MOVEMENT:
        {
            onTeleMove(msg);
        }
        break;

        case MessageType::CMD_OPERATIONAL_MODE:
        {
            _log->info("Setting operational mode to [{}].",OperationalMode_Name(msg->opmode().opmode()));
            _op_mode = msg->opmode().opmode();

            _ctrlr_teleop.setActive(false);
            _ctrlr_followme.setActive(false);
            
            switch(msg->opmode().opmode())
            {
                case OperationalMode::IDLE:
                {
                    //do nothing
                    setObjectDetectionEnabled(false);
                }
                break;

                case OperationalMode::AUTONOMOUS:
                {
                    setObjectDetectionEnabled(false);
                }
                break;

                case OperationalMode::FOLLOW_ME:
                {
                    setObjectDetectionEnabled(true);
                    _ctrlr_followme.setActive(true);
                }
                break;

                case OperationalMode::TELEOP:
                {
                    setObjectDetectionEnabled(false);
                    _ctrlr_teleop.setActive(true);
                }
                break;

                default:
                {
                    _log->warn("Don't know how to handle requested operational mode.");
                }
                break;
            }
        }
        break;

        case VPM_OBJ_DET_COORDS:
        {
            if(_op_mode == OperationalMode::FOLLOW_ME)
            {
                SensorsState::setAngleToTarget(msg->objcoords().object_at_angle());

                if(objDetContainsClass(0,msg))
                {
                    fsm_handle::dispatch(TargetAcquired());

                }else{

                    fsm_handle::dispatch(TargetLost());
                }
            }

            //make a copy of message we received
            BadMessage txMsg;
            txMsg.CopyFrom(*msg);
            
            //send to remote as telemetry
            _messaging.txMsg(&txMsg);

            _vpm_last_rx_at = std::chrono::system_clock::now();
            _objCoords.CopyFrom(msg->objcoords());

            for(int i=0; i<_objCoords.coordinates_size();i++)
            {
                const badbot::messages::Coords& coords=_objCoords.coordinates(i);
                _log->debug(
                    "{}. Class: [{}] [y,x,h,w: %] [{},{},{},{}: {}] @[{}]",
                    i, coords.objid(), coords.y(), coords.x(), coords.h(), coords.w(), coords.confidence(), _objCoords.object_at_angle());
            }

        }
        break;

        default:
            _log->info("received ws message, not implemented");
        break;
    }

}
