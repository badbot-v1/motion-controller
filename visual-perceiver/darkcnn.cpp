#include "darkcnn.hpp"
#include <sharedstorage/sharedstrings.hpp>
#include <yaml-cpp/yaml.h>
#include <chrono>




DarkCnn::DarkCnn()
:BadBotLogger("cnn")
{
}

bool DarkCnn::init()
{
    _log->debug("Being init.");
    
    YAML::Node config = YAML::LoadFile(SharedStrings::get()->getVal("config-file"));

    _enabled = config["cnn"]["enable"].as<bool>();
    _opt_flow_enabled = config["cnn"]["opt_flow_enabled"].as<bool>();
    
    _detection_process_frequency_ms = config["cnn"]["detection_process_frequency_ms"].as<int>();
    _threshold_distance_detection_mid_point = config["cnn"]["threshold_distance_detection_mid_point"].as<int>();
    _threshold_distance_detection_mid_point_reset_count = config["cnn"]["threshold_distance_detection_mid_point_reset_count"].as<int>();
    _img_width = config["cnn"]["width"].as<int>();
    _img_height = config["cnn"]["height"].as<int>();
    _PERSON_CLASS_ID = config["cnn"]["person_class_id"].as<int>();

    if(!_enabled){
        _log->warn("Enabled [{}]", _enabled);
    }else{
        _log->info("Enabled [{}]", _enabled);
    }

    _log->info("Optical flow enabled [{}]", _opt_flow_enabled);
    _log->info("_threshold_distance_detection_mid_point [{}]", _threshold_distance_detection_mid_point);
    _log->info("_threshold_distance_detection_mid_point_reset_count [{}]", _threshold_distance_detection_mid_point_reset_count);
    
    _log->info("Network config [{}]", config["cnn"]["detection_config"].as<std::string>());
    _log->info("Network weights [{}]", config["cnn"]["detection_weights"].as<std::string>());
    _log->info("Img Dimensions HxW {}x{}",config["cnn"]["height"].as<int>(),config["cnn"]["width"].as<int>());
    _log->info("Detection frequency [{}]",config["cnn"]["detection_process_frequency_ms"].as<int>());
    _log->info("_PERSON_CLASS_ID [{}]", _PERSON_CLASS_ID);

    if(_enabled)
    {
        detector.reset(new Detector(config["cnn"]["detection_config"].as<std::string>(), 
            config["cnn"]["detection_weights"].as<std::string>()));
    

        //warm up
        _log->trace("Warning up NN.");
        auto img = detector->load_image(config["cnn"]["warm_up_img"].as<std::string>());
        std::vector<bbox_t> result_vec = detector->detect(img);
        detector->free_image(img);

        _log->debug("Found [{}] objects.", result_vec.size());
    }else{
        _log->warn("CNN disabled. Not performing warmup.");
    }

    _img_mid_x = _img_width / 2;
    _img_mid_y = _img_height / 2;

    _rectMidLine = cv::Rect(
        _img_mid_x,
        _img_mid_y - 50,
        1,
        100
    );

    _log->debug("End init.");

    return true;
}

using namespace std::chrono;

int DarkCnn::processCamFrame(cv::Mat &frame, ObjectDetectionCoords *OUTcoords, float &OUT_conf)
{

    if(!_enabled)
    {
        return VALUE_NO_DETECTION;
    }


    if(!_opt_flow_enabled || !_optical_tracking)
    {
        milliseconds ms = duration_cast< milliseconds >(
            system_clock::now().time_since_epoch()
        );
        int64_t now = ms.count();

        if((now - _last_detection_attempted_at) > _detection_process_frequency_ms)
        {
            _last_detection_attempted_at = now;
            
            std::chrono::time_point<std::chrono::steady_clock> begin = std::chrono::steady_clock::now();

            _result_vec = detector->detect(frame);

            std::chrono::time_point<std::chrono::steady_clock> end = std::chrono::steady_clock::now();
            std::chrono::milliseconds duration = std::chrono::duration_cast<milliseconds> (end - begin);

            _log->trace("Took [{}]ms for detection", duration.count());

            _personIndex = getPersonIndex(_result_vec);

            if(_opt_flow_enabled && _personIndex >= 0)
            {
                _optical_tracking = true;
            
                std::vector<bbox_t> opt_track_vec;
                bbox_t *bbPerson = &_result_vec[_personIndex];
                int person_mid_x = bbPerson->x + ( bbPerson->w / 2); 
                int person_mid_y = bbPerson->y + ( bbPerson->h / 2);
                
                bbPerson->x = person_mid_x-50;
                bbPerson->w = 100;
                bbPerson->y = person_mid_y-50;
                bbPerson->h = 100;
                
                opt_track_vec.push_back(_result_vec[_personIndex]);

                //hand over to optical flow
                optFlow.update_tracking_flow(frame, opt_track_vec);
            }
        }
    }
    else if(_opt_flow_enabled && _optical_tracking)
    {
        _result_vec = optFlow.tracking_flow(frame);
    }

    if(_personIndex >= 0)
    {
        //we have lost the target
        if(_result_vec.size() <=0 ){
            _optical_tracking = false;
            return VALUE_NO_DETECTION;
        }

        //fill out return val
        for(int i=0;i<_result_vec.size();i++)
        {
            badbot::messages::Coords* coords = OUTcoords->add_coordinates();
            coords->set_y(_result_vec[i].y);
            coords->set_x(_result_vec[i].x);
            coords->set_h(_result_vec[i].h);
            coords->set_w(_result_vec[i].w);
            coords->set_confidence(_result_vec[i].prob*100.0);
            coords->set_objid(_result_vec[i].obj_id);
        }

        bbox_t *bbPerson = &_result_vec[_personIndex];
        int person_mid_x = bbPerson->x + ( bbPerson->w / 2); 
        int person_mid_y = bbPerson->y + ( bbPerson->h / 2); 

        _log->trace("Found object at (y,x) [{},{}]", bbPerson->y, bbPerson->x);
    
        //60 deg fov = 0.0575 per pixel on 1280x920 (WxH) image - tested
        //160 deg fov = 0.125 deg / pixel on 1280x720 (WxH) image
        //int person_mid_angle = (_img_mid_x - person_mid_x) * 0.0575 * -1;

        //https://www.raspberrypi.org/documentation/hardware/camera/
        //v2 hfov is 62.2 degrees
        // 62.2 dev fov = 0.0971875 per pixel on 640x480 (WxH) image fed to neural net
        int person_mid_angle = (int)((float)(_img_mid_x - person_mid_x) * 0.0971875f * -1.0f);
        OUT_conf = bbPerson->prob*100.0;
        
        _log->trace("Person at angle [{}] conf [{}]", person_mid_angle, OUT_conf);

        //calculate delta here and ignore this calculation if exceeding
        bool validDetection = true;

        if(_last_detection_person_mid_x >=0 )
        {
            //calculate distance
            int delta = sqrt((person_mid_x - _last_detection_person_mid_x)^2 + (person_mid_y - _last_detection_person_mid_y)^2);

            if(delta <= _threshold_distance_detection_mid_point)
            {
                validDetection = true;
            }else
            {
                validDetection = false;
                _num_invalid_detections++;

                if(_num_invalid_detections >= _threshold_distance_detection_mid_point_reset_count)
                {
                    _num_invalid_detections = 0;
                    validDetection = true;

                    return VALUE_NO_DETECTION;
                }
            }
        }

        
        if(validDetection)
        {
            //update last values
            _last_detection_person_mid_x = person_mid_x;
            _last_detection_person_mid_y = person_mid_y;
            _last_person_mid_angle = person_mid_angle;

            return person_mid_angle;
        }
    }

    return VALUE_NO_DETECTION;

}

int DarkCnn::getPersonIndex(std::vector<bbox_t> &results)
{
    int ret = -1;

    float highestProb = 0.0;

    for(uint i=0; i<results.size(); i++)
    {
        if
        (
            results[i].prob > highestProb
            &&
            results[i].obj_id == _PERSON_CLASS_ID
        ){
            ret = i;
            highestProb = results[i].prob;
        }

    }
    return ret;
}


CNN_CURRENT_MODE DarkCnn::getCurrentMode()
{
    CNN_CURRENT_MODE currentMode = CNN_CURRENT_MODE::detecting;

    if(_optical_tracking)
    {
        currentMode = CNN_CURRENT_MODE::tracking;
    }

    return currentMode;
}
