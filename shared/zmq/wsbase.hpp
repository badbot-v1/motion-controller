#pragma once


#include "shared/log/badbotlogger.hpp"

#include <czmq.h>
#include <zwssock.h>
#include <string>
#include <thread>
#include <vector>
#include <boost/signals2/signal.hpp>

#include <bbmessages/message.pb.h>

using namespace std;
using namespace boost;
using namespace badbot::messages;

class WSBase : BadBotLogger {
    public:
        typedef boost::signals2::signal<void(BadMessage msg)> signal_message;
        typedef signal_message::slot_type signal_message_slot_type;

    public:
        WSBase();
        WSBase(std::string moduleName);
        virtual ~WSBase();
        void cleanup();
        bool init();

        void connectToSignalMessage(const signal_message_slot_type &slot);
        std::string getListenAddress();
        void setListenAddress(std::string address);
        void txMsg(BadMessage &msg);
    
    protected:
        void rx_proc();
        void raiseSignalMessage(BadMessage &msg);
        

    private:
        std::string _module_name = "WSBase";
        zwssock_t *_sock = nullptr;
        std::string _listen_address = "tcp://0.0.0.0:8181";
        std::thread _thread_rx;
        bool _keep_running = true;
        signal_message _signal_message;
        vector<char> _listener_routing_id;

};