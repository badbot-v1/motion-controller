#include "sensors_state.hpp"


#define MAX_NO_UPDATE_DURATION 100 //todo: get from config

atomic<int> SensorsState::_imu_heading(0);
atomic<int> SensorsState::_distToTarget(0);
atomic<int> SensorsState::_angleToTarget(0);
atomic<int> SensorsState::_relative_angle_to_target(0);
std::chrono::time_point<std::chrono::system_clock> SensorsState::_last_updated_inputs_at(std::chrono::system_clock::now());

int SensorsState::getImuHeading()
{
    return _imu_heading;
}

void SensorsState::setImuHeading(int heading)
{
    _imu_heading = heading;
}

void SensorsState::updateLastInputRxTime()
{
    _last_updated_inputs_at = std::chrono::system_clock::now();
}


bool SensorsState::isInputStillValid()
{
    auto now = std::chrono::system_clock::now();
    auto diff = std::chrono::duration_cast<std::chrono::milliseconds>(now - _last_updated_inputs_at);   

    if(diff.count() < MAX_NO_UPDATE_DURATION) //todo revise
    {
        return true;
    }

    return false;
}


void SensorsState::setDistToTarget(int distToTarget)
{
    _distToTarget = distToTarget;
}

void SensorsState::setAngleToTarget(int angleToTarget)
{
    _angleToTarget = angleToTarget;

    updateLastInputRxTime();
}

void SensorsState::setRelativeAngleToTarget(int angleToTarget)
{
    _relative_angle_to_target = angleToTarget;
}

void SensorsState::setTargetParameters(int distToTarget, int angleToTarget)
{
    _distToTarget = distToTarget;
    //_angleToTarget = abs(angleToTarget) > 15 ? (angleToTarget > 0 ? 15 : -15) : angleToTarget;
    _angleToTarget = angleToTarget;

    updateLastInputRxTime();
}

int SensorsState::getDistToTarget()
{
    if(!isInputStillValid())
    {
        return CONTROLLER_INVALID_VALUE;
    }
    
    return _distToTarget;
}

int SensorsState::getAngleToTarget(bool checkValidity)
{
    if(checkValidity && !isInputStillValid())
    {
        return CONTROLLER_INVALID_VALUE;
    }

    return _angleToTarget;
}


int SensorsState::getRelativeAngleToTarget()
{
    return _relative_angle_to_target;
}