#pragma once

#include <CYdLidar.h>
#include <opencv2/core.hpp>
#include <opencv2/opencv.hpp>
#include "shared/log/badbotlogger.hpp"
#include "shared/drawing/drawingbase.hpp"

using namespace ydlidar;
using namespace cv;
using namespace std;


class LidarMap : public DrawingBase, BadBotLogger
{
    public:
        LidarMap();
        LidarMap(int map_width, int map_height);
        void init();
        
        /**
         * mapimg is only initialized if isPointsOfInterestData is false
         * mapimage is cloned to the template if drawHints is true, or, initialized to black opaque if drawHints is false
         * */
        void getCloudAsImage(cv::Mat &mapimg, vector<LaserPoint> &laser_scan_data, bool drawHints=true, float mount_diff_radians=0.0, bool isPointsOfInterestData = false);
        void getCloudAsPlot(cv::Mat &mapimg, vector<LaserPoint> &laser_scan_data, bool drawHints=true);
        void getCloudAsConnectedLines(cv::Mat &mapimg, vector<LaserPoint> &laser_scan_data);

        int getMapDimensions(int &width, int &height);
        int setMapDimensions(int width, int height);
    
    protected:
        void getPolarPointCoordinates(Point &OUT, LaserPoint &lp);
        

    protected:
        //the dimension of image to make for lidar map
        int _map_width = 512;
        int _map_height = 512;
        //max distance in ft we will plot, readings beyond this will not appear on map
        int _max_dist_ft = 20;
        //the mid point of the map
        int _map_width_mid = 0;
        int _map_height_mid = 0;
        //used to plot points, calculated later in init
        int _x_pixels_per_ft = 0;
        int _y_pixels_per_ft = 0;
        //how many dist (ft) does one circle cover
        int _circle_dist = 5;
        //we create an image of circles
        cv::Mat _mat_template_map;
        cv::Mat _mat_plot;
        cv::Mat _mat_connected_dots;

};