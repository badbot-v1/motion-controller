#pragma once

#include "shared/log/badbotlogger.hpp"
#include <boost/signals2/signal.hpp>

#include "zmq.hpp"

#include "shared/messaging/cppsrc/message.pb.h"

using namespace badbot::messages;



class MessagingServer : BadBotLogger
{
    public:
        typedef boost::signals2::signal<void(const BadMessage *msg)> signal_message;
        typedef signal_message::slot_type signal_message_slot_type;

    public:
        MessagingServer(std::string logName);
        void init(std::string configSectionQualifier);
        void connectToSignalMessage(const signal_message_slot_type &slot);
        void txMsg(badbot::messages::BadMessage *msg);

    protected:
        void onSysShutdown();
        void serverThread();
        void raiseSignalMessage(const BadMessage *msg);

    protected:
        std::thread _thread_server;
        bool _keep_running = true;
        bool _telemetry_enabled = false;
        signal_message _signal_message;

        zmq::socket_t sockRx;
        zmq::socket_t sockTx;
        
};