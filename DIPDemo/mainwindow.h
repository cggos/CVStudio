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

private:
    void DisplayImage(cv::Mat matImage,
                      QLabel *labelImageTitle,
                      int SrcOrDst,
                      QString nameImage,
                      QString dirImage,
                      QLabel *labelImage,
                      QLabel *labelImageInfos);

private slots:
    void slotOpenImgSrc();//Open Source Image
    void slotSaveImgSrc();//Save Source Image
    void slotSaveImgDst();//Save Destination Image

    void slotGrayImg();//image gray processing
    void slotHistogram();//generate image of gray image histogram

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

    QMenu *menuPointOperate;
    QAction *actionGray;
    QAction *actionHist;

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
