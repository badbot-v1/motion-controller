#include "lidar.hpp"
#include <time.h>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <opencv2/opencv.hpp>
#include <stdlib.h>
#include <sharedstorage/sharedstrings.hpp>
#include "shared/system/sysevents.hpp"
#include <yaml-cpp/yaml.h>


using namespace cv;

#define degreesToRadians(angleDegrees) ((angleDegrees) * M_PI / 180.0)
#define radiansToDegrees(angleRadians) ((angleRadians) * 180.0 / M_PI)

Lidar::Lidar()
:BadBotLogger("Lidar")
{
    SysEvents::getInstance()->connectToSignalShutdown(boost::bind(&Lidar::onSysShutdown, this));
    this->_recording_enabled = false;
}

Lidar::~Lidar()
{

}

void Lidar::drawText(string text, int textX, int textY, cv::Mat &frame)
{

    int fontFace = FONT_HERSHEY_PLAIN;
    double fontScale = 1.0;
    int thickness = 1;

    Point textOrg(textX, textY);

    putText(frame, text, textOrg, fontFace, fontScale,
        Scalar::all(255), thickness, 8);
}

void Lidar::setEnabled(bool enabled)
{
    _enabled = enabled;
    
}

bool Lidar::getEnabled()
{
    return _enabled;
}

bool Lidar::readConfig()
{
    bool ret = false;


    try{
        
        YAML::Node config = YAML::LoadFile(SharedStrings::get()->getVal("config-file"));
        _CONFIG_PORT = config["lidar_x4"]["port"].as<std::string>();
        _CONFIG_MAX_ANGLE = config["lidar_x4"]["maxAngle"].as<int>();
        _CONFIG_MIN_ANGLE = config["lidar_x4"]["minAngle"].as<int>();
        _CONFIG_MAX_RANGE = config["lidar_x4"]["maxRange"].as<float>();
        _CONFIG_MIN_RANGE = config["lidar_x4"]["minRange"].as<float>();
        _map_width = config["lidar_x4"]["mapWidth"].as<int>();
        _map_height = config["lidar_x4"]["mapHeight"].as<int>();
        _max_dist_ft = config["lidar_x4"]["maxDistance"].as<int>();
        _enabled = config["lidar_x4"]["enabled"].as<bool>();
        _mount_diff_radians = config["lidar_x4"]["mountDifferenceInRadians"].as<float>();
        _plotting_points_of_interest = config["lidar_x4"]["plot_points_of_interest"].as<bool>();
        _reported_distance_on_disable = config["lidar_x4"]["reported_distance_on_disable"].as<float>();
        
        // cout << "Config read successfully. Will be using following"
        _log->info("Config read successfully. Will be using following parameters for LIDAR.");
        _log->info("port  [{}]", _CONFIG_PORT);
        _log->info("maxAngle  [{}]", _CONFIG_MAX_ANGLE);
        _log->info("minAngle  [{}]", _CONFIG_MIN_ANGLE);
        _log->info("maxRange  [{}]", _CONFIG_MAX_RANGE);
        _log->info("minRange  [{}]", _CONFIG_MIN_RANGE);
        _log->info("_map_width  [{}]", _map_width);
        _log->info("_map_height  [{}]", _map_height);
        _log->info("_max_dist_ft  [{}]", _max_dist_ft);
        _log->info("mountDifferenceInRadians  [{}]", _mount_diff_radians);
        _log->info("plot_points_of_interest  [{}]", _plotting_points_of_interest);
        _log->info("reported_distance_on_disable  [{}]", _reported_distance_on_disable);

        if(_enabled)
        {
            _log->info("_enabled  [{}]", _enabled);
        }else{
            _log->warn("_enabled  [{}]", _enabled);
        }


        ret = true;

    }catch(const std::exception& e){
        _log->error(e.what());
    }

    return ret;
}

bool Lidar::init(int argc, char **argv)
{
    bool bRet = false;

    if(!readConfig()){
        return false;
    }



    _lidarMap.setMapDimensions(_map_width, _map_height);
    _lidarMap.init();

    //we do not init lidar, just setup everything else
    if(!_enabled)
    {
        _log->info("Lidar partial init completed.");
        return true;
    }


    // std::string port;
    // std::map<std::string, std::string> ports =
    //     ydlidar::YDlidarDriver::lidarPortList();
    
    // if (ports.size() == 1) {
    //     port = ports.begin()->second;

    // } else if (ports.size() == 0) {
    //     cout << "No lidars present. exiting." << endl;
    //     return false;        
    // }else{
    //     cout << "Multiple lidars present, not configured for that. exiting." << endl;
    //     return false;
    // }

    // cout << "Using port " << port << " for lidar." << endl;

    int baudrate = 115200;
    float frequency = 8.0;

    //<! lidar port
    laser.setSerialPort(_CONFIG_PORT);
    //<! lidar baudrate
    laser.setSerialBaudrate(baudrate);

    //<! fixed angle resolution
    laser.setFixedResolution(false);
    //<! rotate 180
    laser.setReversion(false); //rotate 180
    //<! Counterclockwise
    laser.setInverted(false);//ccw
    laser.setAutoReconnect(false);//hot plug
    //<! one-way communication
    laser.setSingleChannel(true);

    //<! tof lidar
    laser.setLidarType(!isTOFLidar);
    //unit: °
    laser.setMaxAngle(_CONFIG_MAX_ANGLE);
    laser.setMinAngle(_CONFIG_MIN_ANGLE);

    //unit: m
    laser.setMinRange(_CONFIG_MIN_RANGE);
    laser.setMaxRange(_CONFIG_MAX_RANGE);

    //unit: Hz
    laser.setScanFrequency(frequency);
    std::vector<float> ignore_array;
    ignore_array.clear();
    laser.setIgnoreArray(ignore_array);

    bRet = laser.initialize();

    if (bRet) 
    {
        bRet = laser.turnOn();
        if(bRet == true)
        {
            thread_lidar_reader = std::thread( [this] { readLidarData(); });
        }
        
    }

    if(!bRet){
        _log->error("Unable to initialize LIDAR.");
    }

    return bRet;
}

bool Lidar::cleanup()
{
    bool bRet = false;
    
    laser.turnOff();
    laser.disconnecting();

    return bRet;
}

void Lidar::readLidarData()
{

  while (_keep_running && ydlidar::ok()) 
  {
    bool hardError;
    LaserScan scan;


    if (laser.doProcessSimple(scan, hardError)) {
      // fprintf(stdout, "Scan received[%llu]: %u ranges is [%f]Hz\n",
      //         scan.stamp,
      //         (unsigned int)scan.points.size(), 1.0 / scan.config.scan_time);
      // fflush(stdout);
        if(scan.points.size() > 0)
        {
            std::lock_guard<std::mutex> guard(mutex_laser_scan_data);
            lastest_laser_scan_data = scan.points;
        }
        else{
            continue;
        }

        if(_recording_enabled)
        {
            uint32_t num_samples = scan.points.size();
            _recording_file.write((const char*)&num_samples, sizeof(uint32_t));

            for(unsigned int i=0;  i<scan.points.size(); i++)
            {
                LaserPoint *p = &scan.points[i];
                _recording_file.write((const char*)p, sizeof(LaserPoint));
            }

            _recording_frames_captured++;
        }

        //raise event
        badbot::messages::LidarScan *lidarScan 
            = new badbot::messages::LidarScan();
        
        for(unsigned int i=0;  i<scan.points.size(); i++)
        {
            LaserPoint *p = &scan.points[i];
            
            badbot::messages::LidarPoint *scanPoint = lidarScan->add_scanpoints();
            scanPoint->set_angle(p->angle);
            scanPoint->set_range(p->range);
        }

        _signalLidarScan(lidarScan, false);

    }
  }

}

//may be move to as part of threaded op
void Lidar::getCloudAsImage(cv::Mat &mapimg)
{
    vector<LaserPoint> laser_scan_data;
    {
        std::lock_guard<std::mutex> guard(mutex_laser_scan_data);
        //make copy
        laser_scan_data = lastest_laser_scan_data;
    }

    _lidarMap.getCloudAsImage(mapimg, laser_scan_data, true, _mount_diff_radians);
}

void Lidar::plotPointsOfInterest(cv::Mat &mapimg)
{
    if(!_plotting_points_of_interest)
    {
        return;
    }
    
    vector<LaserPoint> laser_scan_data;
    {
        std::lock_guard<std::mutex> guard(mutex_points_of_interest);
        //make copy
        laser_scan_data = _points_of_interest;
    }

    _lidarMap.getCloudAsImage(mapimg, laser_scan_data, true, _mount_diff_radians, true);
}

int Lidar::getDistanceToRoi(int angleMin, int angleMax, int depthMin, int depthMax, int samplePoints)
{
    int ret = -1;

    if(!_enabled)
    {
        //_log->trace("_reported_distance_on_disable [{}]", _reported_distance_on_disable);
        return _reported_distance_on_disable;
    }

    // angleMin < 0 ? angleMin = 359 + angleMin : angleMin;
    // angleMax < 0 ? angleMax = 359 + angleMax : angleMax;

    float ang_begin = degreesToRadians(angleMin);
    float ang_end = degreesToRadians(angleMax);
    
    //filter all the points
    vector<LaserPoint> laser_scan_data;
    {
        std::lock_guard<std::mutex> guard(mutex_laser_scan_data);
        //make copy
        laser_scan_data = lastest_laser_scan_data;
    }

    badbot::messages::LidarScan *lidarScan 
            = new badbot::messages::LidarScan();

    float dist_total = 0.0;
    int processed_points = 1;

    for(size_t i=0;  i<laser_scan_data.size() && processed_points < samplePoints; i++)
    {
        LaserPoint *p = &laser_scan_data[i];
        float angle = laser_scan_data[i].angle + _mount_diff_radians; 

        if( 
            (ang_begin <= angle && angle <= ang_end)
        )
        {
            if(depthMin <= p->range && p->range <= depthMax)
            {
                dist_total += p->range;
                processed_points ++;

                badbot::messages::LidarPoint *scanPoint = lidarScan->add_scanpoints();
                scanPoint->set_angle(p->angle);
                scanPoint->set_range(p->range);
            }
        }
    }

    //finally take average
    //dont really need to push data to new vec, but may become convenient for debugging in these early days
    //consider wrapping in a define macro to enable if debug needed
    if(processed_points > 0)
    {
        ret = (int) (dist_total / (float)processed_points);
        _signalLidarScan(lidarScan, true);
    }

    
    _log->trace("Found [{}] pts b/w angles [{}] & [{}], depth b/w [{}] & [{}] with dist [{}]", processed_points, angleMin, angleMax, depthMin, depthMax, ret);

    return ret;

}

void Lidar::dumpReadingToConsole()
{
    vector<LaserPoint> laser_scan_data;
    {
        std::lock_guard<std::mutex> guard(mutex_laser_scan_data);
        //make copy
        laser_scan_data = lastest_laser_scan_data;
    }

    char buffer[100] = {0};
    for(size_t i=0; i<laser_scan_data.size();i++)
    {
        LaserPoint *p = &laser_scan_data[i];
        sprintf(buffer, "[%d] r:[%f] d:[%f] r:[%f]", (int)i, p->angle, radiansToDegrees(p->angle), p->range);
        cout << buffer << endl;

        memset(buffer, 0, sizeof(buffer));
    }
}


bool Lidar::setLaserState(bool active)
{
    if(!_enabled)
    {
        return true;
    }

    if(!active)
    {
        laser.turnOff();
    }else{
        laser.turnOn();
    }

    return true;
}

Lidar *Lidar::_instance = nullptr;
Lidar *Lidar::instance()
{
    if(_instance == nullptr){
        _instance = new Lidar();
    }

    return _instance;
}


bool Lidar::isRecording()
{
    return _recording_enabled;
}

bool Lidar::toggleRecording(bool enable)
{
    if(enable){

        //note the start time
        //_recording_start_time = std::chrono::system_clock::now();

        //open the file
        time_t tt = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        tm local_time = *localtime(&tt);
        char filename[1024] = {0};
        sprintf(filename, "lidar-recording-%04d%02d%02d-%02d%02d%02d.record",
            local_time.tm_year,
            local_time.tm_mon,
            local_time.tm_mday,
            local_time.tm_hour,
            local_time.tm_min,
            local_time.tm_sec
        );

        _recording_file_name = filename;
        _log->info("Will be recording in file [{}]", _recording_file_name);
        _recording_file.open(_recording_file_name, ios::binary | ios::out);
        

        //mark for recording
        _recording_enabled = true;
        _log->info("Recording started.");
    }else{
        //stop recording
        _recording_enabled = false;
        _log->info("Recording stopped.");

        //close the file
        _recording_file.flush();
        _recording_file.close();
        _log->info("Recording completed in file [{}] with [{}] records written.", _recording_file_name, _recording_frames_captured);
        _recording_frames_captured = 0;
        _recording_file_name.clear();
    }

    return true;
}

void Lidar::onSysShutdown()
{
    _log->info("Shut down started.");
    _keep_running = false;

    if(thread_lidar_reader.joinable())
    {
        thread_lidar_reader.join();
    }

    cleanup();

    _log->info("Shut down completed.");
    
}

void Lidar::connecToSignalLidarScanReady(const slot_lidarScan &slot)
{
    _signalLidarScan.connect(slot);
}