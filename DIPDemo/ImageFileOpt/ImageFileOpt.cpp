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
    QString filePath = QFileDialog
            ::getSaveFileName(this,
                              tr("保存图像"),
                              ".",
                              tr("Image Files(*.png *.jpg *.jpeg *.bmp)"));
    if (!filePath.isNull())
    {
        return procCVImg.SaveImage(image,filePath);
    }
    else
    {
        //点的是取消
        return 1;
    }
}

bool ImageFileOpt::LoadQssFile(const QString &pathQSS, QApplication *qApplication)
{
    //加载CSS样式表文件并应用相应样式
    QFile qssFile(pathQSS);
    if(qssFile.exists())
    {
        qssFile.open(QFile::ReadOnly);
        if(qssFile.isOpen())
        {
            QString qss = QLatin1String(qssFile.readAll());
            qApplication->setStyleSheet(qss);
            qssFile.close();
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        QMessageBox::warning(NULL,"Qss文件错误",pathQSS+"找不到！");
        return false;
    }
}
