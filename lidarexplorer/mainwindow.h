#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtCore/QObject>
#include <QtWidgets/QMainWindow>
#include <CYdLidar.h>
#include <opencv2/core.hpp>
#include <vector>
#include <map>
#include "lidarexplorer/ui_mainwindow.h"
#include "shared/drawing/lidarmap.hpp"

using namespace ydlidar;
using namespace cv;


class MainWindow : public QMainWindow, private Ui::MainWindow
{
  Q_OBJECT

public:
  MainWindow(QWidget *parent = 0);

private:
  void updateLabelText();
  void updateImage(int index);

private:
  map<int,vector<LaserPoint>> _laser_scan_data;
  uint64_t _number_of_frames;
  LidarMap _lidarMap;
  float _mount_ang_diff = 0.0f;

private slots:
  void on_spinBox_valueChanged(int value);
  void on_scrollbar_valueChanged(int value);
  void on_actionE_xit_triggered();
  void on_actionL_oad_triggered();

// private:
//   Ui::MainWindow ui;
};

#endif // MAINWINDOW_H
