#include <yaml-cpp/yaml.h>

#include "gps.hpp"
#include "shared/system/sysevents.hpp"
#include "shared/utils/sharedstrings.hpp"

#define CONFIG_SECTION_NAME "sensors_gps"

GpsSensor::GpsSensor()
:SensorBase("GpsSensor")
{
    
}

GpsSensor::~GpsSensor()
{

}

void GpsSensor::thread_proc()
{
    
    while(_keep_running)
    {
        _log->info("GPS update process entering.");

        if (_gps->stream(WATCH_ENABLE | WATCH_JSON) == nullptr) 
        {
            _log->error("No GPSD running.");
            std::this_thread::sleep_for(std::chrono::seconds(10));
            continue;   
        }

        auto const waiting_time{1000000};  // 1000000 is 1 second

        while(_keep_running)
        {
            if (!_gps->waiting(waiting_time)) {

                if(!_keep_running)
                {
                    break;
                }

                continue;
            }

            struct gps_data_t* gpsd_data{nullptr};

            if ((_gps->read()) == nullptr) {
                _log->error("GPSD read error.");
                break;
            }

            while (((gpsd_data = _gps->read()) == nullptr) || (gpsd_data->fix.mode < MODE_2D)) {
                // Do nothing until fix, block execution for 1 second (busy wait mitigation)
                if(!_keep_running)
                {
                    break;
                }
                //emit signal for last known position
                badbot::messages::GpsData *gpsData = new badbot::messages::GpsData(_gpsData);

                _signalGps(gpsData);

                //wait until fix
                std::this_thread::sleep_for(std::chrono::seconds(1));
            }

            //report heatlh
            updateLastRxTime();

            _gpsData.set_latitude(gpsd_data->fix.latitude);
            _gpsData.set_longitude(gpsd_data->fix.longitude);
            _gpsData.set_hdop(gpsd_data->dop.hdop);
            _gpsData.set_vdop(gpsd_data->dop.vdop);
            _gpsData.set_pdop(gpsd_data->dop.pdop);
            _gpsData.set_satellites_visible(gpsd_data->satellites_visible);
            _gpsData.set_satellites_used(gpsd_data->satellites_used);
            
            badbot::messages::GpsData *gpsData = new badbot::messages::GpsData(_gpsData);

            _signalGps(gpsData);
            
        }

        _log->info("GPS update process exiting.");
    }
    
}

void GpsSensor::cleanup()
{
    _log->info("Cleanup started.");

    
    _log->info("Cleanup completed.");
}

bool GpsSensor::init()
{
    _log->info("Initialization started.");

    YAML::Node config = YAML::LoadFile(SharedStrings::get()->getVal("config-file"));
    _gps.reset(new gpsmm("localhost", DEFAULT_GPSD_PORT));

    //important, must not be called before we create _gps to prevent seg faults
    SensorBase::init(CONFIG_SECTION_NAME);

    _log->info("Initialization finished.");
    return true;

}

void GpsSensor::connecToSignalGps(const slot_gps &slot)
{
    _signalGps.connect(slot);
}