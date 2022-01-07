#include "camfeed.hpp"
#include <iostream>
#include <string>
#include <iomanip>
#include <algorithm>
#include <cctype>
#include <yaml-cpp/yaml.h>
#include "shared/utils/sharedstrings.hpp"
#include "shared/system/sysevents.hpp"
#include "videoframe.pb.h"

using namespace std;

CamFeed::CamFeed()
:BadBotLogger("CamFeed")
{
}


int CamFeed::main(int argc, char **argv)
{

    SysEvents::getInstance()->connectToSignalShutdown(boost::bind(&CamFeed::onSysShutdown, this));

    if(!init(argc,argv))
    {
        return -2;
    }
    
    loop();
}

bool CamFeed::init(int argc, char **argv)
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

    _log->info("Initializing messaging.");
    _messaging.init();
    _messaging.connectToSignalMessage(
        boost::bind(&CamFeed::on_rpc_msg, this, _1)
    );

    _keep_running = true;
    

    return true;
}

void CamFeed::onSysShutdown()
{
    _log->info("Shut down started.");

    // _log->info("Stopping media conversion pipeline.");
    // _media_conversion.stop();

    _log->info("Stopping app src pipeline.");
    _appSrc.stop();

    _log->info("Stopping app sink pipeline.");
    _appSink.stop();

    _keep_running = false;
    

    _log->info("Shut down completed.");
    
}

void CamFeed::pushFrameOverWs(cv::Mat &frame)
{
    // BadMessage msg;
    // msg.set_msgtype(MessageType::VIDEO_FRAME);
    // VideoFrame* frameToTx = new VideoFrame();
    // msg.set_allocated_videoframe(frameToTx);

    // frameToTx->set_width(frame.cols);
    // frameToTx->set_height(frame.rows);
    // frameToTx->set_channels(frame.channels());
    // frameToTx->set_frame(frame.data, frame.total() * frame.elemSize());

    // _ws->txMsg(msg);
}