#pragma once

/**
 * Visual perception module
 * */

#include <mtlog/badbotlogger.hpp>
#include <thread>
#include <atomic>
#include <memory>
#include "darkcnn.hpp"
#include "shared/gst/appsink.hpp"
#include "shared/gst/appsrc.hpp"
#include "shared/gst/mediaconversion.hpp"
#include "consts.pb.h"
#include "message.pb.h"
#include "shared/messaging/messaging_server.hpp"
#include "shared/filters/kalman1.hpp"

using namespace badbot::messages;
using namespace std;

class VisualPerceptionModule : BadBotLogger
{
public:
    VisualPerceptionModule();
    int main(int argc, char** argv);
    void on_rpc_msg(const BadMessage *msg);


protected:
    bool _keep_running = false;
    bool _object_detection_enabled = false;

    /**
     * 
     * Set to true when cnn starts processing to block any new input
     * 
    */
    std::atomic<bool> _cnn_currently_processing_frame;

    /**
     * set to true after clone _cnn_input_image with input image
     * _thread_cnn_processor wakes up after finding value of true
     *
    */
    std::atomic<bool> _cnn_image_ready_for_processing;

    /**
     * Result of kalman filter which we report to c2
     */
    std::atomic<float> _kalman_reported_estimate;

    /**
     * 
     * used by _thread_cnn_processor to call cnn
     * 
     */
    Mat _cnn_input_image;

    /**
     * Used to smooth out detections
     */
    Kalman1 _kalman;

    MessagingServer _messaging;
    AppSink _appSink;
    DarkCnn _cnn;

    std::thread _thread_cnn_processor;

    /// set when there is target acquisition based on whether if target is left or right of centerline
    //  used across loops even when there is no target to correctly communicate
    //  kalman estimates
    float _result_multiplier = 1.0f;

protected:
    void telemetry_proc();
    void processCnn();
    void onSysShutdown();
    bool validateOptions(int argc, char **argv);
    bool init(int argc, char **argv);
    void loop();
    void onKalmanEstimateAvailable(const float estimate);
};