#pragma once

#include <mtlog/badbotlogger.hpp>
#include <thread>
#include <atomic>
#include <memory>
#include "shared/gst/appsink.hpp"
#include "consts.pb.h"
#include "message.pb.h"
#include "shared/messaging/messaging_server.hpp"

using namespace badbot::messages;
using namespace std;

class CamFeed : BadBotLogger
{
public:
    CamFeed();
    int main(int argc, char** argv);
    void on_rpc_msg(const BadMessage *msg);


protected:
    bool _keep_running = false;

    MessagingServer _messaging;
    AppSink _appSink;

protected:
    void onSysShutdown();
    bool validateOptions(int argc, char **argv);
    bool init(int argc, char **argv);
    void loop();
};