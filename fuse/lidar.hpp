#pragma once


#include <CYdLidar.h>
#include <thread>
#include <chrono>
#include <fstream>
#include <opencv2/core.hpp>
#include <mutex>
#include <boost/signals2.hpp>
#include <mtlog/badbotlogger.hpp>
#include "shared/drawing/lidarmap.hpp"
#include "lidarscan.pb.h"

using namespace ydlidar;
using namespace cv;
using namespace std;

class Lidar : BadBotLogger
{
    public:
        typedef boost::signals2::signal<void (badbot::messages::LidarScan*,bool)> signalLidarScan;
        typedef signalLidarScan::slot_type slot_lidarScan;

    private:
        Lidar();
        static Lidar *_instance;

    public:
        static Lidar *instance();
        ~Lidar();
    
        bool init(int argc, char **argv);
        bool cleanup();

        void connecToSignalLidarScanReady(const slot_lidarScan &slot);

        void getCloudAsImage(cv::Mat &mapimg);
        void plotPointsOfInterest(cv::Mat &mapimg);

        // Gets the distance to points in the region that fits between min and max angles
        // this is a cone structure from origin 
        //
        // Returns
        //  -1 if no points fall within the specified parameters
        //  >0 if distance was found
        int getDistanceToRoi(int angleMin, int angleMax, int depthMin = 5, int depthMax = 10, int samplePoints = 10);

        //utility method for debugging
        //dumps the readins in following format
        //index - radians - degrees - range
        void dumpReadingToConsole();

        int getMapWidth(){ return _map_width;};
        int getMapHeight(){ return _map_height;};

        void setEnabled(bool enabled);
        bool getEnabled();

        bool setLaserState(bool active);

        //recording section
        bool isRecording();
        /**
         * set enable to true to start recording
         * set enable to false to stop recording
         * if recording is in progress it will keep recording on successive calls with parameter true
         * 
         * will return 
         *  true if toggle was success
         *  false in case of error
         *
         **/
        bool toggleRecording(bool enable);
        void onSysShutdown();

    protected:
        void readLidarData();
        void drawText(string text, int textX, int textY, cv::Mat &frame);
        bool readConfig();

    protected:
        CYdLidar laser;

        //thread reads the data and stores to this private variable for processing as needed
        std::thread thread_lidar_reader;
        mutex mutex_laser_scan_data;
        vector<LaserPoint> lastest_laser_scan_data;

        bool _plotting_points_of_interest;
        mutex mutex_points_of_interest;
        vector<LaserPoint> _points_of_interest;

        //we create an image of circles
        cv::Mat mat_template_map;

        //the dimension of image to make for lidar map
        int _map_width = 512;
        int _map_height = 512;
        //max distance in ft we will plot, readings beyond this will not appear on map
        int _max_dist_ft = 20;
        LidarMap _lidarMap;

        //whether to do full init
        bool _enabled = true;

        //whether to keep running
        bool _keep_running = true;

        //for alignment of lidar to base platform
        float _mount_diff_radians = 0.0;
        
        //data recording section
        //whether recording is enabled
        std::atomic_bool _recording_enabled;
        //stats
        uint32_t _recording_frames_captured = 0;
        //time started
        std::chrono::time_point<std::chrono::milliseconds> _recording_start_time;
        //name of file being recorded to
        std::string _recording_file_name;
        //file to write to
        std::fstream _recording_file;

        //from config file
        float _reported_distance_on_disable = 0;


        //signal
        signalLidarScan _signalLidarScan;
        
    //from config yml
    protected:
        std::string _CONFIG_PORT = "/dev/ttyUSB0";
        int _CONFIG_MAX_ANGLE = 180;
        int _CONFIG_MIN_ANGLE = -180;
        float _CONFIG_MAX_RANGE = 64.0;
        float _CONFIG_MIN_RANGE = 0.01;


};