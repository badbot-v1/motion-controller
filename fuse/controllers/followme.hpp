#pragma once

#include <mtlog/badbotlogger.hpp>
#include <sharedstorage/sharedstrings.hpp>
#include <atomic>
#include <thread>
#include <boost/signals2.hpp>
#include "controllerbase.hpp"
#include "follow_fsm.hpp"

using namespace std;
using namespace boost;

using fsm_handle = FollowStage;

class FollowMeController :  public ControllerBase
{

    protected:

        //min dist when to stop moving, max distance how much to act within
        int _DIST_MIN;
        int _DIST_MAX;

        int _CORRECTIVE_MID_THRESHOLD;
        int _MAX_ALLOWED_DEVIATION; //how far away from center the person can be, this directly influences the reactivity of orientation from robot
        

    public:
        FollowMeController();
        bool init();
        bool cleanup();
        void calculateNextFrame();

        void setActive(bool state) override;

        //How near to the target before bot should stop moving
        int getMinDistanceThresholdToTarget();

        //How far from target after which we give up following
        int getMaxDistanceThresholdToTarget();

        //How far from center of bot the target should be before we take corrective measure to align orientation
        //with target
        int getCorrectiveMidThreshold();

        //How far the target can be (in degrees) to be considered at the extreme
        int getMaxAllowedDeviation();
        
};