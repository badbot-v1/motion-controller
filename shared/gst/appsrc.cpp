#include "appsrc.hpp"
#include <yaml-cpp/yaml.h>
#include <sharedstorage/sharedstrings.hpp>

AppSrc::AppSrc()
:AppPipeline("AppSrc")
{

}

bool AppSrc::init()
{
    bool bRet = false;

    try{

        YAML::Node config = YAML::LoadFile(SharedStrings::get()->getVal("config-file"));
        
        std::string pipeline = config["appsrc"]["pipeline"].as<std::string>();
        _width = config["appsrc"]["width"].as<int>();
        _height = config["appsrc"]["height"].as<int>();
        _enabled = config["appsrc"]["enable"].as<bool>();

        _log->info("Pipeline [{}]",pipeline);
        _log->info("Image HxW [{}x{}]",_height,_width);
        if(_enabled)
        {
            _log->info("Enabled [{}]",_enabled);
        }else{
            _log->warn("Enabled [{}]",_enabled);
        }
       
        bRet = AppPipeline::init(pipeline);
        if(bRet){

            _appSrc = _appSrc.cast_dynamic(_pipeline->get_element("appSrc"));
            bRet = true;
        }
    }catch(std::exception &e){
        _log->error(e.what());
    }

    return bRet;
}


void AppSrc::pushFrame(cv::Mat &frame)
{
    if(!_enabled || !_keep_running)
    {
        return;
    }


    try{

        int bufferSize = frame.rows * frame.cols * frame.channels();
        Glib::RefPtr<Gst::Buffer> buffer = Gst::Buffer::create(bufferSize);

        Gst::MapInfo mapInfo;
        buffer->map(mapInfo, Gst::MapFlags::MAP_WRITE);
        memcpy(mapInfo.get_data(), frame.data, bufferSize);
        buffer->unmap(mapInfo);

        auto clock = _appSrc->get_clock();
        auto base_time = _appSrc->get_base_time();
        auto abs_time = clock->get_time();
        buffer->set_pts(abs_time - base_time);
        buffer->set_dts(abs_time - base_time);

        auto result = _appSrc->push_buffer(buffer);
        if(result != Gst::FlowReturn::FLOW_OK){
            _log->warn("Unable to push buffer");
        }
        
    }catch(std::exception &e){
        _log->error(e.what());
    }
}
