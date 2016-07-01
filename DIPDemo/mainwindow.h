#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "./ImageFileOpt/ImageFileOpt.h"

#include <QMainWindow>
#include <QMessageBox>
#include <QWidget>
#include <QGridLayout>
#include <QLabel>

#include <QResizeEvent>



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
    void DisplayImage(cv::Mat matImage,int SrcOrDst);
    cv::Mat CvtToGrayImg(cv::Mat matImage);

private slots:
    void slotOpenImgSrc();//Open Source Image
    void slotSaveImgSrc();//Save Source Image
    void slotSaveImgDst();//Save Destination Image
    void slotSwapImg();//Swap the Source Image and Destination Image

    void slotGrayImg();//image gray processing
    void slotHistogram();//generate image of gray image histogram
    void slotHistEqualize();//equalize the histogram of image

private:
    void resizeEvent(QResizeEvent *);

private:
    ImageFileOpt optImgFile;

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

    QMenu *menuPointOperate;
    QAction *actionGray;
    QAction *actionHist;
    QAction *actionHistEqualize;

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
};

#endif // MAINWINDOW_H
