#pragma once
#include <gstreamermm.h>
#include <opencv2/core.hpp>

#include <mtlog/badbotlogger.hpp>

class AppPipeline : protected BadBotLogger
{
    public:
        AppPipeline(std::string childName);
    public:
        bool init(std::string pipeline);
        bool start();
        bool pause();
        bool stop();
        void toggleEnabled(bool enable);
        bool getEnabled(){return _enabled;}
    
    protected:
        void onSysShutdown();

    protected:
        Glib::RefPtr<Gst::Pipeline> _pipeline;
        bool _enabled = false;
        bool _keep_running = true;

};