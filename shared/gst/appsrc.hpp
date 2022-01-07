#pragma once

#include "apppipeline.hpp"

#include <gstreamermm.h>
#include <opencv2/core.hpp>
#include <mtlog/badbotlogger.hpp>

class AppSrc : public AppPipeline
{
    public:
        AppSrc();
    public:
        bool init();
        void pushFrame(cv::Mat &frame);

    private:
        Glib::RefPtr<Gst::AppSrc> _appSrc;
        int _width;
        int _height;
};