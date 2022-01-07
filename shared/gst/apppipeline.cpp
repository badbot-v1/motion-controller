#include "apppipeline.hpp"
#include "shared/system/sysevents.hpp"


AppPipeline::AppPipeline(std::string childName)
:BadBotLogger(childName)
{
    SysEvents::getInstance()->connectToSignalShutdown(boost::bind(&AppPipeline::onSysShutdown, this));
}

bool AppPipeline::init(std::string pipeline)
{
    bool bRet = false;

    try{


        Glib::RefPtr<Gst::Element> parsedPipeline = Gst::Parse::launch(pipeline);
        _pipeline = _pipeline.cast_dynamic(parsedPipeline);

        bRet = true;
    }catch(...){
        std::exception_ptr p = std::current_exception();
        _log->error((p ? p.__cxa_exception_type()->name() : "null"));
    }

    return bRet;
}


bool AppPipeline::start()
{
    bool bRet = false;

    try{

        _pipeline->set_state(Gst::State::STATE_PLAYING);

        bRet = true;
    }catch(std::exception &e){
        _log->error(e.what());
    }

    return bRet;
}

bool AppPipeline::pause()
{
    bool bRet = false;

    try{

        _pipeline->set_state(Gst::State::STATE_PAUSED);

        bRet = true;
    }catch(std::exception &e){
        _log->error(e.what());
    }

    return bRet;
}

bool AppPipeline::stop()
{
    bool bRet = false;

    try{
        
        _pipeline->set_state(Gst::State::STATE_NULL);

        bRet = true;
    }catch(std::exception &e){
        _log->error(e.what());
    }

    return bRet;
}

void AppPipeline::toggleEnabled(bool enable)
{
    _enabled = enable;
    if(!_enabled){
        pause();
    }else{
        start();
    }
}


void AppPipeline::onSysShutdown()
{
    _log->info("Shut down started.");
    _keep_running = false;
    
    stop();

    _log->info("Shut down completed.");
    
}