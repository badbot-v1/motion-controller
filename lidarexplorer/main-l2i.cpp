#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <CYdLidar.h>
#include <opencv2/core.hpp>
#include <vector>
#include <map>
#include "shared/drawing/lidarmap.hpp"
#include <sharedstorage/sharedstrings.hpp>
#include <experimental/filesystem>

using namespace std;
using namespace ydlidar;
using namespace cv;
namespace fs = std::experimental::filesystem;

//file_name is the name of the file without path
std::string file_name = "";
//file_name_without_extension is the file name without extension
std::string file_name_without_extension = "";
//file_name_template_frame is the template filename we use to save frames
std::string file_name_template_frame = "";

bool createWorkingDirectoryForRecording(std::string recordingPath)
{
  if(!fs::path(recordingPath).has_filename()){
    return false;
  }

  if(!fs::path(recordingPath).has_stem()){
    return false;
  }
  
  file_name = fs::path(recordingPath).filename();
  file_name_without_extension = "l2i/";
  file_name_without_extension += fs::path(file_name).stem().c_str();
  fs::create_directories(file_name_without_extension);
  file_name_template_frame = file_name_without_extension + "/frame_#.jpg";

  return true;

}

void converRecordingToCSV(map<int,vector<LaserPoint>> &laser_scan_data)
{
  stringstream ss;

  ss << "Frame,";
  for(int i=0;i<360;i++){
    ss << i << ",";
  }
    
  ss << endl;

  int total_readings = 0;
  //since one frame contains many 360 degree scans, we group data based on scan angle
  for(auto it = laser_scan_data.begin(); it != laser_scan_data.end(); it++)
  {

    //init
    map<int, float> mappedReadings;
    for(int i=0;i<360;i++){
      mappedReadings[i] = 0;
    }
   
    //take average
    for(auto p : it->second)
    {
      int angle = floor(radiansToDegrees(p.angle - 0.261799));
      if(angle<0)
      {
        angle += 360;
      }

      float prev_range = mappedReadings[angle];
      if(prev_range > 0){
        mappedReadings[angle] = (prev_range + p.range)/2.0;
      }else{
        mappedReadings[angle] = p.range;
      }
    }

    //format
    ss << it->first << ",";

    for(auto itm = mappedReadings.begin(); itm!=mappedReadings.end(); itm++)
    {
      ss << itm->second << ",";
    }
    ss << endl;
  }

  
  //write to file
  ofstream ofs;
  std::string csv_filename = file_name_without_extension + "/" + file_name + ".csv";
  ofs.open(csv_filename);
  ofs << ss.str();
  ofs.flush();
  ofs.close();
}

bool replace(std::string& str, const std::string& from, const std::string& to) {
    size_t start_pos = str.find(from);
    if(start_pos == std::string::npos)
        return false;
    str.replace(start_pos, from.length(), to);
    return true;
}

void lidarDataToImgMaps(map<int,vector<LaserPoint>> &laser_scan_data)
{
  LidarMap lidarMap(128,128);
  lidarMap.init();

  for(auto frame : laser_scan_data)
  {
    cv::Mat frameImg;

    string file_name = file_name_template_frame;
    if(!replace(file_name, "#", std::to_string(frame.first)))
    {
      continue;
    }
    lidarMap.getCloudAsImage(frameImg, frame.second, false);
    cv::imwrite(file_name, frameImg);
  }
}



int main(int argc, char *argv[])
{
  if(argc < 2){
    cout << "Please provide with a .recording file";
    return -1;
  }

  if(!createWorkingDirectoryForRecording(argv[1]))
  {
    cout << "Unable to create working folder" << endl;
    return -2;
  }

  SharedStrings::get()->setVal("config-file", "./config/l2i.yml");


  ifstream ifs;
  ifs.open(argv[1], ios::binary | ios::in);

  map<int,vector<LaserPoint>> _laser_scan_data;
  
  uint64_t frameCounter = 0;
  uint64_t totalRecordsRead = 0;
  uint32_t recordsToRead = 0;
  ifs.read((char*)&recordsToRead, sizeof(uint32_t));
  
  while(recordsToRead > 0)
  {
    for(auto index=0; index<recordsToRead; index++)
    {
      LaserPoint p;
      memset(&p, 0, sizeof(LaserPoint));

      ifs.read((char*)&p, sizeof(LaserPoint));
      _laser_scan_data[frameCounter].push_back(p);
    }

    cout << "Read [" << recordsToRead << "] records for Frame [" << frameCounter << "]" << endl;

    totalRecordsRead+= recordsToRead;
    recordsToRead = 0;
    frameCounter++;
    ifs.read((char*)&recordsToRead, sizeof(uint32_t));
  }

  ifs.close();

  cout << "Total records read: " << totalRecordsRead << endl;
  cout << "Total frames read: " << frameCounter << endl;

  converRecordingToCSV(_laser_scan_data);
  lidarDataToImgMaps(_laser_scan_data);

  return 0;
}
