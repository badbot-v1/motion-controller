#pragma once

#include <atomic>
#include <chrono>

#define CONTROLLER_INVALID_VALUE -10000

using namespace std;

class SensorsState
{
    private:
        static atomic<int> _imu_heading;

        static atomic<int> _distToTarget;
        static atomic<int> _angleToTarget;

        //set from follow fsm before transitioning into orienting state
        static atomic<int> _relative_angle_to_target;


        //safety feature, how long since we last got a sensor update?
        //if we do not get updated in _MAX_NO_UPDATE_DURATION we stop issuing commands
        static std::chrono::time_point<std::chrono::system_clock> _last_updated_inputs_at;

    protected:
        /**
         * updates the member field _last_updated_inputs_at with current system clock timepoint
         */
        static void updateLastInputRxTime();


    public:
        SensorsState();

        static int getImuHeading();
        static void setImuHeading(int heading);

        static void setTargetParameters(int distToTarget, int angleToTarget);
        
        static void setDistToTarget(int distToTarget);
        static int getDistToTarget();
        
        static void setAngleToTarget(int angleToTarget);
        static int getAngleToTarget(bool checkValidity = true);

        static void setRelativeAngleToTarget(int angleToTarget);
        static int getRelativeAngleToTarget();

        /**
         * Utility function that takes returns true if
         *  current time - _last_updated_inputs_at < _MAX_NO_UPDATE_DURATION
         * or false otherwise
         */
        static bool isInputStillValid();
};