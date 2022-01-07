#include <yaml-cpp/yaml.h>

#include "sensorbase.hpp"
#include "shared/system/sysevents.hpp"
#include "shared/utils/sharedstrings.hpp"

SensorBase::SensorBase(std::string loggerName)
:BadBotLogger(loggerName)
{
    _last_rx_at = std::chrono::system_clock::now();
}

SensorBase::~SensorBase()
{

}

bool SensorBase::init(std::string CONFIG_SECTION_NAME)
{
    _log->info("Initialization started.");

    YAML::Node config = YAML::LoadFile(SharedStrings::get()->getVal("config-file"));

    UNHEALTHY_THRESHOLD_MS = config[CONFIG_SECTION_NAME]["unhealthy_threshold_ms"].as<uint32_t>();

    _keep_running = true;
    SysEvents::getInstance()->connectToSignalShutdown(boost::bind(&SensorBase::onSysShutdown, this));

    _thread_proc = std::thread(&SensorBase::thread_proc, this);

    _log->info("Initialization finished.");
    return true;

}

void SensorBase::thread_proc()
{
    _log->warn("Thread process exiting, not overridden in child.");
}

void SensorBase::onSysShutdown()
{
    _log->info("Shut down started.");

    _keep_running = false;
    
    //let children cleanup
    try
    {
        _log->info("Cleaning up.");
        cleanup();
    }
    catch(const std::exception& e)
    {
        _log->error(e.what());
    }
    
    _log->info("Shut down completed.");
}

void SensorBase::cleanup()
{
    
}

bool SensorBase::isHealthy()
{
    auto now = std::chrono::system_clock::now();

    auto diff = std::chrono::duration_cast< std::chrono::milliseconds >(
        (now - _last_rx_at)
    );
    
    int64_t difference_ms = diff.count();

    if(difference_ms >= UNHEALTHY_THRESHOLD_MS)
    {
        return false;
    }

    return true;

}

void SensorBase::updateLastRxTime()
{
    _last_rx_at = std::chrono::system_clock::now();
}