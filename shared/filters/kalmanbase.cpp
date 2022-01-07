#include "kalmanbase.hpp"
#include "shared/system/sysevents.hpp"

KalmanBase::KalmanBase(std::string loggerName, uint32_t ms_sleep_interval, uint32_t ms_estimate_signal_interval)
:BadBotLogger(loggerName),
_ms_sleep_interval_between_calculations(ms_sleep_interval),
_ms_estimate_signal_interval(ms_estimate_signal_interval),
_keep_running(true),
_is_active(false)
{
    _time_last_estimate_signal = std::chrono::steady_clock::now();
    _thread_computation = std::thread(&KalmanBase::computationProc,this);

    SysEvents::getInstance()->connectToSignalShutdown(boost::bind(&KalmanBase::onSysShutdown, this));
}

void KalmanBase::computationProc()
{
    bool exit_thread = false;

    while (_keep_running && !exit_thread)
    {
        if(!_is_active)
        {
            std::this_thread::sleep_for
            (
                std::chrono::seconds(1)
            );            
            continue;
        }

        exit_thread = computeEstimate();
        
        std::this_thread::sleep_for
        (
            std::chrono::milliseconds(_ms_sleep_interval_between_calculations)
        );
    } 
}

bool KalmanBase::computeEstimate()
{
    _log->warn("Missing implementation for computeEstimate. Default method called in base class.");
    
    return false;
}

void KalmanBase::onSysShutdown()
{
    _log->info("Shut down started.");

    _keep_running = false;

    _log->info("Shut down completed.");    
}


void KalmanBase::setActive(bool isActive)
{
    _is_active = isActive;
}