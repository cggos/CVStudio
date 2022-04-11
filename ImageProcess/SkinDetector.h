#ifndef SKINDETECTOR_H
#define SKINDETECTOR_H

#include <opencv2/opencv.hpp>

/**
 * @brief 
 * @ref https://www.bytefish.de/blog/skin_color_thresholding.html
 * 
 */
class SkinDetector
{
public:
    SkinDetector();

public:
    static cv::Mat GetSkin_YCrCb(const cv::Mat &srcImg);
    static cv::Mat GetSkin_RGBHCbCr(const cv::Mat &srcImg);

private:
    static bool R1(int R, int G, int B);
    static bool R2(float Y, float Cr, float Cb);
    static bool R3(float H, float S, float V);
};

#endif // SKINDETECTOR_H
