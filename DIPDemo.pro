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
        mainwindow.cpp \
    ImageFileOpt/ImageFileOpt.cpp \
    ImageProcess/CVImgProc.cpp \
    SubWindow/SelChannelDlg.cpp \
    SubWindow/SelFlipTypeDlg.cpp \
    SubWindow/SelColorReduceDivDlg.cpp \
    SubWindow/SelThreshDlg.cpp \
    ImageProcess/SkinDetector.cpp

HEADERS  += mainwindow.h \
    ImageFileOpt/ImageFileOpt.h \
    ImageProcess/CVImgProc.h \
    SubWindow/SelChannelDlg.h \
    SubWindow/SelFlipTypeDlg.h \
    SubWindow/SelColorReduceDivDlg.h \
    SubWindow/SelThreshDlg.h \
    ImageProcess/SkinDetector.h

FORMS    += mainwindow.ui \
    SubWindow/SelChannelDlg.ui \
    SubWindow/SelFlipTypeDlg.ui \
    SubWindow/SelColorReduceDivDlg.ui \
    SubWindow/SelThreshDlg.ui

#CONFIG  += C++11
QMAKE_CXXFLAGS += -std=c++0x

win32 {

OpenCV_RootDir = D:\OpenCV249\

INCLUDEPATH += $$OpenCV_RootDir\build\include\

LIBS += $$OpenCV_RootDir\build_qt5\lib\libopencv_calib3d249.dll.a\
  $$OpenCV_RootDir\build_qt5\lib\libopencv_contrib249.dll.a\
  $$OpenCV_RootDir\build_qt5\lib\libopencv_core249.dll.a\
  $$OpenCV_RootDir\build_qt5\lib\libopencv_features2d249.dll.a\
  $$OpenCV_RootDir\build_qt5\lib\libopencv_flann249.dll.a\
  $$OpenCV_RootDir\build_qt5\lib\libopencv_gpu249.dll.a\
  $$OpenCV_RootDir\build_qt5\lib\libopencv_highgui249.dll.a\
  $$OpenCV_RootDir\build_qt5\lib\libopencv_imgproc249.dll.a\
  $$OpenCV_RootDir\build_qt5\lib\libopencv_legacy249.dll.a\
  $$OpenCV_RootDir\build_qt5\lib\libopencv_ml249.dll.a\
  $$OpenCV_RootDir\build_qt5\lib\libopencv_objdetect249.dll.a\
  $$OpenCV_RootDir\build_qt5\lib\libopencv_video249.dll.a
}

unix {
INCLUDEPATH += /usr/local/include/

LIBS += /usr/local/lib/libopencv_core.so\
/usr/local/lib/libopencv_highgui.so\
/usr/local/lib/libopencv_imgcodecs.so\
/usr/local/lib/libopencv_imgproc.so\
/usr/local/lib/libopencv_ml.so\
/usr/local/lib/libopencv_video.so\
/usr/local/lib/libopencv_videoio.so
}



RESOURCES += \
    dipdemo.qrc

DESTDIR = ../Output

#message($$OpenCV_RootDir)

DISTFILES +=
