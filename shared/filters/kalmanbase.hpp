#pragma once

#include "shared/log/badbotlogger.hpp"
#include <thread>

class KalmanBase : public BadBotLogger
{
    protected:
        uint32_t _ms_sleep_interval_between_calculations;
        uint32_t _ms_estimate_signal_interval;
        std::thread _thread_computation;
        
        bool _keep_running;
        bool _is_active;
        
        std::chrono::steady_clock::time_point _time_last_estimate_signal;

    private:
        void computationProc();
        void onSysShutdown();

    protected:
        /**
         * Thread will exit if function returns false
         */
        virtual bool computeEstimate();
    
    public:
        KalmanBase(std::string loggerName, uint32_t ms_sleep_interval, uint32_t ms_estimate_signal_interval);       

        /**
         * Mark as active to receive callbacks and calculations to perform
         */
        void setActive(bool isActive);
};