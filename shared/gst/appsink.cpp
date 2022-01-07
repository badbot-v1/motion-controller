#include "appsink.hpp"
#include <yaml-cpp/yaml.h>
#include <sharedstorage/sharedstrings.hpp>



AppSink::AppSink()
:AppPipeline("AppSink")
{

}

bool AppSink::init()
{
    bool bRet = false;

    try{

        YAML::Node config = YAML::LoadFile(SharedStrings::get()->getVal("config-file"));
        
        std::string pipeline = config["appsink"]["pipeline"].as<std::string>();
        _width = config["appsink"]["width"].as<int>();
        _height = config["appsink"]["height"].as<int>();

        _log->info("Pipeline [{}]",pipeline);
        _log->info("Image HxW [{}x{}]",_height,_width);
        
        bRet = AppPipeline::init(pipeline);
        if(bRet){

            _appSink = _appSink.cast_dynamic(_pipeline->get_element("appSink"));
            bRet = true;
        }
    }catch(std::exception &e){
        _log->error(e.what());
    }

    return bRet;
}


bool AppSink::pullFrame(cv::Mat &frame)
{
    frame = cv::Mat(_height,_width, CV_8UC3);

     if(!_keep_running)
     {
         return false;
     }

    try{
        Glib::RefPtr<Gst::Buffer> buffer;
        Glib::RefPtr<Gst::Sample> sample = _appSink->try_pull_sample(0);
        if(!sample){
            return false;
        }
        buffer = sample->get_buffer();

        Gst::MapInfo mapInfo;
        buffer->map(mapInfo, Gst::MapFlags::MAP_READ);
        
        memcpy(frame.data, mapInfo.get_data(), mapInfo.get_size());
        buffer->unmap(mapInfo);
        
        return true;

    }catch(std::exception &e){
        _log->error(e.what());
    }

    return false;
}

