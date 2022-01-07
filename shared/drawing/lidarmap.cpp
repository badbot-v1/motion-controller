#include "lidarmap.hpp"
#include <opencv2/opencv.hpp>


LidarMap::LidarMap()
:BadBotLogger("LidarMap")
{
}

LidarMap::LidarMap(int map_width, int map_height)
:BadBotLogger("LidarMap")
{
    _map_width = map_width;
    _map_height = map_height;

}

void LidarMap::init()
{
    _mat_template_map = cv::Mat(_map_height, _map_width, CV_8UC3, Scalar::all(0));
    _mat_plot = cv::Mat(_map_height, _map_width, CV_8UC3, Scalar::all(0));
    _mat_connected_dots = cv::Mat(_map_height, _map_width, CV_8UC3, Scalar::all(0));

    ///////////////////////////
    //lidar radar map
    ///////////////////////////
    _map_width_mid = _map_width / 2;
    _map_height_mid = _map_height / 2;
    _x_pixels_per_ft = (_map_width/2) / _max_dist_ft;
    _y_pixels_per_ft = (_map_height/2) / _max_dist_ft;

    Point p_map_mid(
        _map_width_mid,
        _map_height_mid
    );

    int pixels_per_foot = sqrt((_x_pixels_per_ft *_x_pixels_per_ft) + (_y_pixels_per_ft * _y_pixels_per_ft));
    for(int i=0; i< (_max_dist_ft/_circle_dist); i++)
    {
        int radius =  pixels_per_foot *  (i *_circle_dist);
        cv::circle(_mat_template_map, p_map_mid, radius, Scalar(100,100,100), 1);
    }

        for(int i=0; i<=180; i+=10)
    {
        float rads = degreesToRadians(i);
        Point end(
            _map_width_mid + cos(rads) * _x_pixels_per_ft * pixels_per_foot,
            _map_height_mid + sin(rads) * _y_pixels_per_ft * pixels_per_foot
        );
        // cout << i << " " << end.x << " " << end.y << endl;
        cv::line(_mat_template_map,p_map_mid,end,Scalar(0,150,0));

        char temp[100] = {0};
        sprintf(temp, "%d", i);
        drawText(temp, end.x, end.y, _mat_template_map);
    }


    //draw lines at 10 degrees
    //0 to -180
    for(int i=0; i>-180; i-=10)
    {
        float rads = degreesToRadians(i);
        Point end(
            _map_width_mid + cos(rads) * _x_pixels_per_ft * pixels_per_foot,
            _map_height_mid + sin(rads) * _y_pixels_per_ft * pixels_per_foot
        );
        // cout << i << " " << end.x << " " << end.y << endl;
        cv::line(_mat_template_map,p_map_mid,end,Scalar(0,150,0));

        char temp[100] = {0};
        sprintf(temp, "%d", i);
        drawText(temp, end.x, end.y, _mat_template_map);
    }

    ///////////////////////////
    //lidar 2d plot (point concentration)
    ///////////////////////////
    cv::rectangle(_mat_plot, Point(1,1), Point(_mat_plot.cols-1, _mat_plot.rows-1),Scalar(0,255,0) , 2);

}

void LidarMap::getCloudAsImage(cv::Mat &mapimg, vector<LaserPoint> &laser_scan_data, bool drawHints, float mount_diff_radians, bool isPointsOfInterestData)
{

    int radius = 1;
    Scalar color = Scalar(0,0,255);

    if(isPointsOfInterestData)
    {
        radius = 3;
        color = Scalar(0,255,0);
    }else{
        if(drawHints)
        {
            mapimg = _mat_template_map.clone();
        }else{
            mapimg = cv::Mat(_map_height, _map_width, CV_8UC3, Scalar::all(0));
        }
    }

    //draw points
    #pragma omp parallel for
    for(size_t i=0; i<laser_scan_data.size(); i++)
    {
        float angle = laser_scan_data[i].angle + mount_diff_radians;
        
        int x = _map_width_mid + (cos(angle) * _x_pixels_per_ft * laser_scan_data[i].range);
        int y = _map_height_mid + (sin(angle) * _y_pixels_per_ft * laser_scan_data[i].range);
        
        Point pointToDraw(
            x,y
        );
        
        cv::circle(mapimg, pointToDraw, radius, color, -1);
    }
}

void LidarMap::getCloudAsPlot(cv::Mat &mapimg, vector<LaserPoint> &laser_scan_data, bool drawHints)
{
    if(drawHints)
    {
        mapimg = _mat_plot.clone();
    }else{
        mapimg = cv::Mat(_map_height, _map_width, CV_8UC3, Scalar::all(0));
    }

    //how many pixels on x axis correspond to 1 unit of measurement (degrees)
    float x_ppu = (float)mapimg.cols/360.0;
    float y_ppu = (float)mapimg.rows/20.0; //we can plot maximum of 14 ft dist

    //draw points
    #pragma omp parallel for
    for(size_t i=0; i<laser_scan_data.size(); i++)
    {
        if(laser_scan_data[i].range > 20.0)
        {
            continue;
        }

        float angle = radiansToDegrees(laser_scan_data[i].angle - 0.261799);
        if(angle < 0){
            angle += 360;
        }
        
        int x = std::min(x_ppu * angle, (float)mapimg.cols);
        int y = y_ppu * laser_scan_data[i].range;
        
        Point pointToDraw(
            x,y
        );
        
        cv::circle(mapimg, pointToDraw, 1, Scalar(0,0,255), -1);
    }
}

void LidarMap::getPolarPointCoordinates(Point &OUT, LaserPoint &lp)
{
    float angle = lp.angle - 0.261799;
    OUT.x = _map_width_mid + (cos(angle) * _x_pixels_per_ft * lp.range);
    OUT.y = _map_height_mid + (sin(angle) * _y_pixels_per_ft * lp.range);
}

inline float euclideanDist(Point& p, Point& q) {
    Point diff = p - q;
    return cv::sqrt(diff.x*diff.x + diff.y*diff.y);
}

void LidarMap::getCloudAsConnectedLines(cv::Mat &mapimg, vector<LaserPoint> &laser_scan_data)
{
    mapimg = _mat_connected_dots.clone();

    #pragma omp parallel for
    for(size_t i=0; i<laser_scan_data.size()-2; i++)
    {
        Point p1;
        getPolarPointCoordinates(p1, laser_scan_data[i]);

        Point p2;
        getPolarPointCoordinates(p2, laser_scan_data[i+1]);

        double dist = euclideanDist(p1, p2);
        // cout 
        //     << radiansToDegrees(laser_scan_data[i].angle) << " " << laser_scan_data[i].range << " " 
        //     << radiansToDegrees(laser_scan_data[i+1].angle) << " " << laser_scan_data[i+1].range <<  " "
        //     << dist 
        // << endl;

        if(dist <= 5.0)
        {
            cv::circle(mapimg, p1, 1, Scalar(255,0,0), -1);
            cv::circle(mapimg, p2, 1, Scalar(255,255,0), -1);

            cv::line(mapimg, p1, p2, Scalar(255,0,0),1,8);
        }else{
            cv::circle(mapimg, p1, 1, Scalar(255,255,255), -1);
        }
    }
}


int LidarMap::getMapDimensions(int &width, int &height)
{
    width = _map_width;
    height = _map_height;
}

int LidarMap::setMapDimensions(int width, int height)
{
    _map_width = width;
    _map_height = height;
}