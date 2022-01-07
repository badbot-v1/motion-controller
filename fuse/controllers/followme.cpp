#include "followme.hpp"
#include <yaml-cpp/yaml.h>
#include <chrono>
#include "shared/system/sensors_state.hpp"


//**************************************************************
//**************************************************************
//**************************************************************
//**************************************************************
//**************************************************************
/***************************************************************
 * 
 * 
 * Followme Controller implementation follows
 * 
 */
//**************************************************************
//**************************************************************
//**************************************************************
//**************************************************************
//**************************************************************

FollowMeController::FollowMeController()
: ControllerBase("FollowMeController")
{
    fsm_handle::start();
}

bool FollowMeController::init()
{
    bool bRet = false;

    try{

        bRet = ControllerBase::init("ctrlr_followme");

        YAML::Node config = YAML::LoadFile(SharedStrings::get()->getVal("config-file"));
        _DEADZONE_MIN = config["ctrlr_followme"]["deadzoneMin"].as<int>();
        _DEADZONE_MAX = config["ctrlr_followme"]["deadzoneMax"].as<int>();
        _DIST_MIN = config["ctrlr_followme"]["distMin"].as<int>();
        _DIST_MAX = config["ctrlr_followme"]["distMax"].as<int>();
        _CORRECTIVE_MID_THRESHOLD = config["ctrlr_followme"]["correctiveMidThreshold"].as<int>();
        _MAX_ALLOWED_DEVIATION = config["ctrlr_followme"]["max_allowed_deviation"].as<int>();

        _log->info("_DEADZONE_MIN [{}]",_DEADZONE_MIN);
        _log->info("_DEADZONE_MAX [{}]",_DEADZONE_MAX);
        _log->info("_DIST_MIN [{}]",_DIST_MIN);
        _log->info("_DIST_MAX [{}]",_DIST_MAX);
        _log->info("_CORRECTIVE_MID_THRESHOLD [{}]",_CORRECTIVE_MID_THRESHOLD);
        _log->info("_MAX_ALLOWED_DEVIATION [{}]",_MAX_ALLOWED_DEVIATION);

        bRet = true;

    }catch(...){
        std::exception_ptr p = std::current_exception();
        _log->error((p ? p.__cxa_exception_type()->name() : "null"));
    }


    return bRet;
}

bool FollowMeController::cleanup()
{
    return ControllerBase::cleanup();
}



void FollowMeController::calculateNextFrame()
{
    while(_keep_running)
    {      
        if(!_active_controller)
        {
            if(!_keep_running)
            {
                return;
            }

            std::this_thread::sleep_for(std::chrono::seconds(1));
            continue;
        }

        //invoke fsm
        ClockTick tick;
        tick.controller = this;
        tick.logger = _log;
        fsm_handle::dispatch(tick);

        //sleep b/w invocations
        std::this_thread::sleep_for(std::chrono::milliseconds(_CMD_CALCULATION_FREQUENCY));      
    }

    _log->warn("Exiting calculation loop.");
}

int FollowMeController::getMinDistanceThresholdToTarget()
{
    return _DIST_MIN;
}

int FollowMeController::getMaxDistanceThresholdToTarget()
{
    return _DIST_MAX;
}

int FollowMeController::getCorrectiveMidThreshold()
{
    return _CORRECTIVE_MID_THRESHOLD;
}

int FollowMeController::getMaxAllowedDeviation()
{
    return _MAX_ALLOWED_DEVIATION;
}



void FollowMeController::setActive(bool state)
{
    if(!state)
    {
        fsm_handle::dispatch(ModeIdle());
    }else{
        fsm_handle::dispatch(ModeFollow());
    }
    ControllerBase::setActive(state);
}
