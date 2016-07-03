#ifndef IMAGEFILEOPT_H
#define IMAGEFILEOPT_H

#include <QObject>
#include <QFileDialog>
#include <QFileInfo>

#include "../ImageProcess/CVImgProc.h"

class ImageFileOpt : public QWidget
{
    Q_OBJECT
public:
    explicit ImageFileOpt(QWidget *parent = 0);

public:
    int OpenImage(QFileInfo &infoImgFile);
    int SaveImage(cv::Mat image);

private:
    CVImgProc procCVImg;

signals:

public slots:
};

#endif // IMAGEFILEOPT_H
