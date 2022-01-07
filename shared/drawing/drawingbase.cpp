#include "drawingbase.hpp"
#include <opencv2/opencv.hpp>

void DrawingBase::drawText(string text, int textX, int textY, cv::Mat &frame)
{

    int fontFace = FONT_HERSHEY_PLAIN;
    double fontScale = 1.0;
    int thickness = 1;

    Point textOrg(textX, textY);

    putText(frame, text, textOrg, fontFace, fontScale,
        Scalar::all(255), thickness, 8);
}
