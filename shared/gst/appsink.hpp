#pragma once
#include <gstreamermm.h>
#include <opencv2/core.hpp>
#include <mtlog/badbotlogger.hpp>

#include "apppipeline.hpp"

class AppSink : public AppPipeline
{
    public:
        AppSink();
    public:
        bool init();
        bool pullFrame(cv::Mat &mat);

    private:
        Glib::RefPtr<Gst::AppSink> _appSink;
        int _width;
        int _height;
};