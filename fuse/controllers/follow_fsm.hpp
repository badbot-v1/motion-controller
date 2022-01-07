#pragma once

#include <spdlog/spdlog.h>

#include "shared/fsm/tinyfsm.hpp"
#include "shared/system/sensors_state.hpp"
#include "controllerbase.hpp"


//logger to be used in this fsm
extern spdlog::logger logger_fsm;

/**
 * 
 * 
 * FSM definition follows
 * 
 */

//foward decls

struct FollowStage_Idle;
struct FollowStage_Steering;
struct FollowStage_Orienting;
struct FollowStage_AcquiringTarget;

// ----------------------------------------------------------------------------
// 1. Event Declarations
//
struct ModeIdle : tinyfsm::Event { };
struct ModeFollow : tinyfsm::Event { };

struct ClockTick : tinyfsm::Event 
{
    ControllerBase *controller;
    std::shared_ptr<spdlog::logger> logger;
};

//when we receive an object detection coords list with at least one human
struct TargetAcquired : tinyfsm::Event { }; 

//when we do not received obj detection coords containing at least one human
struct TargetLost : tinyfsm::Event { };


// ----------------------------------------------------------------------------
// 2. State Machine Base Class Declaration
//
struct FollowStage : tinyfsm::Fsm<FollowStage>
{
  virtual void react(ModeIdle const &) { };
  virtual void react(ModeFollow const &) { };
  virtual void react(ClockTick const &) { };
  virtual void react(TargetAcquired const &) { };
  virtual void react(TargetLost const &) { };

  // alternative: enforce handling of Toggle in all states (pure virtual)
  //virtual void react(Toggle const &) = 0;

  virtual void entry(void) { };  /* entry actions in some states */
  virtual void exit(void)  { };  /* exit actions in some states */

  // alternative: enforce entry actions in all states (pure virtual)
  //virtual void entry(void) = 0;
};


// ----------------------------------------------------------------------------
// 3. State Declarations
//
struct FollowStage_Idle : FollowStage
{
    void entry() override 
    { 
        logger_fsm.info("FollowStage_Idle | entry");
    };

    virtual void react(ModeFollow const &e) 
    { 
        transit<FollowStage_Steering>();
    };
};

struct FollowStage_Steering : FollowStage
{
    void entry() override 
    { 
        logger_fsm.info("FollowStage_Steering | entry");
    };

    virtual void react(ModeIdle const &) override
    { 
        transit<FollowStage_Idle>();
    };

    virtual void react(ClockTick const &e) override
    {
        //the minimum amount of calculation we need
        int ang_to_target = SensorsState::getAngleToTarget();
        if(ang_to_target == CONTROLLER_INVALID_VALUE)
        {
            return;
        }

        int ang_to_target_abs = abs(ang_to_target);

        logger_fsm.info("ang_to_target [{}] ang_to_target_abs[{}]",
            ang_to_target,
            ang_to_target_abs
        );


        float percent_deviation = 1.0f - 
        (
            (
                24
                - 
                (float)abs(
                    min(
                        24,
                        ang_to_target_abs
                    )
                )
            )
            /
            24
        );
        percent_deviation *= 100.0f;
        
        
        //refer to documentation
        if(percent_deviation > 70)
        {
            SensorsState::setRelativeAngleToTarget
            (
                SensorsState::getAngleToTarget()
            );

            logger_fsm.info("Switching to orienting, deviation > 70%.");
            transit<FollowStage_Orienting>();
        }
        else
        {
            //calculate speed

            unsigned char left_motor_speed = 255;
            unsigned char right_motor_speed = 255;

            if( false == SensorsState::isInputStillValid())
            {
                left_motor_speed = 0;
                right_motor_speed = 0;
            }
            else if(SensorsState::getDistToTarget() <= 0)
            {
                left_motor_speed = 0;
                right_motor_speed = 0;
            }
            else if
            (
                SensorsState::getDistToTarget() > 0 && 
                SensorsState::getDistToTarget() <= 3
            )
            {
                left_motor_speed = 0;
                right_motor_speed = 0;
            }
            else if
            (
                SensorsState::getDistToTarget() > 0 && 
                SensorsState::getDistToTarget() >= 8
            )
            {
                left_motor_speed = 0;
                right_motor_speed = 0;
            }
            else if
            (
                SensorsState::getDistToTarget() > 0 &&
                SensorsState::getDistToTarget() <= 8
            )
            {
                if(ang_to_target_abs > 5)
                {
                    //we can observe a max of 15 degrees to either side of camera
                    

                    //get reactive force
                    //equation generator http://www.1728.org/threepts.htm
                    //equation plotter https://www.desmos.com/calculator
                    //y=40+\ln\left(x\right)^{2.8}-0.2x
                    // float reactivity = 
                    //       40.0f + powf32(log10f32(percent_deviation), 2.8) - (0.2 * percent_deviation);

                    //https://mycurvefit.com/
                    // float reactivity = 2.256484 + 5.282536*percent_deviation - 0.02775793*powf32(percent_deviation,2);
                    // if(reactivity > 255.0f)
                    // {
                    //     reactivity = 255.0f;
                    // }
                    
                    // if(percent_deviation > 70)
                    // {
                    //     if(e.targetHeading < 0)
                    //     {
                    //         right_motor_speed = 100;
                    //         left_motor_speed  = 0;
                    //     }
                    //     else if (e.targetHeading > 0)
                    //     {
                    //         left_motor_speed = 100;
                    //         right_motor_speed  = 0;
                    //     } 
                    // }
                    // else
                    // {
                    // if(_angleToTarget < 0)
                    //     {
                    //         right_motor_speed  = 200;
                    //         left_motor_speed  = 100;
                    //     }
                    //     else if (_angleToTarget > 0)
                    //     {
                    //         left_motor_speed  = 200;
                    //         right_motor_speed  = 100;
                    //     } 
                    // }



                    // if angle is more to the left, we decrease the speed of left motor
                    // if angle is more to the right, we decrease the speed of the right motor
                    if(SensorsState::getAngleToTarget() < 0)
                    {
                        //right_motor_speed = max(100, 255 - (unsigned char) reactivity);
                        right_motor_speed = percent_deviation * 255.0f;
                        left_motor_speed  = max(255, (int)(150+(255-percent_deviation)));
                    }
                    else
                    {
                        //left_motor_speed = max(100, 255 - (unsigned char) reactivity);
                        left_motor_speed = percent_deviation * 255.0f;
                        right_motor_speed  = max(255, (int)(150+ (255-percent_deviation)));
                    }
                    
                    
                }
            }

            logger_fsm.info
            (
                "Steer [distance {}, angle {}] %dev[{}] reac[{}] lms[{}] rms[{}]", 
                SensorsState::getDistToTarget(),
                SensorsState::getAngleToTarget(),
                percent_deviation, 
                0.0, 
                left_motor_speed, 
                right_motor_speed
            );

            e.controller->raiseDrivelineSignal("Follow::Steer", left_motor_speed, right_motor_speed);
            
        }
    }
};

struct FollowStage_Orienting : FollowStage
{
    //this is the target we chase
    int _absoluteTargetHeading = 0;
    bool _turn_counter_clockwise = false;

    void entry() override 
    { 
        logger_fsm.info("FollowStage_Orienting::entry | begin.");

        int imuHeading = SensorsState::getImuHeading();
        int angleToTarget = SensorsState::getRelativeAngleToTarget();

        logger_fsm.info(
            "imuHeading [{}] angleToTarget [{}]",
            imuHeading,
            angleToTarget
        );

        //since angle To Target is always relative we can add it
        _absoluteTargetHeading = imuHeading + angleToTarget;

        //which way the target was? we will turn that way
        if(_absoluteTargetHeading < 0)
        {
            _absoluteTargetHeading = 360 + _absoluteTargetHeading;
        }else if (_absoluteTargetHeading > 359)
        {
            _absoluteTargetHeading-=360;
        }

        //which way should we turn
        //compass lowers readings when turned anti-clock wise
        if(imuHeading >= 0 && imuHeading < 180)
        {
            if(_absoluteTargetHeading >= 0 && _absoluteTargetHeading < 180)
            {
                _turn_counter_clockwise =  _absoluteTargetHeading < imuHeading;
            }else
            {
                _turn_counter_clockwise = (_absoluteTargetHeading - imuHeading) > 180;
            }
        }else
        {
            if(_absoluteTargetHeading >= 180 && _absoluteTargetHeading < 360)
            {
                _turn_counter_clockwise = _absoluteTargetHeading < imuHeading;
            }else
            {
                _turn_counter_clockwise = (_absoluteTargetHeading - imuHeading) < 180;
            }               
        }

        logger_fsm.info(
            "absoluteTargetHeading [{}] turn_counter_clockwise [{}]",
            _absoluteTargetHeading,
            _turn_counter_clockwise
        );

        logger_fsm.info("FollowStage_Orienting::entry | exit.");        
    };

    virtual void react(ModeIdle const &e) override
    { 
        transit<FollowStage_Idle>();
    };

    virtual void react(ClockTick const &e) override
    {
        //orient robot by
        //burst 
        //wait
        //burst
        //wait
        //....
        
        unsigned char left_motor_speed=0, right_motor_speed=0;
        int imuHeading = SensorsState::getImuHeading();

        //refer to documentation
        if(abs(imuHeading-_absoluteTargetHeading) > 8)
        {
            
            if(_turn_counter_clockwise)
            {
                right_motor_speed = 200;
            }else{
                left_motor_speed = 200;
            }

            e.controller->raiseDrivelineSignal("Follow::orient", left_motor_speed, right_motor_speed);
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
            e.controller->raiseDrivelineSignal("Follow::orient", 0, 0);
            std::this_thread::sleep_for(std::chrono::milliseconds(150));

            logger_fsm.info(
                "absoluteTargetHeading [{}] imuHeading [{}] _turn_counter_clockwise [{}] left [{}] right [{}]",
                _absoluteTargetHeading,
                imuHeading,
                _turn_counter_clockwise,
                left_motor_speed,
                right_motor_speed
            );

        }else
        {
            transit<FollowStage_AcquiringTarget>();
        }
    };
};

struct FollowStage_AcquiringTarget : FollowStage
{
    std::chrono::system_clock::time_point _entry_time;
    std::chrono::system_clock::duration _ms_max_time_acquiring = std::chrono::milliseconds(10000);

    void entry() override
    {
        logger_fsm.info("FollowStage_AcquiringTarget | entry");
        _entry_time = std::chrono::system_clock::now();
    };

    virtual void react(ModeIdle const &e) override
    { 
        logger_fsm.info("FollowStage_AcquiringTarget | Mode changed to idle, transiting.");
        transit<FollowStage_Idle>();
    };

    //should not have this, because target lost events are fired frequently
    // virtual void react(TargetLost const &e) override
    // { 
    //     logger_fsm.info("FollowStage_AcquiringTarget | target lost, transiting.");
    //     transit<FollowStage_Idle>();
    // };

    virtual void react(TargetAcquired const &e) override
    { 
        logger_fsm.info("FollowStage_AcquiringTarget | target acquired, transiting.");
        transit<FollowStage_Steering>();
    };

    virtual void react(ClockTick const &e) override
    {
        //if elapsed time from entering this state
        //to max allowable limit for acquiring target has
        //expired, then
        //
        if( (std::chrono::system_clock::now() - _entry_time) > _ms_max_time_acquiring  )
        {
            logger_fsm.info("FollowStage_AcquiringTarget | timeout expired acquiring, transiting.");
            transit<FollowStage_Idle>();
        }
    };
};
