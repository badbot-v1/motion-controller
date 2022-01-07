#include "messaging_server.hpp"
#include "shared/system/sysevents.hpp"
#include <yaml-cpp/yaml.h>
#include <sharedstorage/sharedstrings.hpp>
#include <exception>

//todo: move to a global space
zmq::context_t zmqCtx;

MessagingServer::MessagingServer(std::string logName)
:BadBotLogger(logName)
{
    
}

void MessagingServer::init(std::string configSectionQualifier)
{
    _log->info("Init started with config qualifier [{}]", configSectionQualifier);

    YAML::Node config = YAML::LoadFile(SharedStrings::get()->getVal("config-file"));

    std::string subscriptionAddress = config[configSectionQualifier]["subscriptionAddress"].as<std::string>();
    std::string publishingAddress = config[configSectionQualifier]["publishingAddress"].as<std::string>();
    bool subscriberBinds = config[configSectionQualifier]["subscriberBinds"].as<bool>();

    _log->info("Will subscribe at: [{}]", subscriptionAddress);
    _log->info("Subscriber binds?: [{}]", subscriberBinds);
    _log->info("Will publish at: [{}]", publishingAddress);

    sockRx = zmq::socket_t(::zmqCtx, zmq::socket_type::sub);
    sockTx = zmq::socket_t(::zmqCtx, zmq::socket_type::pub);

    if(subscriberBinds)
    {
        sockRx.bind(subscriptionAddress);
    }else{
        sockRx.connect(subscriptionAddress);
    }
    sockTx.bind(publishingAddress);

    sockRx.setsockopt(ZMQ_SUBSCRIBE, "", 0);

    int lingerVal = 0;
    sockTx.setsockopt(ZMQ_LINGER, lingerVal);
        
    _log->info("Starting server thread.");
    _thread_server = std::thread(&MessagingServer::serverThread, this);
    

    SysEvents::getInstance()->connectToSignalShutdown(
        boost::bind(&MessagingServer::onSysShutdown, this)
    );
    _log->info("Init finished.");
}

void MessagingServer::onSysShutdown()
{
    _log->info("shutdown started.");

    _keep_running = false;
    _thread_server.join();

    _log->info("shutdown finished.");
}

void MessagingServer::serverThread()
{
    _log->info("Server thread started.");

    constexpr auto rxFlags = zmq::recv_flags::none | zmq::recv_flags::dontwait;

    while(_keep_running)
    {
        try
        {
            zmq::recv_result_t result;
            zmq::message_t received_message;

            result = sockRx.recv(received_message, rxFlags);
            if(result.has_value() == false)
            {
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
                continue;
            }
            BadMessage msg;
            msg.ParseFromArray(received_message.data(), received_message.size());
            raiseSignalMessage(&msg);

        }catch(std::exception& e)
        {
            _log->error(e.what());
        }

        // if(result.value() == EAGAIN)
        // {
        //     std::this_thread::sleep_for(std::chrono::milliseconds(10));
        // }else{
        //     BadMessage msg;
        //     msg.ParseFromArray(received_message.data(), received_message.size());
        //     raiseSignalMessage(&msg);
        // }
    }


    _log->info("Server thread exited.");
}

void MessagingServer::connectToSignalMessage(const signal_message_slot_type &slot)
{
    _signal_message.connect(slot);
}

void MessagingServer::raiseSignalMessage(const BadMessage *msg)
{
    //some pre-filtering for video
    if(
        msg->msgtype() == MessageType::CMD_TOGGLE 
        &&
        msg->togglecmd().device() == Devices::TELEMETRY
    )
    {
        _telemetry_enabled = msg->togglecmd().enable();
    }

    _signal_message(msg);
}


void MessagingServer::txMsg(badbot::messages::BadMessage *msg)
{
    if(!sockTx.connected())
    {
        return;
    }
    std::string serialized = msg->SerializeAsString();
    zmq::message_t zmsg(serialized);
        
    sockTx.send(zmsg, zmq::send_flags::none);
}