#include "badbotlogger.hpp"
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <yaml-cpp/yaml.h>
#include <sharedstorage/sharedstrings.hpp>
#include <iostream>

using namespace spdlog;

long BadBotLogger::_serial = 0;
spdlog::level::level_enum BadBotLogger::_log_level = spdlog::level::level_enum::err;
string BadBotLogger::_log_pattern = "%H:%M:%S.%e|%20!n|%^%L%$|%5t| %v";
std::mutex BadBotLogger::_mutex_serial;
std::vector<spdlog::sink_ptr> BadBotLogger::sinks;

void BadBotLogger::initLogging(std::string sectionQualifier, std::string logFileName)
{
    YAML::Node config = YAML::LoadFile(SharedStrings::get()->getVal("config-file"));
    
    _log_level = spdlog::level::from_str(config[sectionQualifier]["log_level"].as<string>());
    

    bool console_logger_enabled = config[sectionQualifier]["console_logger_enabled"].as<bool>();

    sinks.push_back(std::make_shared<spdlog::sinks::basic_file_sink_mt>(logFileName, false));
    if(console_logger_enabled)
    {
        sinks.push_back(std::make_shared<spdlog::sinks::stdout_color_sink_mt>());
    }
}

BadBotLogger::BadBotLogger(std::string loggerName, bool appendSerial)
{
    if(appendSerial)
    {
        long next_serial = BadBotLogger::getNextSerial();
        loggerName.append(std::to_string(next_serial));
    }

    //_log = spdlog::stdout_color_mt(loggerName);
    _log = std::make_shared<spdlog::logger>(loggerName, begin(sinks), end(sinks));
    _log->set_level(_log_level);
    _log->set_pattern(_log_pattern);
}


long BadBotLogger::getNextSerial()
{
    std::lock_guard<std::mutex> guard(_mutex_serial);
    ++_serial;

    return _serial;
}

// void BadBotLogger::setLogLevel(int configuredLevel)
// {
//     switch(configuredLevel)
//     {
//         case 0:
//             _log_level = spdlog::level::level_enum::SPDLOG_LEVEL_OFF;
//         break;
        
//         case 1:
//             _log_level = spdlog::level::level_enum::SPDLOG_LEVEL_CRITICAL;
//         break;

//         case 2:
//             _log_level = spdlog::level::level_enum::SPDLOG_LEVEL_ERROR;
//         break;

//         case 3:
//             _log_level = spdlog::level::level_enum::SPDLOG_LEVEL_WARN;
//         break;

//         case 4:
//             _log_level = spdlog::level::level_enum::SPDLOG_LEVEL_INFO;
//         break;

//         case 5:
//             _log_level = spdlog::level::level_enum::SPDLOG_LEVEL_DEBUG;
//         break;

//         case 6:
//             _log_level = spdlog::level::level_enum::SPDLOG_LEVEL_TRACE;
//         break;

//     }

// }