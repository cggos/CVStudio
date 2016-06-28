#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QWidget>
#include <QGridLayout>
#include <QLabel>

#include <QResizeEvent>

#include <opencv2/opencv.hpp>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

private:
    void CreateActions();
    void CreateMenus();
    void InitMainWindow();

private:
    void DisplayImage(cv::Mat matImage,QLabel *labelImage,QLabel *labelImageInfos);

private slots:
    void slotOpenOriginImg();//Open Source Image

    void slotGrayImg();//image gray processing

private:
    void resizeEvent(QResizeEvent *event);

private:
    cv::Mat imgSrc;
    cv::Mat imgDst;

private:
    QMenu *menuFile;
    QAction *actionOpenImg;

    QMenu *menuPointOperate;
    QAction *actionGray;

    QWidget *widgetMain;
    QGridLayout *layoutGrid;
    QLabel *labelSrcImgTitle;
    QLabel *labelDstImgTitle;
    QLabel *labelSrcImg;
    QLabel *labelDstImg;
    QLabel *labelSrcImgInfos;
    QLabel *labelDstImgInfos;
};

#endif // MAINWINDOW_H
