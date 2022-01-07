#pragma once

#include <libgpsmm.h>
#include <memory>
#include <thread>
#include <boost/signals2.hpp>

#include "shared/log/badbotlogger.hpp"
#include "sensorbase.hpp"
#include "gpsdata.pb.h"

class GpsSensor : public SensorBase
{
    public:
        typedef boost::signals2::signal<void (badbot::messages::GpsData*)> signalGps;
        typedef signalGps::slot_type slot_gps;

    protected:
        std::unique_ptr<gpsmm> _gps;
        //signal
        signalGps _signalGps;
        //cached
        badbot::messages::GpsData _gpsData;

    public:
        GpsSensor();
        virtual ~GpsSensor();
        bool init();
        void connecToSignalGps(const slot_gps &slot);
    
    protected:
        virtual void thread_proc() override;
        virtual void cleanup() override;
    
};