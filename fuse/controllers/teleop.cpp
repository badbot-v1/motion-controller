#include "teleop.hpp"
#include "shared/system/sensors_state.hpp"
#include <yaml-cpp/yaml.h>
#include <chrono>

TeleopController::TeleopController() 
: ControllerBase("TeleopController")
{

}

bool TeleopController::init()
{
    bool bRet = false;
    try{
        bRet = ControllerBase::init("ctrlr_teleop");

        YAML::Node config = YAML::LoadFile(SharedStrings::get()->getVal("config-file"));
        //_DEADZONE_MIN is the JS deadzone
        _DEADZONE_MIN = config["ctrlr_teleop"]["deadzoneMin"].as<int>();
        _OBSTACLE_DIST = config["ctrlr_teleop"]["obstacle_dist"].as<int>();
        

        _log->info("_DEADZONE_MIN/JS DEADZONE [{}]",_DEADZONE_MIN);
        _log->info("_OBSTACLE_DIST [{}]",_OBSTACLE_DIST);

        _log->info("Init result [{}].", bRet);


        bRet = true;

    }catch(...){
        std::exception_ptr p = std::current_exception();
        _log->error((p ? p.__cxa_exception_type()->name() : "null"));
    }


    return bRet;
}

bool TeleopController::cleanup()
{
    return ControllerBase::cleanup();
}

void TeleopController::setVelocity(int vX, int vY)
{
    this->vX = vX;
    this->vY = vY;

    updateLastInputRxTime();
}


void TeleopController::calculateNextFrame()
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

        

        unsigned char left_motor_speed = 0;
        unsigned char right_motor_speed = 0;

        //save function call below
        auto abs_vY = abs(vY);

        //simple case, joystick is vertically at mid or below, so we turn
        if(vY <= 0 && abs_vY > _DEADZONE_MIN){

            if(vX <0){
                right_motor_speed = 255;
            }else if(vX > 0){
                left_motor_speed = 255;
            }
            
        }else if(vY > 0 && abs_vY > _DEADZONE_MIN){

            left_motor_speed = 255;
            right_motor_speed = 255;

            //reduce by where the JS is on x axis
            if(vX != 0 && abs(vX) >= _DEADZONE_MIN)
            {
                float proportion = 1.0 - (abs(vX) / 100.0);

                if(vX < 0){
                    //reduce left motor speed
                    left_motor_speed *= proportion;
                }else{
                    right_motor_speed *= proportion;
                }
            }
        }

        if(vY != 0)
        {
            if(!isInputStillValid())
            {
                vY = 0;
                vX = 0;
            }
        }

        _signalDrivelineCmd("TeleopController", left_motor_speed, right_motor_speed);
        std::this_thread::sleep_for(std::chrono::milliseconds(_CMD_CALCULATION_FREQUENCY));

    }
}