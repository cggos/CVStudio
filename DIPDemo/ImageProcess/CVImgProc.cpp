#include "CVImgProc.h"

CVImgProc::CVImgProc()
{

}

QImage CVImgProc::CVMat2QImg(const cv::Mat &matImage)
{
    cv::Mat image;
    //image.create(rows,cols,channels);

    QImage qImg;//老是出问题，待解决？？？？？？？？？？？？
    if(matImage.type() == CV_8UC3)
    {
        cv::cvtColor(matImage,image,CV_BGR2RGB);
        qImg = QImage((const unsigned char*)(image.data),
                      image.cols,image.rows,
                      image.cols*image.channels(),
                      QImage::Format_RGB888);
    }
//    if(matImage.type() == CV_8UC1)// 8-bits unsigned, NO. OF CHANNELS = 1
//    {
//        qImg = QImage(image.cols,
//                      image.rows,
//                      QImage::Format_Indexed8);
//        // Set the color table (used to translate colour indexes to qRgb values)
//        qImg.setColorCount(256);
//        for(int i = 0; i < 256; i++)
//        {
//            qImg.setColor(i, qRgb(i, i, i));
//        }
//        // Copy input image
//        uchar *pSrc = image.data;
//        for(int row = 0; row < image.rows; row ++)
//        {
//            uchar *pDest = qImg.scanLine(row);
//            memcpy(pDest, pSrc, image.cols);
//            pSrc += image.step;
//        }
//    }
    return qImg;
}

cv::Mat CVImgProc::ReadImage(const QString &pathImg)
{
    cv::Mat img;
    img = cv::imread(pathImg.toLocal8Bit().data());
    if(img.data)
    {
        return img;
    }
    else
    {
        return img;
    }

}

int CVImgProc::SaveImage(const cv::Mat &matImage, const QString &pathImg)
{
    if(matImage.empty())
    {
        return -1;
    }
    else
    {
        cv::imwrite(pathImg.toLocal8Bit().data(),matImage);
        return 0;
    }
}

cv::Mat CVImgProc::CvtToGrayImg(const cv::Mat &imgSrc)
{
    //转换为灰度图
    cv::Mat imgGray;
    imgGray.create(imgSrc.rows,imgSrc.cols,CV_8U);
    if(imgSrc.channels()==3)
    {
        cv::cvtColor(imgSrc,imgGray,CV_BGR2GRAY);
    }
    else if(imgSrc.channels()==1)
    {
        imgGray = imgSrc;
    }
    return  imgGray;
}

cv::Mat CVImgProc::GetHistgramImg(const cv::Mat &imgSrc, int indexChannel)
{
    int channels[1]={0};
    channels[0] = indexChannel;//使用通道号
    int histSize[1]={256};//项的数量
    float hranges[2]={0.0,255.0};//像素的最小和最大值
    const float *ranges[1];
    ranges[0]=hranges;
    cv::MatND hist;//计算图像直方图
    cv::calcHist(&imgSrc,1,channels,cv::Mat(),hist,1,histSize,ranges);

    double maxVal=0;
    double minVal=0;
    cv::minMaxLoc(hist,&minVal,&maxVal,0,0);

    int W_HistImg = histSize[0]*4;
    int H_HistImg = histSize[0]*3;
    cv::Mat imgHist(H_HistImg,W_HistImg,CV_8UC3,cv::Scalar::all(255));
    int hpt = static_cast<int>(0.9*H_HistImg);//设置最高点
    int xUnitLen = static_cast<int>(W_HistImg/histSize[0]);//X轴单位长度
    int xPt=0;
    //每个条目都绘制一条垂直线
    for(int n=0;n<histSize[0];n++)
    {
        float binVal = hist.at<float>(n);
        int intensity = static_cast<int>(binVal*hpt/maxVal);
        cv::line(imgHist,
                 cv::Point(xPt,H_HistImg),
                 cv::Point(xPt,H_HistImg-intensity),
                 cv::Scalar(0,255,0));//cv::Scalar::all(0)
        //画x轴刻度
        if(n%16 == 0)
        {
            cv::rectangle(imgHist,
                          cv::Point(xPt,H_HistImg),
                          cv::Point(xPt+5,H_HistImg-5),
                          cv::Scalar(0,0,255));
        }
        xPt += xUnitLen;
    }
    return imgHist;
}

cv::Mat CVImgProc::EqualizeImgHist(const cv::Mat &imgSrcGray)
{
    cv::Mat imgHistEqua;
    cv::equalizeHist(imgSrcGray,imgHistEqua);
    return imgHistEqua;
}
