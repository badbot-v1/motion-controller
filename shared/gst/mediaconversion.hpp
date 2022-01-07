#pragma once

#include "apppipeline.hpp"

#include <gstreamermm.h>
#include <opencv2/core.hpp>
#include <mtlog/badbotlogger.hpp>

class MediaConversion : public AppPipeline
{
    public:
        MediaConversion();
    public:
        bool init();
        void pushFrame(cv::Mat &frame);
        cv::Mat pullFrame();
        bool pullFrame(uint64 timeout, std::unique_ptr<cv::Mat> &OUTframe);

    private:
        Glib::RefPtr<Gst::AppSink> _appSink;
        Glib::RefPtr<Gst::AppSrc> _appSrc;
        int _width;
        int _height;
};