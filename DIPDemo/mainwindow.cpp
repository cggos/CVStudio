#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    CreateActions();
    CreateMenus();

    InitMainWindow();
}

void MainWindow::CreateActions()
{
    actionOpenImg = new QAction(tr("&Open Image"),this);
    connect(actionOpenImg,SIGNAL(triggered(bool)),this,SLOT(slotOpenOriginImg()));
}

void MainWindow::CreateMenus()
{
    menuFile = ui->menuBar->addMenu(tr("&File"));
    menuFile->addAction(actionOpenImg);
}

void MainWindow::InitMainWindow()
{
    //原图像和目标图像显示区域定义
    labelSrcImg = new QLabel(tr("Source Image"));
    labelDstImg = new QLabel(tr("Destination Image"));
    labelSrcImg->setFrameShape(QFrame::Box);
    labelSrcImg->setAlignment(Qt::AlignCenter);
    labelDstImg->setFrameShape(QFrame::Box);
    labelDstImg->setAlignment(Qt::AlignCenter);
    //原图像和目标图像信息显示区域定义
    labelSrcImgInfos = new QLabel(tr("Source Image Infos"));
    labelDstImgInfos = new QLabel(tr("Destination Image Infos"));
    labelSrcImgInfos->setFrameShape(QFrame::Box);
    labelSrcImgInfos->setAlignment(Qt::AlignCenter);
    labelDstImgInfos->setFrameShape(QFrame::Box);
    labelDstImgInfos->setAlignment(Qt::AlignCenter);

    //主窗口控件布局
    layoutGrid = new QGridLayout(this);
    layoutGrid->addWidget(labelSrcImg,0,0,9,1);
    layoutGrid->addWidget(labelDstImg,0,1,9,1);
    layoutGrid->addWidget(labelSrcImgInfos,9,0,1,1);
    layoutGrid->addWidget(labelDstImgInfos,9,1,1,1);
    layoutGrid->setColumnStretch(0,1);
    layoutGrid->setColumnStretch(1,1);

    widgetMain = new QWidget();
    this->setCentralWidget(widgetMain);
    widgetMain->setLayout(layoutGrid);
}

void MainWindow::slotOpenOriginImg()
{
    //打开源图像
//    QString pathOriImg =
//            QFileDialog::getOpenFileName(this,tr("Open Image"),".",
//                                         tr("Image Files(*.png *.jpg *.jpeg *.bmp)"));
    QStringList pathListOriImg;
    QString selfilter = tr("Image Files(*.png *.jpg *.jpeg *.bmp);;All Files(*)");
    QFileDialog *dlgFile = new QFileDialog(this,"File Dialog",".",selfilter);
    dlgFile->setFilter(QDir::Files);
    dlgFile->setViewMode(QFileDialog::List);
    dlgFile->setFileMode(QFileDialog::ExistingFile);
    if(dlgFile->exec() == QDialog::Accepted)
    {
        pathListOriImg = dlgFile->selectedFiles();
    }
    else
    {
        return;
    }
    //读取并显示源图像
    imgSrc = cv::imread(pathListOriImg.at(0).toLocal8Bit().data());
    if(imgSrc.data)
    {
        DisplayImage(imgSrc,labelSrcImg,labelSrcImgInfos);
    }
    else
    {
        QMessageBox::warning(this,tr("Open Image Error"),tr("Image Error"),
                             QMessageBox::Yes);
        return;
    }
}

void MainWindow::DisplayImage(cv::Mat matImage, QLabel *labelImage, QLabel *labelImageInfos)
{
    cv::Mat image = matImage;
    int W_LabelImg = labelImage->width();
    int H_LabelImg = labelImage->height();
    int W_Img = image.cols;
    int H_Img = image.rows;
    int N_Channels = image.channels();

    //显示图像信息
    labelImageInfos->setText("源图像\r\n宽度："
                        + QString::number(W_Img)
                        + "，高度："
                        + QString::number(H_Img)
                        + "，通道数："
                        + QString::number(N_Channels));

    //根据显示图像的label大小改变图像尺寸
    if(W_Img>W_LabelImg && H_Img<=H_LabelImg)
    {
        cv::resize(image,image,
                   cv::Size(W_LabelImg,H_Img/((float)W_Img/W_LabelImg)));
    }
    else if(W_Img<=W_LabelImg && H_Img>H_LabelImg)
    {
        cv::resize(image,image,
                   cv::Size(W_Img/((float)H_Img/H_LabelImg),H_LabelImg));
    }
    else if(W_Img>W_LabelImg && H_Img>H_LabelImg)
    {
        if(W_LabelImg>=H_LabelImg)
        {
            if(W_Img<=H_Img)
            {
                cv::resize(image,image,
                           cv::Size(W_Img/((float)H_Img/H_LabelImg),H_LabelImg));
            }
            else
            {
                if(W_Img/H_Img >= W_LabelImg/H_LabelImg)
                {
                    cv::resize(image,image,
                               cv::Size(W_LabelImg,H_Img/((float)W_Img/W_LabelImg)));
                }
                else
                {
                    cv::resize(image,image,
                               cv::Size(W_Img/((float)H_Img/H_LabelImg),H_LabelImg));
                }
            }
        }
        else
        {
            if(W_Img>=H_Img)
            {
                cv::resize(image,image,
                           cv::Size(W_LabelImg,H_Img/((float)W_Img/W_LabelImg)));
            }
            else
            {
                if(H_Img/W_Img <= H_LabelImg/W_LabelImg)
                {
                    cv::resize(image,image,
                               cv::Size(W_LabelImg,H_Img/((float)W_Img/W_LabelImg)));
                }
                else
                {
                    cv::resize(image,image,
                               cv::Size(W_Img/((float)H_Img/H_LabelImg),H_LabelImg));
                }
            }
        }
    }
    cv::cvtColor(image,image,CV_BGR2RGB);
    QImage qImg = QImage((const unsigned char*)(image.data),
                         image.cols,image.rows,
                         image.cols*image.channels(),
                         QImage::Format_RGB888);
    labelImage->setPixmap(QPixmap::fromImage(qImg));
    //labelImage->resize(labelImage->pixmap()->size());
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
//    if(imgSrc.data)
//    {
//        DisplayImage(imgSrc,labelSrcImg);
//    }
}

MainWindow::~MainWindow()
{
    delete ui;

    delete actionOpenImg;
    delete menuFile;

    delete labelSrcImg;
    delete labelDstImg;
    delete labelSrcImgInfos;
    delete labelDstImgInfos;

    delete layoutGrid;
    delete widgetMain;
}
