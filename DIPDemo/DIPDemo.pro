#-------------------------------------------------
#
# Project created by QtCreator 2016-06-26T22:45:57
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DIPDemo
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

#CONFIG  += C++11
QMAKE_CXXFLAGS += -std=c++0x

DESTDIR = ../Output

INCLUDEPATH +=   D:\OpenCV249\build\include\

LIBS += D:\OpenCV249\build_qt5\lib\libopencv_calib3d249.dll.a\
  D:\OpenCV249\build_qt5\lib\libopencv_contrib249.dll.a\
  D:\OpenCV249\build_qt5\lib\libopencv_core249.dll.a\
  D:\OpenCV249\build_qt5\lib\libopencv_features2d249.dll.a\
  D:\OpenCV249\build_qt5\lib\libopencv_flann249.dll.a\
  D:\OpenCV249\build_qt5\lib\libopencv_gpu249.dll.a\
  D:\OpenCV249\build_qt5\lib\libopencv_highgui249.dll.a\
  D:\OpenCV249\build_qt5\lib\libopencv_imgproc249.dll.a\
  D:\OpenCV249\build_qt5\lib\libopencv_legacy249.dll.a\
  D:\OpenCV249\build_qt5\lib\libopencv_ml249.dll.a\
  D:\OpenCV249\build_qt5\lib\libopencv_objdetect249.dll.a\
  D:\OpenCV249\build_qt5\lib\libopencv_video249.dll.a
