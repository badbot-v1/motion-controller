#pragma once

#include <string>
#include <opencv2/core.hpp>

using namespace std;
using namespace cv;

#define degreesToRadians(angleDegrees) ((angleDegrees) * M_PI / 180.0)
#define radiansToDegrees(angleRadians) ((angleRadians) * 180.0 / M_PI)


class DrawingBase
{

    protected:
        void drawText(string text, int textX, int textY, cv::Mat &frame);

};