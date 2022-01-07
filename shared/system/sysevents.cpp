#include "sysevents.hpp"

SysEvents* SysEvents::_instance = nullptr;

SysEvents::SysEvents()
:BadBotLogger("SysEvents")
{

}

SysEvents* SysEvents::getInstance()
{
    if(nullptr == _instance){
        _instance = new SysEvents();
    }

    return _instance;
}

void SysEvents::connectToSignalShutdown(const signal_sys_shutdown_slot_type& slot)
{
    _signal_sys_shutdown.connect(slot);
}

void SysEvents::raiseSignalSysShutdown()
{
    _log->info("Signal shutdown initiated.");
    _signal_sys_shutdown();
    //todo read wait value from config
    _log->info("Signal shutdown finished. Waiting 2 seconds for threads to finish.");
    std::this_thread::sleep_for(std::chrono::seconds(2));
}