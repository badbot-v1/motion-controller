#pragma once

#include "shared/log/badbotlogger.hpp"
#include <boost/signals2/signal.hpp>

using namespace std;
using namespace boost;

class SysEvents : BadBotLogger
{
    typedef boost::signals2::signal<void()> signal_sys_shutdown;
    typedef signal_sys_shutdown::slot_type signal_sys_shutdown_slot_type;

    private:
        static SysEvents *_instance;
        signal_sys_shutdown _signal_sys_shutdown;

    protected:
        SysEvents();

    public:
        static SysEvents* getInstance();
        void connectToSignalShutdown(const signal_sys_shutdown_slot_type& slot);
        void raiseSignalSysShutdown();
};