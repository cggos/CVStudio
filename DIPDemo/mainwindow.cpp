#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    strPathQssFile(":/QSS/QSS/StyleSheet.qss"),
    clrBKApp(QColor(205,215,230))
{
    ui->setupUi(this);

    CreateActions();
    CreateMenus();
    ui->mainToolBar->hide();
    InitMainWindow();
    InitStatusBar();

    BeautifyUI();
}

//创建菜单项
void MainWindow::CreateActions()
{
    //“文件”
    actionOpenImg = new QAction(tr("打开图像"),this);
    connect(actionOpenImg,SIGNAL(triggered(bool)),this,SLOT(slotOpenImgSrc()));

    actionSaveImgSrc = new QAction(tr("保存原始图像..."),this);
    connect(actionSaveImgSrc,SIGNAL(triggered(bool)),this,SLOT(slotSaveImgSrc()));

    actionSaveImgDst = new QAction(tr("保存目标图像..."),this);
    connect(actionSaveImgDst,SIGNAL(triggered(bool)),this,SLOT(slotSaveImgDst()));

    actionSwapImg = new QAction(tr("原始目标图像对调"),this);
    connect(actionSwapImg,SIGNAL(triggered(bool)),this,SLOT(slotSwapImg()));

    //设备
    actionOpenCamera = new QAction(tr("打开摄像头"),this);
    connect(actionOpenCamera,SIGNAL(triggered(bool)),this,SLOT(slotOpenCamera()));

    actionCloseCamera = new QAction(tr("关闭摄像头"),this);
    connect(actionCloseCamera,SIGNAL(triggered(bool)),this,SLOT(slotCloseCamera()));

    //“点运算”
    actionGray = new QAction(tr("图像灰度化"),this);
    connect(actionGray,SIGNAL(triggered(bool)),this,SLOT(slotGrayImg()));

    actionHist = new QAction(tr("灰度直方图..."),this);
    connect(actionHist,SIGNAL(triggered(bool)),this,SLOT(slotHistogram()));

    actionHistEqualize = new QAction(tr("直方图均衡化"),this);
    connect(actionHistEqualize,SIGNAL(triggered(bool)),this,SLOT(slotHistEqualize()));

    actionThresholdImg = new QAction(tr("二值化图像..."),this);
    connect(actionThresholdImg,SIGNAL(triggered(bool)),this,SLOT(slotThresholdImg()));

    actionColorReduce = new QAction(tr("图像减色..."),this);
    connect(actionColorReduce,SIGNAL(triggered(bool)),this,SLOT(slotColorReduce()));

    actionSaltImage = new QAction(tr("椒盐噪点"),this);
    connect(actionSaltImage,SIGNAL(triggered(bool)),this,SLOT(slotSaltImage()));

    //"图像变换"
    actionFlip = new QAction(tr("图像反转..."),this);
    connect(actionFlip,SIGNAL(triggered(bool)),this,SLOT(slotFlipImg()));

    //"目标检测"
    actionSkinDetect = new QAction(tr("肤色检测"),this);
    connect(actionSkinDetect,SIGNAL(triggered(bool)),this,SLOT(slotDetectSkin()));
}

//创建菜单，添加菜单项
void MainWindow::CreateMenus()
{
    menuFile = ui->menuBar->addMenu(tr("文件"));
    menuFile->addAction(actionOpenImg);
    menuFile->addSeparator();
    menuFile->addAction(actionSaveImgSrc);
    menuFile->addAction(actionSaveImgDst);
    menuFile->addSeparator();
    menuFile->addAction(actionSwapImg);

    menuDevices = ui->menuBar->addMenu(tr("设备"));
    menuDevices->addAction(actionOpenCamera);
    menuDevices->addAction(actionCloseCamera);

    menuPointOperate = ui->menuBar->addMenu(tr("点运算"));
    menuPointOperate->addAction(actionGray);
    menuPointOperate->addSeparator();
    menuPointOperate->addAction(actionHist);
    menuPointOperate->addAction(actionHistEqualize);
    menuPointOperate->addAction(actionThresholdImg);
    menuPointOperate->addSeparator();
    menuPointOperate->addAction(actionColorReduce);
    menuPointOperate->addAction(actionSaltImage);

    menuTransformImg = ui->menuBar->addMenu(tr("图像变换"));
    menuTransformImg->addAction(actionFlip);

    menuDetect = ui->menuBar->addMenu(tr("目标检测"));
    menuDetect->addAction(actionSkinDetect);
}

//初始化主窗口布局
void MainWindow::InitMainWindow()
{
    //原图像和目标图像标题显示区域定义
    labelSrcImgTitle = new QLabel(tr("Source Image Title"));
    labelDstImgTitle = new QLabel(tr("Destination Image Title"));
    labelSrcImgTitle->setObjectName("objLabelSrcImgTitle");
    labelDstImgTitle->setObjectName("objLabelDstImgTitle");
    labelSrcImgTitle->setAlignment(Qt::AlignCenter);
    labelDstImgTitle->setAlignment(Qt::AlignCenter);
    labelSrcImgTitle->setFrameShape(QFrame::Box);
    labelDstImgTitle->setFrameShape(QFrame::Box);
    //原图像和目标图像显示区域定义
    labelSrcImg = new QLabel(tr("Source Image"));
    labelDstImg = new QLabel(tr("Destination Image"));
    labelSrcImg->setObjectName("objLabelSrcImg");
    labelDstImg->setObjectName("objLabelDstImg");
    labelSrcImg->setAlignment(Qt::AlignCenter);
    labelDstImg->setAlignment(Qt::AlignCenter);
    labelSrcImg->setFrameShape(QFrame::Box);
    labelDstImg->setFrameShape(QFrame::Box);
    //原图像和目标图像信息显示区域定义
    labelSrcImgInfos = new QLabel(tr("Source Image Infos"));
    labelDstImgInfos = new QLabel(tr("Destination Image Infos"));
    labelSrcImgInfos->setObjectName("objLabelSrcImgInfos");
    labelDstImgInfos->setObjectName("objLabelDstImgInfos");
    labelSrcImgInfos->setAlignment(Qt::AlignCenter);
    labelDstImgInfos->setAlignment(Qt::AlignCenter);
    labelSrcImgInfos->setFrameShape(QFrame::Box);
    labelDstImgInfos->setFrameShape(QFrame::Box);

    //主窗口控件布局
    layoutGrid = new QGridLayout();
    layoutGrid->addWidget(labelSrcImgTitle,0,0,1,1);
    layoutGrid->addWidget(labelDstImgTitle,0,1,1,1);
    layoutGrid->addWidget(labelSrcImg,1,0,10,1);
    layoutGrid->addWidget(labelDstImg,1,1,10,1);
    layoutGrid->addWidget(labelSrcImgInfos,11,0,1,1);
    layoutGrid->addWidget(labelDstImgInfos,11,1,1,1);
    layoutGrid->setColumnStretch(0,1);
    layoutGrid->setColumnStretch(1,1);

    widgetMain = new QWidget();
    this->setCentralWidget(widgetMain);
    widgetMain->setLayout(layoutGrid);
}

void MainWindow::InitStatusBar()
{
    labelSrcImgPath = new QLabel("Source Image Path");
    ui->statusBar->addWidget(labelSrcImgPath);
}

void MainWindow::BeautifyUI()
{
    optImgFile.LoadQssFile(strPathQssFile,qApp);

    //设置应用程序背景色
    QPalette *paletteApp=new QPalette();
    paletteApp->setColor(QPalette::Background,clrBKApp);
    this->setPalette(*paletteApp);
    delete paletteApp;
}

void MainWindow::slotOpenImgSrc()
{
    QFileInfo fileImage;
    int ret = optImgFile.OpenImage(fileImage);
    if(ret == 0)
    {
        nameSrcImg = fileImage.fileName();
        pathSrcImg = fileImage.filePath();
        dirSrcImg  = fileImage.absolutePath();

        //读取并显示源图像
        imgSrc = procCVImg.ReadImage(pathSrcImg);
        if(imgSrc.data)
        {
            DisplayImage(imgSrc,0);
        }
        else
        {
            QMessageBox::critical(this,tr("图像错误"),tr("读取图像失败！"),
                                 QMessageBox::Yes);
            return;
        }
    }
}

void MainWindow::slotSaveImgSrc()
{
    int ret = optImgFile.SaveImage(imgSrc);
    if(ret == 0)
    {
        QMessageBox::information(this,
                                 "保存成功",
                                 "保存原始图像成功",
                                 QMessageBox::Yes);
    }
    else if(ret == -1)
    {
        QMessageBox::critical(this,
                              "图像错误",
                              "原始图像不存在",
                              QMessageBox::Yes);
    }
}

void MainWindow::slotSaveImgDst()
{
    int ret = optImgFile.SaveImage(imgDst);
    if(ret == 0)
    {
        QMessageBox::information(this,
                                 "保存成功",
                                 "保存目标图像成功",
                                 QMessageBox::Yes);
    }
    else if(ret == -1)
    {
        QMessageBox::critical(this,
                              "图像错误",
                              "目标图像不存在",
                              QMessageBox::Yes);
    }
}

void MainWindow::slotSwapImg()
{
    if(imgSrc.empty() || imgDst.empty())
    {
        QMessageBox::critical(this,
                              "图像错误",
                              "原始图像或目标图像不存在！",
                              QMessageBox::Yes);
        return;
    }
    cv::Mat imgTemp = imgSrc;
    imgSrc = imgDst;
    imgDst = imgTemp;

    DisplayImage(imgSrc,0);
    DisplayImage(imgDst,1);
}

void MainWindow::slotOpenCamera()
{
    if(captureVideo.isOpened()){
        captureVideo.release();
    }

    captureVideo.open(0);

    if(captureVideo.isOpened())
    {
        timerCaptureVideo = new QTimer(this);
        timerCaptureVideo->setInterval(100);
        connect(timerCaptureVideo, SIGNAL(timeout()), this, SLOT(CaptureFrame()));

        imgSrc = cv::Mat::zeros(captureVideo.get(CV_CAP_PROP_FRAME_HEIGHT), captureVideo.get(CV_CAP_PROP_FRAME_WIDTH), CV_8UC3);

        captureVideo>>imgSrc;

        if(!imgSrc.empty())
        {
            DisplayImage(imgSrc,0);
        }

        timerCaptureVideo->start();
    }
}

void MainWindow::slotCloseCamera()
{
    if(timerCaptureVideo->isActive())
    {
        timerCaptureVideo->stop();
    }

    if(captureVideo.isOpened()){
        captureVideo.release();
    }
}

void MainWindow::CaptureFrame()
{
    captureVideo>>imgSrc;
    if(!imgSrc.empty())
    {
        DisplayImage(imgSrc,0);
        switch(typeDetect)
        {
        case DETECTOR_SKIN:
            imgDst = SkinDetector::GetSkin_RGBHCbCr(imgSrc);
            DisplayImage(imgDst,1);
            break;
        }
    }
}

void MainWindow::slotGrayImg()
{
    if(!CheckSrcImage())
        return;

    imgDst = procCVImg.CvtToGrayImg(imgSrc);
    DisplayImage(imgDst,1);
}

void MainWindow::slotHistogram()
{
    if(!CheckSrcImage())
        return;

    SelChannelDlg *dlgSelChannel = new SelChannelDlg(NULL,imgSrc.channels());
    if(dlgSelChannel->exec() == QDialog::Accepted)
    {
        imgDst = procCVImg.GetHistgramImg(imgSrc,dlgSelChannel->indexChannel);
        DisplayImage(imgDst,1);
    }
    delete dlgSelChannel;
}

void MainWindow::slotHistEqualize()
{
    if(!CheckSrcImage())
        return;
    cv::Mat imgGray = procCVImg.CvtToGrayImg(imgSrc);
    imgDst = procCVImg.EqualizeImgHist(imgGray);
    DisplayImage(imgDst,1);
}

void MainWindow::slotThresholdImg()
{
    if(!CheckSrcImage())
        return;

    SelThreshDlg dlgSelThresh;
    if(dlgSelThresh.exec() == QDialog::Accepted)
    {
        cv::Mat imgGray = procCVImg.CvtToGrayImg(imgSrc);
        imgDst = procCVImg.ThresholdImg(imgGray,dlgSelThresh.threshValue);
        DisplayImage(imgDst,1);
    }
}

void MainWindow::slotColorReduce()
{
    if(!CheckSrcImage())
        return;
    SelColorReduceDivDlg dlgColorReduce;
    dlgColorReduce.show();
    if(dlgColorReduce.exec() == QDialog::Accepted)
    {
        imgDst = procCVImg.colorReduce(imgSrc,dlgColorReduce.divColorReduce);
        DisplayImage(imgDst,1);
    }
}

void MainWindow::slotSaltImage()
{
    if(!CheckSrcImage())
        return;
    imgDst = procCVImg.SaltImage(imgSrc);
    DisplayImage(imgDst,1);
}

void MainWindow::slotFlipImg()
{
    if(!CheckSrcImage())
        return;

    SelFlipTypeDlg dlgSelFlipType;
    if(dlgSelFlipType.exec() == QDialog::Accepted)
    {
        enum FlipType{Horizon=0,Vertical,HV}typeFlip;
        typeFlip = FlipType(dlgSelFlipType.typeFlip);
        switch(typeFlip)
        {
        case Horizon:
            imgDst = procCVImg.FlipImg(imgSrc,1);
            break;
        case Vertical:
            imgDst = procCVImg.FlipImg(imgSrc,0);
            break;
        case HV:
            imgDst = procCVImg.FlipImg(imgSrc,-1);
            break;
        }
        DisplayImage(imgDst,1);
    }
}

void MainWindow::slotDetectSkin()
{
    if(!CheckSrcImage())
        return;

    typeDetect = DETECTOR_SKIN;

    imgDst = SkinDetector::GetSkin_RGBHCbCr(imgSrc);
    DisplayImage(imgDst,1);
}

bool MainWindow::CheckSrcImage()
{
    if(imgSrc.empty())
    {
        QMessageBox::critical(this,
                              "图像错误",
                              "原始图像不存在",
                              QMessageBox::Yes);
        return false;
    }
    else
    {
        return true;
    }
}

void MainWindow::DisplayImage(cv::Mat matImage,int SrcOrDst)
{
    //不能使用image=matImage，会影响matImage，进而影响ingSRC
    cv::Mat image;
    matImage.copyTo(image);//创建新的拷贝

    QLabel *labelImage;
    QLabel *labelImageInfos;

    int W_Img = image.cols;
    int H_Img = image.rows;
    int N_Channels = image.channels();

    if(SrcOrDst==0)
    {
        labelSrcImgTitle->setText("源图像");
        labelImage = labelSrcImg;
        labelImageInfos = labelSrcImgInfos;

        labelSrcImgPath->setText("原始图像路径："+pathSrcImg);
    }
    else
    {
        labelDstImgTitle->setText("目标图像");
        labelImage = labelDstImg;
        labelImageInfos = labelDstImgInfos;
    }

    int W_LabelImg = labelImage->width();
    int H_LabelImg = labelImage->height();

    //显示图像信息
    labelImageInfos->setText("宽度："
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
                if(W_Img/(float)H_Img >= W_LabelImg/(float)H_LabelImg)
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
                if(H_Img/(float)W_Img <= H_LabelImg/(float)W_LabelImg)
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
    QImage qImg;
    if(image.type() == CV_8UC3)
    {
        cv::cvtColor(image,image,CV_BGR2RGB);
        qImg = QImage((const unsigned char*)(image.data),
                      image.cols,image.rows,
                      image.cols*image.channels(),
                      QImage::Format_RGB888);
    }
    if(image.type() == CV_8UC1)// 8-bits unsigned, NO. OF CHANNELS = 1
    {
        qImg = QImage(image.cols,
                      image.rows,
                      QImage::Format_Indexed8);
        // Set the color table (used to translate colour indexes to qRgb values)
        qImg.setColorCount(256);
        for(int i = 0; i < 256; i++)
        {
            qImg.setColor(i, qRgb(i, i, i));
        }
        // Copy input image
        uchar *pSrc = image.data;
        for(int row = 0; row < image.rows; row ++)
        {
            uchar *pDest = qImg.scanLine(row);
            memcpy(pDest, pSrc, image.cols);
            pSrc += image.step;
        }
    }

    labelImage->setPixmap(QPixmap::fromImage(qImg));
    //labelImage->resize(labelImage->pixmap()->size());
}

void MainWindow::resizeEvent(QResizeEvent *)
{
}

MainWindow::~MainWindow()
{
    delete ui;

    delete menuFile;
    delete actionOpenImg;
    delete actionSaveImgSrc;
    delete actionSaveImgDst;

    delete menuPointOperate;
    delete actionGray;

    delete labelSrcImgTitle;
    delete labelSrcImg;
    delete labelSrcImgInfos;
    delete labelSrcImgPath;

    delete labelDstImgTitle;
    delete labelDstImg;
    delete labelDstImgInfos;

    delete layoutGrid;
    delete widgetMain;
}
