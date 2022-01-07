#pragma once

#include <mtlog/badbotlogger.hpp>
#include <sharedstorage/sharedstrings.hpp>
#include <thread>
#include <chrono>

#include <boost/signals2.hpp>
#include "controllerbase.hpp"

using namespace std;
using namespace boost;

class TeleopController :  public ControllerBase
{

    protected:
        //min dist when to stop moving, max distance how much to act within
        int _OBSTACLE_DIST;
        int vX;
        int vY;

    public:
        TeleopController();
        bool init();
        bool cleanup();
        void calculateNextFrame();
        void setVelocity(int vX, int vY);
};