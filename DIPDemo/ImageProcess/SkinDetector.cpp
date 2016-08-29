#include "SkinDetector.h"

SkinDetector::SkinDetector()
{
}

//this function will return a skin masked image
cv::Mat SkinDetector::GetSkin_YCrCb(const cv::Mat &srcImg)
{
    //YCrCb threshold
    // You can change the values and see what happens
    int Y_MIN  = 0;
    int Y_MAX  = 255;
    int Cr_MIN = 133;
    int Cr_MAX = 173;
    int Cb_MIN = 77;
    int Cb_MAX = 127;

    cv::Mat skin;
    //first convert our RGB image to YCrCb
    cv::cvtColor(srcImg,skin,cv::COLOR_BGR2YCrCb);

    //uncomment the following line to see the image in YCrCb Color Space
    //cv::imshow("YCrCb Color Space",skin);

    //filter the image in YCrCb color space
    cv::inRange(skin,cv::Scalar(Y_MIN,Cr_MIN,Cb_MIN),cv::Scalar(Y_MAX,Cr_MAX,Cb_MAX),skin);

    return skin;
}

/*
Nusirwan Anwar bin Abdul Rahman, Kit Chong Wei and John See.
RGB-H-CbCr Skin Colour Model for Human Face Detection.*/
cv::Mat SkinDetector::GetSkin_RGBHCbCr(cv::Mat const &srcImg) {
    // allocate the result matrix
    cv::Mat dst = srcImg.clone();

    cv::Vec3b cwhite = cv::Vec3b::all(255);
    cv::Vec3b cblack = cv::Vec3b::all(0);

    cv::Mat src_ycrcb, src_hsv;
    // OpenCV scales the YCrCb components, so that they
    // cover the whole value range of [0,255], so there's
    // no need to scale the values:
    cv::cvtColor(srcImg, src_ycrcb, CV_BGR2YCrCb);
    // OpenCV scales the Hue Channel to [0,180] for
    // 8bit images, so make sure we are operating on
    // the full spectrum from [0,360] by using floating
    // point precision:
    srcImg.convertTo(src_hsv, CV_32FC3);
    cv::cvtColor(src_hsv, src_hsv, CV_BGR2HSV);
    // Now scale the values between [0,255]:
    cv::normalize(src_hsv, src_hsv, 0.0, 255.0, cv::NORM_MINMAX, CV_32FC3);

    for(int i = 0; i < srcImg.rows; i++) {
        for(int j = 0; j < srcImg.cols; j++) {

            cv::Vec3b pix_bgr = srcImg.ptr<cv::Vec3b>(i)[j];
            int B = pix_bgr.val[0];
            int G = pix_bgr.val[1];
            int R = pix_bgr.val[2];
            // apply rgb rule
            bool a = R1(R,G,B);

            cv::Vec3b pix_ycrcb = src_ycrcb.ptr<cv::Vec3b>(i)[j];
            int Y = pix_ycrcb.val[0];
            int Cr = pix_ycrcb.val[1];
            int Cb = pix_ycrcb.val[2];
            // apply ycrcb rule
            bool b = R2(Y,Cr,Cb);

            cv::Vec3f pix_hsv = src_hsv.ptr<cv::Vec3f>(i)[j];
            float H = pix_hsv.val[0];
            float S = pix_hsv.val[1];
            float V = pix_hsv.val[2];
            // apply hsv rule
            bool c = R3(H,S,V);

            if(!(a&&b&&c))
                dst.ptr<cv::Vec3b>(i)[j] = cblack;
        }
    }
    return dst;
}

bool SkinDetector::R1(int R, int G, int B) {
    bool e1 = (R>95) && (G>40) && (B>20) &&
            ((cv::max(R,cv::max(G,B)) - cv::min(R, cv::min(G,B)))>15) &&
            (abs(R-G)>15) && (R>G) && (R>B);
    bool e2 = (R>220) && (G>210) && (B>170) &&
            (abs(R-G)<=15) && (R>B) && (G>B);
    return (e1||e2);
}

bool SkinDetector::R2(float Y, float Cr, float Cb) {
    bool e3 = Cr <= 1.5862*Cb+20;
    bool e4 = Cr >= 0.3448*Cb+76.2069;
    bool e5 = Cr >= -4.5652*Cb+234.5652;
    bool e6 = Cr <= -1.15*Cb+301.75;
    bool e7 = Cr <= -2.2857*Cb+432.85;
    return e3 && e4 && e5 && e6 && e7;
}

bool SkinDetector::R3(float H, float S, float V) {
    return (H<25) || (H > 230);
}
