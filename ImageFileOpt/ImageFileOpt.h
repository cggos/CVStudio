#ifndef IMAGEFILEOPT_H
#define IMAGEFILEOPT_H

#include <QObject>
#include <QApplication>
#include <QFileDialog>
#include <QFileInfo>
#include <QMessageBox>

#include "../ImageProcess/CVImgProc.h"

class ImageFileOpt : public QWidget
{
    Q_OBJECT
public:
    explicit ImageFileOpt(QWidget *parent = 0);

public:
    int OpenImage(QFileInfo &infoImgFile);
    int SaveImage(cv::Mat image);

    bool LoadQssFile(const QString &pathQSS,QApplication* qApplication);

private:
    CVImgProc procCVImg;

signals:

public slots:
};

#endif // IMAGEFILEOPT_H
