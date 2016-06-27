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
//    if(pathOriImg.isEmpty())
//    {
//        QMessageBox::warning(this,tr("Open Image Error"),
//                             tr(""),
//                             QMessageBox::Yes);
//        return;
//    }
    cv::Mat matImg = cv::imread(pathListOriImg.at(0).toLocal8Bit().data());
    if(matImg.data)
    {
        cv::namedWindow("Original Image");
        cv::imshow("Original Image",matImg);
    }

}

MainWindow::~MainWindow()
{
    delete ui;

    delete actionOpenImg;
    delete menuFile;
}
