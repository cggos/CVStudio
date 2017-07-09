#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "./ImageFileOpt/ImageFileOpt.h"
#include "./ImageProcess/SkinDetector.h"
#include "./SubWindow/SelChannelDlg.h"
#include "./SubWindow/SelFlipTypeDlg.h"
#include "./SubWindow/SelColorReduceDivDlg.h"
#include "./SubWindow/SelThreshDlg.h"

#include <QMainWindow>
#include <QMessageBox>
#include <QWidget>
#include <QGridLayout>
#include <QLabel>

#include <QResizeEvent>

#include <QTimer>

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
    void InitStatusBar();
    void BeautifyUI();

private:
    bool CheckSrcImage();
    void DisplayImage(cv::Mat matImage,int SrcOrDst);

private slots:
    void slotOpenImgSrc();//Open Source Image
    void slotSaveImgSrc();//Save Source Image
    void slotSaveImgDst();//Save Destination Image
    void slotSwapImg();//Swap the Source Image and Destination Image

    void slotOpenCamera();
    void slotCloseCamera();

    void slotGrayImg();//image gray processing
    void slotHistogram();//generate image of gray image histogram
    void slotHistEqualize();//equalize the histogram of image
    void slotThresholdImg();//
    void slotColorReduce();//reduce the image color number
    void slotSaltImage();

    void slotFlipImg();//flip image:

    void slotFilter2D();

    void slotDetectSkin();//detect skin color

private:
    void resizeEvent(QResizeEvent *);

private:
    ImageFileOpt optImgFile;
    CVImgProc procCVImg;

private:
    cv::Mat imgSrc;
    cv::Mat imgDst;

    QString nameSrcImg;
    QString pathSrcImg;
    QString  dirSrcImg;

    QString nameDstImg;
    QString pathDstImg;
    QString  dirDstImg;


private:
    QMenu *menuFile;
    QAction *actionOpenImg;
    QAction *actionSaveImgSrc;
    QAction *actionSaveImgDst;
    QAction *actionSwapImg;

    QMenu *menuDevices;
    QAction *actionOpenCamera;
    QAction *actionCloseCamera;

    QMenu *menuPointOperate;
    QAction *actionGray;
    QAction *actionHist;
    QAction *actionHistEqualize;
    QAction *actionThresholdImg;
    QAction *actionColorReduce;
    QAction *actionSaltImage;

    QMenu *menuTransformImg;
    QAction *actionFlip;

    QMenu *menuFilterImg;
    QAction *actionFilter2D;

    QMenu *menuDetect;
    QAction *actionSkinDetect;

    QWidget *widgetMain;
    QGridLayout *layoutGrid;

    QLabel *labelSrcImgTitle;
    QLabel *labelSrcImg;
    QLabel *labelSrcImgInfos;
    QLabel *labelSrcImgPath;

    QLabel *labelDstImgTitle;
    QLabel *labelDstImg;
    QLabel *labelDstImgInfos;

private:
    const QString strPathQssFile;
    const QColor clrBKApp;

private:
    cv::VideoCapture captureVideo;
    QTimer *timerCaptureVideo;
    cv::Mat (*processImg)(const cv::Mat &imgSrc);

private slots:
    void CaptureFrame();
};

#endif // MAINWINDOW_H
