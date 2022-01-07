#pragma once

#include <spdlog/spdlog.h>
#include <mutex>

// base class to be extended by those which need to access
// console logger in a multi threaded base
// exposes _log and _err as protected members for loggin to console wiht colors

using namespace std;
class BadBotLogger
{
    public:
        BadBotLogger(std::string loggerName, bool appendSerial=false);

        /**
         * Must be called on program startup to create sinks (screen and file)
         */
        static void initLogging(std::string sectionQualifier, std::string logFileName);

    protected:
        std::shared_ptr<spdlog::logger> _log;
        static std::vector<spdlog::sink_ptr> sinks;
    
    private:
        static long _serial;
        static std::mutex _mutex_serial;
        static spdlog::level::level_enum _log_level;
        static string _log_pattern;

    private:
        static long getNextSerial();
    
    // protected:
    //     inline bool getFrequentDataLogIntervalElapsed();
};