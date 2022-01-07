#include "vpm.hpp"
#include <iostream>
#include <string>
#include <iomanip>
#include <algorithm>
#include <cctype>
#include <yaml-cpp/yaml.h>
#include "shared/utils/sharedstrings.hpp"
#include "shared/system/sysevents.hpp"
#include "shared/messaging/cppsrc/obj_det_coords.pb.h"

using namespace std;

void VisualPerceptionModule::loop()
{
    while (_keep_running)
    {
        if(
            false == _object_detection_enabled
        )
        {
            std::this_thread::sleep_for(std::chrono::seconds(1));
            continue;
        }
        
        if(
            false == _cnn_currently_processing_frame
        ){
            if(_appSink.pullFrame(_cnn_input_image))
            {
                _cnn_currently_processing_frame = true;
                _cnn_image_ready_for_processing = true;
            }
        }else{
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    }
}


/**
 * Thread procedure for processing frames through cnn
 */
void VisualPerceptionModule::processCnn()
{
    _log->info("Entered processCNN.");

    do
    {
        //we do nothing if the current mode is not follow me
        if(false == _object_detection_enabled)
        {
            std::this_thread::sleep_for(std::chrono::seconds(1));
            continue;
        }

        while
        (
            _keep_running
            &&
            false == _cnn_image_ready_for_processing
        )
        {
            //wait until frame ready
            //this gives us around 10 detections/s which are enough given the
            //size of badbot

            //if this would be a bigger ugv, with a more powerful hardward
            //and we wanted to achive higher driving speeds such as in the case of
            //convoy, we have to reconsider this (and other related delays) to lower values
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }

        BadMessage msg;
        msg.set_msgtype(badbot::messages::MessageType::VPM_OBJ_DET_COORDS);
        ObjectDetectionCoords *coords = new ObjectDetectionCoords();
        msg.set_allocated_objcoords(coords);

        float conf_or_err = 0.0f;
        int angle_roi_mid = _cnn.processCamFrame(_cnn_input_image, coords, conf_or_err);
        

        //perform kalman filtering
        if(angle_roi_mid == VALUE_NO_DETECTION)
        {
            conf_or_err = 100.0f;
            angle_roi_mid = 0.0f;
        }
        else{
            //25% is good for us
            conf_or_err /= 25.0f;
            if(conf_or_err > 1.0f){
                conf_or_err = 1.0f;
            }
            conf_or_err *= 100.0f;


            conf_or_err = 100.0f - conf_or_err;

            if(angle_roi_mid < 0.0)
            {
                _result_multiplier = -1.0f;
            }else{
                _result_multiplier = 1.0f;
            }
        }

        //scale error between 0.0 and 4.0

        //does not yield very good results.. effectively removes kalman from picture
        // conf_or_err = ( (100.0f - conf_or_err) / 100.0f);
        // if (conf_or_err > 0.5f)
        // {
        //     conf_or_err = 0.02f;
        // }else{
        //     conf_or_err = 0.0f;
        // }
        
        // if(angle_roi_mid < 0.0f)
        // {
        //     angle_roi_mid = _kalman.getEstimate(err_percent, fabs(angle_roi_mid)) * -1.0f;
        // }else{
        //     angle_roi_mid = _kalman.getEstimate(err_percent, angle_roi_mid);
        // }

        _kalman.setMeasurements(conf_or_err, fabs(angle_roi_mid));

        coords->set_object_at_angle(_kalman_reported_estimate * _result_multiplier);

        //valid detection
        _messaging.txMsg(&msg);
        
        //flag we are ready for next frame
        _cnn_image_ready_for_processing = false;
        _cnn_currently_processing_frame = false;

    }while(_keep_running);

    _log->info("Exiting processCNN.");
}
