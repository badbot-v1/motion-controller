#include "controllerbase.hpp"
#include <chrono>
#include <yaml-cpp/yaml.h>

ControllerBase::ControllerBase(std::string name) 
: BadBotLogger(name)
{

}

bool ControllerBase::init(std::string ymlNodeName)
{
    bool bRet = false;
    try{

        YAML::Node config = YAML::LoadFile(SharedStrings::get()->getVal("config-file"));

        _CMD_CALCULATION_FREQUENCY = config[ymlNodeName]["msCalculationFrequency"].as<int>();
        _MAX_NO_UPDATE_DURATION = config[ymlNodeName]["msNoUpdateDuration"].as<int>();

        _log->info("_CMD_CALCULATION_FREQUENCY [{}]",_CMD_CALCULATION_FREQUENCY);
        _log->info("_MAX_NO_UPDATE_DURATION [{}]",_MAX_NO_UPDATE_DURATION);

        _thread_cmd_generator = std::thread(&ControllerBase::calculateNextFrame,this);

        bRet = true;

    }catch(...){
        std::exception_ptr p = std::current_exception();
        _log->error((p ? p.__cxa_exception_type()->name() : "null"));
    }


    return bRet;
}

bool ControllerBase::cleanup()
{
    _keep_running = false;
    _thread_cmd_generator.join();

    return true;
}

void ControllerBase::connectToSignalDrivelineCmd(const slot_signalDrivelineCmd &slot)
{
    _signalDrivelineCmd.connect(slot);
}

void ControllerBase::setActive(bool state)
{
    _active_controller = state;
}


void ControllerBase::raiseDrivelineSignal(std::string source, unsigned char vLeft, unsigned char vRight)
{
    _signalDrivelineCmd("ControllerBase", vLeft, vRight);
}

/**
 * Following funcs are used for teleop and alike data validation checks
 */
void ControllerBase::updateLastInputRxTime()
{
    _last_updated_inputs_at = std::chrono::system_clock::now();
}


bool ControllerBase::isInputStillValid()
{
    auto now = std::chrono::system_clock::now();
    auto diff = std::chrono::duration_cast<std::chrono::milliseconds>(now - _last_updated_inputs_at);   

    if(diff.count() < _MAX_NO_UPDATE_DURATION) //todo revise
    {
        return true;
    }

    return false;
}