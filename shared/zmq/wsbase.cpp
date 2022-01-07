#include "wsbase.hpp"
#include <zframe.h>
#include <chrono>
#include "shared/system/sysevents.hpp"
#include <errno.h>

WSBase::WSBase()
:BadBotLogger(_module_name)
{

}

WSBase::WSBase(std::string moduleName)
:BadBotLogger(moduleName)
{
    _module_name = moduleName;
}


WSBase::~WSBase()
{
    cleanup();
}



std::string WSBase::getListenAddress()
{
    _log->info("getListenAddress | {}", _listen_address);
    return _listen_address;
}


void WSBase::setListenAddress(std::string address)
{
    _log->info("setListenAddress | {}", address);
    _listen_address = address;
}

void WSBase::cleanup()
{
    _log->info("cleanup | entered");

    _keep_running = false;

    if(nullptr != _sock)
    {
        _log->info("cleanup | release _sock");

        zwssock_destroy(&_sock);
        _sock = nullptr;
    }
 
    _log->info("cleanup | exiting");
}


bool WSBase::init()
{
    bool bRet = false;
    _log->info("init | entered");

    zsys_handler_set(NULL);
    SysEvents::getInstance()->connectToSignalShutdown(boost::bind(&WSBase::cleanup, this));

    _keep_running = true;
    _thread_rx = std::thread(&WSBase::rx_proc,this);
    bRet = true;


    _log->info("init | exiting [{}]", bRet);
    return bRet;
}

void WSBase::txMsg(BadMessage &msg)
{
    if(!_keep_running || _listener_routing_id.size() == 0)
    {
        return;
    }

    vector<char> buffer(msg.ByteSize());

    if(!msg.SerializeToArray(buffer.data(), buffer.size()))
    {
        _log->error("Unable to serialize message for tx.");

    }else{
        zmsg_t *msgTx = zmsg_new();

        // zframe_t* msgTxFrameId = nullptr;
        // if(msg.frame_id().size() > 0)
        // {
        //     msgTxFrameId = zframe_from(msg.frame_id().c_str());
        //     zmsg_push(msgTx, msgTxFrameId);
        // }
        zmsg_pushmem(msgTx, _listener_routing_id.data(), _listener_routing_id.size());
        zmsg_addmem(msgTx, buffer.data(), buffer.size());

        //_log->info("Transmitting [{}] frames.", zmsg_size(msgTx));

        int rc = zwssock_send(_sock, &msgTx);

        if(rc != 0){
            _log->error("Unable to tx msg.");
        }

        // if(nullptr != msgTxFrameId)
        // {
        //     zframe_destroy(&msgTxFrameId);
        // }

        zmsg_destroy(&msgTx);
    }

}


void WSBase::rx_proc()
{
    _log->info("rx_proc | entered.");

    do{
        _log->info("rx_proc | create sock.");
        _sock = zwssock_new_router();

        _log->info("rx_proc | bind sock.");
        zwssock_bind(_sock, (char*)_listen_address.c_str());

        zmsg_t* wire_msg = nullptr;
        zframe_t *id = nullptr;

        while(_keep_running)
        {
            
            //wire_msg = zwssock_recv_with_timeout(_sock, 5000);
            wire_msg = zwssock_recv(_sock);
            // if(wire_msg == 0){
            //     continue;
            // }else if(wire_msg < 0){
            //     _log->error("Poll error.");
            //     std::this_thread::sleep_for(std::chrono::seconds(5));
            //     continue;
            // }

            if (!wire_msg)
                break;

            // first message is the routing id
            id = zmsg_pop(wire_msg);

            int remaining_frames_count = zmsg_size(wire_msg);
            while (remaining_frames_count != 0)
            {
                zframe_t *data_frame = zmsg_pop(wire_msg);
                size_t data_frame_content_length = zframe_size(data_frame);

                //decode protobuf and raise signal
                BadMessage msgToSignal;
                msgToSignal.ParseFromArray(zframe_data(data_frame), data_frame_content_length);

                if(msgToSignal.msgtype() == MessageType::HEARTBEAT_RC)
                {
                    int id_len = zframe_size(id);
                    _listener_routing_id.clear();
                    _listener_routing_id.resize(id_len);
                    memcpy(_listener_routing_id.data(), zframe_data(id), id_len);
                    
                    //respond
                    zmsg_t *msg_ack = zmsg_new();
                    zmsg_prepend(msg_ack, &id);
                    zmsg_append(msg_ack, &data_frame);

                    //zmsg_addstr(msg_ack, "ack");

                    int rc = zwssock_send(_sock, &msg_ack);
                    if(rc != 0){
                        _log->warn("Unable to ack heartbeat");
                    } 
                    zmsg_destroy(&msg_ack);
                }else{
                    msgToSignal.set_frame_id(std::string((char*)zframe_data(id),zframe_size(id)));
                    raiseSignalMessage(msgToSignal); 
                }

//                zframe_destroy(&data_frame);
                //data_frame = nullptr;

                remaining_frames_count = zmsg_size(wire_msg);               
            }

  //          zframe_destroy(&id);
            //id = nullptr;

            zmsg_destroy(&wire_msg);
        }

        //in case clean up set it to nullptr
        if(nullptr != _sock)
        {
            zwssock_destroy(&_sock);
            _sock = nullptr;
        }

        
        if(_keep_running)
        {
            //todo read sleep value from config file
            _log->info("rx_proc | sock closed, sleeping for 5s.");
            std::this_thread::sleep_for(std::chrono::seconds(5));
        }

    }while(_keep_running);

    _log->info("rx_proc | exiting.");
}

void WSBase::connectToSignalMessage(const signal_message_slot_type &slot)
{
    _signal_message.connect(slot);
}

void WSBase::raiseSignalMessage(BadMessage &msg)
{
    _log->info("Raising signal for message type: {}", MessageType_Name(msg.msgtype()));
    _signal_message(msg);
}