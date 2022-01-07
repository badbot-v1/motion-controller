#include "mediaconversion.hpp"
#include <yaml-cpp/yaml.h>
#include <sharedstorage/sharedstrings.hpp>

MediaConversion::MediaConversion()
:AppPipeline("MediaConversion")
{

}

bool MediaConversion::init()
{
    bool bRet = false;

    try{

        YAML::Node config = YAML::LoadFile(SharedStrings::get()->getVal("config-file"));
        
        std::string pipeline = config["mediaconversion"]["pipeline"].as<std::string>();
        _width = config["mediaconversion"]["width"].as<int>();
        _height = config["mediaconversion"]["height"].as<int>();
        _enabled = config["mediaconversion"]["enable"].as<bool>();

        _log->info("Pipeline [{}]",pipeline);
        _log->info("Image HxW [{}x{}]",_height,_width);
        _log->info("Enabled [{}]",_enabled);
       
        bRet = AppPipeline::init(pipeline);
        if(bRet){

            _appSink = _appSink.cast_dynamic(_pipeline->get_element("appSink"));
            _appSrc = _appSrc.cast_dynamic(_pipeline->get_element("appSrc"));
            bRet = true;
        }
    }catch(std::exception &e){
        _log->error(e.what());
    }

    return bRet;
}


void MediaConversion::pushFrame(cv::Mat &frame)
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

cv::Mat MediaConversion::pullFrame()
{
    cv::Mat frame(_height,_width, CV_8UC3);

    if(!_enabled || !_keep_running)
    {
        return frame;
    }

    try{
        Glib::RefPtr<Gst::Buffer> buffer;
        Glib::RefPtr<Gst::Sample> sample = _appSink->pull_sample();
        buffer = sample->get_buffer();

        Gst::MapInfo mapInfo;
        buffer->map(mapInfo, Gst::MapFlags::MAP_READ);
        
        memcpy(frame.data, mapInfo.get_data(), mapInfo.get_size());
        buffer->unmap(mapInfo);
        
        return frame;

        
    }catch(std::exception &e){
        _log->error(e.what());
    }
}

bool MediaConversion::pullFrame(uint64 timeout, std::unique_ptr<cv::Mat> &OUTframe)
{
    OUTframe.reset(new cv::Mat(_height,_width, CV_8UC3));

    if(!_enabled || !_keep_running)
    {
        return false;
    }

    try{
        Glib::RefPtr<Gst::Buffer> buffer;
        Glib::RefPtr<Gst::Sample> sample = _appSink->try_pull_sample(timeout);
        if(!sample)
        {
            return false;
        }

        buffer = sample->get_buffer();

        Gst::MapInfo mapInfo;
        buffer->map(mapInfo, Gst::MapFlags::MAP_READ);
        
        memcpy(OUTframe->data, mapInfo.get_data(), mapInfo.get_size());
        buffer->unmap(mapInfo);
        
        return true;

        
    }catch(std::exception &e){
        _log->error(e.what());
    }
}
