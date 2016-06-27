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
    widgetMain = new QWidget();
    this->setCentralWidget(widgetMain);

    labelSrcImg = new QLabel(tr("Source Image"));
    labelDstImg = new QLabel(tr("Destination Image"));
    labelSrcImg->setFrameShape(QFrame::Box);
    labelSrcImg->setAlignment(Qt::AlignCenter);
    labelDstImg->setFrameShape(QFrame::Box);
    labelDstImg->setAlignment(Qt::AlignCenter);

    layoutGrid = new QGridLayout(this);
    layoutGrid->addWidget(labelSrcImg,0,0);
    layoutGrid->addWidget(labelDstImg,0,1);
    layoutGrid->setColumnStretch(0,1);
    layoutGrid->setColumnStretch(1,1);

    widgetMain->setLayout(layoutGrid);
}

void MainWindow::slotOpenOriginImg()
{
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
    cv::Mat matImg = cv::imread(pathListOriImg.at(0).toLocal8Bit().data());
    if(matImg.data)
    {
//        cv::namedWindow("Original Image");
//        cv::imshow("Original Image",matImg);

        cv::cvtColor(matImg,matImg,CV_BGR2RGB);
        QImage qImg = QImage((const unsigned char*)(matImg.data),
                             matImg.cols,matImg.rows,
                             matImg.cols*matImg.channels(),
                             QImage::Format_RGB888);
        labelSrcImg->setPixmap(QPixmap::fromImage(qImg));
        labelSrcImg->resize(labelSrcImg->pixmap()->size());
    }
    else
    {
        QMessageBox::warning(this,tr("Open Image Error"),tr("Image Error"),
                             QMessageBox::Yes);
        return;
    }
}

MainWindow::~MainWindow()
{
    delete ui;

    delete actionOpenImg;
    delete menuFile;

    delete labelSrcImg;
    delete labelDstImg;

    delete layoutGrid;
    delete widgetMain;
}
