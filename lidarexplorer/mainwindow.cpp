#include "mainwindow.h"
#include <iostream>
#include <QtWidgets/QFileDialog>
#include <fstream>
#include <yaml-cpp/yaml.h>
#include <sharedstorage/sharedstrings.hpp>

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent)
{ 
  setupUi(this);
  _lidarMap.setMapDimensions(512,512);
  _lidarMap.init();
}

void MainWindow::on_actionE_xit_triggered()
{
  close();
}

void MainWindow::on_actionL_oad_triggered()
{
  QString fileName = QFileDialog::getOpenFileName(this,
    tr("Open Lidar Recording"), "", tr("Lidar Recording Files (*.record)"));
  cout << fileName.toStdString() << endl;

  YAML::Node config = YAML::LoadFile(SharedStrings::get()->getVal("config-file"));
  _mount_ang_diff = config["fuse"]["mount_ang_diff"].as<float>();

  cout << "_mount_ang_diff: " << _mount_ang_diff << endl << endl;

  ifstream ifs;
  ifs.open(fileName.toStdString(), ios::binary | ios::in);

  _laser_scan_data.clear();

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

    totalRecordsRead+= recordsToRead;
    recordsToRead = 0;
    frameCounter++;
    ifs.read((char*)&recordsToRead, sizeof(uint32_t));
  }

  ifs.close();

  cout << "Total records read: " << totalRecordsRead << endl;
  cout << "Total frames read: " << frameCounter << endl;

  _number_of_frames = frameCounter;
  spinBox->setMinimum(0);
  spinBox->setMaximum(frameCounter);
  scrollbar->setMinimum(0);
  scrollbar->setMaximum(frameCounter);

  spinBox->setValue(0);
  updateLabelText();
  updateImage(0);

}

void MainWindow::updateLabelText()
{
  QString text = QString("%1 of %2").arg(spinBox->value()).arg(_number_of_frames);
  lblCurrRecord->setText(text);
}

void MainWindow::updateImage(int index)
{
  cv::Mat lidarmap;
  _lidarMap.getCloudAsImage(lidarmap,_laser_scan_data[index], true, _mount_ang_diff);
  imglbl->setPixmap(QPixmap::fromImage(QImage(lidarmap.data, lidarmap.cols, lidarmap.rows, lidarmap.step, QImage::Format_RGB888)));


  cv::Mat plotImg;
  _lidarMap.getCloudAsPlot(plotImg,_laser_scan_data[index]);
  plotLbl->setPixmap(QPixmap::fromImage(QImage(plotImg.data, plotImg.cols, plotImg.rows, plotImg.step, QImage::Format_RGB888)));

  cv::Mat lineImg;
  _lidarMap.getCloudAsConnectedLines(lineImg,_laser_scan_data[index]);
  lineLbl->setPixmap(QPixmap::fromImage(QImage(lineImg.data, lineImg.cols, lineImg.rows, lineImg.step, QImage::Format_RGB888)));

  
}

void MainWindow::on_spinBox_valueChanged(int value)
{
  scrollbar->setValue(value);
  updateLabelText();
  updateImage(value);

}

void MainWindow::on_scrollbar_valueChanged(int value)
{
  spinBox->setValue(value);
  updateLabelText();
  updateImage(value);
}