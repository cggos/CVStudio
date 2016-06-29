#include "ImageFileOpt.h"

ImageFileOpt::ImageFileOpt(QWidget *parent) : QWidget(parent)
{

}

int ImageFileOpt::OpenImage(QFileInfo &infoImgFile)
{
//    QString pathOriImg =
//            QFileDialog::getOpenFileName(this,tr("Open Image"),".",
//                                         tr("Image Files(*.png *.jpg *.jpeg *.bmp)"));

    QString selfilter = tr("Image Files(*.png *.jpg *.jpeg *.bmp);;All Files(*)");
    QFileDialog *dlgFile = new QFileDialog(this,"File Dialog",".",selfilter);
    dlgFile->setFilter(QDir::Files);
    dlgFile->setViewMode(QFileDialog::List);
    dlgFile->setFileMode(QFileDialog::ExistingFile);
    if(dlgFile->exec() == QDialog::Accepted)
    {
        QStringList pathListImg;
        pathListImg = dlgFile->selectedFiles();
        infoImgFile = QFileInfo(pathListImg.at(0));
        return 0;
    }
    else
    {
        return 1;
    }
}

int ImageFileOpt::SaveImage(cv::Mat image)
{
    if(image.empty())
    {
        return -1;
    }
    QString filePath = QFileDialog
            ::getSaveFileName(this,
                              tr("保存图像"),
                              ".",
                              tr("Image Files(*.png *.jpg *.jpeg *.bmp)"));
    if (!filePath.isNull())
    {
        cv::imwrite(filePath.toLocal8Bit().data(),image);
        return 0;
    }
    else
    {
        //点的是取消
        return 1;
    }
}
