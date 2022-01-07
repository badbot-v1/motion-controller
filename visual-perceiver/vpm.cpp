#include "vpm.hpp"
#include <iostream>
#include <iostream>
#include <string>
#include <iomanip>
#include <algorithm>
#include <cctype>
#include <yaml-cpp/yaml.h>
#include "shared/utils/sharedstrings.hpp"
#include "shared/system/sysevents.hpp"

using namespace std;

VisualPerceptionModule::VisualPerceptionModule()
:BadBotLogger("VPM"),
_messaging("InternalMessaging"),
_kalman(0.5f, 5.0f)
{
    _cnn_currently_processing_frame = false;
    _cnn_image_ready_for_processing = false;
    _kalman.connectToSignalEstimate(
        boost::bind(&VisualPerceptionModule::onKalmanEstimateAvailable, this, _1)
    );
}


int VisualPerceptionModule::main(int argc, char **argv)
{

    SysEvents::getInstance()->connectToSignalShutdown(boost::bind(&VisualPerceptionModule::onSysShutdown, this));

    if(!init(argc,argv))
    {
        return -2;
    }
    
    loop();
}

bool VisualPerceptionModule::init(int argc, char **argv)
{
    try
    {

        YAML::Node config = YAML::LoadFile(SharedStrings::get()->getVal("config-file"));

        _log->info("Initializing App Sink");
        if(!_appSink.init())
        {
            _log->error("Unable to init _appSink pipeline.");
            return false;
        }
        
        if(!_appSink.start())
        {
            _log->error("Unable to start _appSink pipeline.");
            return false;
        }

        _log->info("Initializing CNN");
        if(!_cnn.init())
        {
            return false;
        }

        _log->info("Initializing messaging.");
        _messaging.init("internal_messaging");
        _messaging.connectToSignalMessage(
            boost::bind(&VisualPerceptionModule::on_rpc_msg, this, _1)
        );

        _keep_running = true;

        //start the image processing thread
        _log->info("Starting cnn processor thread");
        _thread_cnn_processor = std::thread(&VisualPerceptionModule::processCnn, this);

    }catch(...)
    {
        _log->error("An error occurred while initializing.");
        return false; 
    }

    return true;
}

void VisualPerceptionModule::onSysShutdown()
{
    _log->info("Shut down started.");

    _log->info("Stopping app sink pipeline.");
    _appSink.stop();

    _keep_running = false;

    _log->info("Shut down completed.");
    
}


void VisualPerceptionModule::onKalmanEstimateAvailable(const float estimate)
{
    _kalman_reported_estimate = estimate;
}