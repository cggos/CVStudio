#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>

#include <opencv2/opencv.hpp>

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

private slots:
    void slotOpenOriginImg();

private:
    QAction *actionOpenImg;
    QMenu *menuFile;
};

#endif // MAINWINDOW_H
