#pragma once

#include <opencv2/core.hpp>
#include <mtlog/badbotlogger.hpp>

#define GPU
#define OPENCV
#define TRACK_OPTFLOW
#include <dnet/yolo_v2_class.hpp>

#include "shared/messaging/cppsrc/obj_det_coords.pb.h"

using namespace cv;
using namespace std;
using namespace badbot::messages;

#define VALUE_NO_DETECTION -1000

enum CNN_CURRENT_MODE
{
    detecting = 0,
    tracking = 1
};

class DarkCnn : BadBotLogger
{
    public:
        DarkCnn();
        bool init();
        void cleanup() { _keep_running = false;}

        int processCamFrame(cv::Mat &frame, ObjectDetectionCoords *OUTcoords, float &OUT_conf);

        CNN_CURRENT_MODE getCurrentMode();

    protected:
        int getPersonIndex(std::vector<bbox_t> &results);


    protected:
        //min time between two detection attempts
        int _detection_process_frequency_ms;
        //last detection attempt at
        int64_t _last_detection_attempted_at = 0;
        //result of last detection
        std::vector<bbox_t> _result_vec;
        int _personIndex = -1;

        int _img_width;
        int _img_height;
        int _img_mid_x;
        int _img_mid_y;
        cv::Rect _rectMidLine;

        //for calculating delta b/w current and previous detections
        int _last_detection_person_mid_x = -1;
        int _last_detection_person_mid_y = -1;
        int _num_invalid_detections = 0; //see doc below
        int _last_person_mid_angle = -1000;
        /**
         * if current_mid - _last_detection_mid > threshold_distance_detection_mid_point, then this detection is faulty 
         * the reason for introducing this is detections bounce around causing the bot to aggressively try to orient itself
         * as a result creating a left-right movement effectively causing cnn failure due to motion blue
         * may be in future by using a better cnn model these false detections will be minimal, nevertheless this is a good feature
         * to have in order to make sure the detection is inline with the previous position a human was detected at
         */
        int _threshold_distance_detection_mid_point = 20; //actual value read from config file
        /**
         * how many detections exceeding the threshold before we change the _last_detection_person_mid to current
         * this is required to break an infinite ignore cycle which can be engaged due to the above described problem
         */
        int _threshold_distance_detection_mid_point_reset_count = 100; //actual read from file

        std::unique_ptr<Detector> detector;
        Tracker_optflow optFlow;

        bool _keep_running = true;

        //used in function to check if we are actively tracking something
        bool _optical_tracking = false;

        //read from config
        bool _opt_flow_enabled = false;

        //set through yaml, if false, cnn is not initialized
        bool _enabled = true;

        //set from config, the label/class id of person in nn training
        int _PERSON_CLASS_ID = 1;

};