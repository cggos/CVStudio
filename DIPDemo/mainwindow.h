#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>

#include <opencv2/opencv.hpp>
#include <QWidget>
#include <QGridLayout>
#include <QLabel>

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

private slots:
    void slotOpenOriginImg();

private:
    QAction *actionOpenImg;
    QMenu *menuFile;

    QWidget *widgetMain;
    QGridLayout *layoutGrid;
    QLabel *labelSrcImg;
    QLabel *labelDstImg;
};

#endif // MAINWINDOW_H
