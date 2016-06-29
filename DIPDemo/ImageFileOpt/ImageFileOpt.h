#ifndef IMAGEFILEOPT_H
#define IMAGEFILEOPT_H

#include <QObject>
#include <QFileDialog>
#include <QFileInfo>

#include <opencv2/opencv.hpp>

class ImageFileOpt : public QWidget
{
    Q_OBJECT
public:
    explicit ImageFileOpt(QWidget *parent = 0);

public:
    int OpenImage(QFileInfo &infoImgFile);
    int SaveImage(cv::Mat image);

signals:

public slots:
};

#endif // IMAGEFILEOPT_H
