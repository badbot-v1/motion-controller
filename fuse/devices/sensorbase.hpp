#pragma once

#include <memory>
#include <thread>

#include "shared/log/badbotlogger.hpp"

class SensorBase : public BadBotLogger
{
    protected:
        bool _keep_running;

        std::chrono::system_clock::time_point _last_rx_at;
        uint32_t UNHEALTHY_THRESHOLD_MS = 100;

        std::thread _thread_proc;

    public:
        SensorBase(std::string loggerName);
        virtual ~SensorBase();
        bool isHealthy();
        
    
    protected:
        void onSysShutdown();
        virtual void cleanup();

        virtual void thread_proc();
        void updateLastRxTime();

        virtual bool init(std::string CONFIG_SECTION_NAME);

};