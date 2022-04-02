cmake_minimum_required(VERSION 2.8)
project(DIPDemoQt) # Your project name

set(CMAKE_CXX_STANDARD 11) # This is equal to QMAKE_CXX_FLAGS += -std=c++0x

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)
# Instruct CMake to run uic automatically when needed.
set(CMAKE_AUTOUIC ON)

# This will find the Qt5 files. You will need a QT5_DIR env variable
find_package(Qt5Widgets REQUIRED) # Equivalent of QT += widgets

find_package(OpenCV 3.0 QUIET)
if(NOT OpenCV_FOUND)
   find_package(OpenCV 2.4.3 QUIET)
   if(NOT OpenCV_FOUND)
      message(FATAL_ERROR "OpenCV > 2.4.3 not found.")
   endif()
endif()
include_directories(${OpenCV_INCLUDE_DIRS})

#set(SOURCES main.cpp mainwindow.cpp testitemlistmodel.cpp)
#set(HEADERS mainwindow.h testclass.h testitemlistmodel.h)
#set(UI mainwindow.ui)

list(APPEND SOURCES main.cpp                                        
    mainwindow.cpp                                                  
    ImageFileOpt/ImageFileOpt.cpp                                   
    ImageProcess/CVImgProc.cpp                                      
    SubWindow/SelChannelDlg.cpp                                     
    SubWindow/SelFlipTypeDlg.cpp                                    
    SubWindow/SelColorReduceDivDlg.cpp                              
    SubWindow/SelThreshDlg.cpp                                      
    ImageProcess/SkinDetector.cpp)

list(APPEND HEADERS mainwindow.h                                    
    ImageFileOpt/ImageFileOpt.h                                     
    ImageProcess/CVImgProc.h                                        
    SubWindow/SelChannelDlg.h                                       
    SubWindow/SelFlipTypeDlg.h                                      
    SubWindow/SelColorReduceDivDlg.h                                
    SubWindow/SelThreshDlg.h                                        
    ImageProcess/SkinDetector.h)

list(APPEND FORMS mainwindow.ui                                     
    SubWindow/SelChannelDlg.ui                                      
    SubWindow/SelFlipTypeDlg.ui                                     
    SubWindow/SelColorReduceDivDlg.ui                               
    SubWindow/SelThreshDlg.ui)

qt5_add_resources(QRC_FILES dipdemo.qrc)

add_executable(DIPDemoQt ${SOURCES} ${HEADERS} ${FORMS} ${QRC_FILES})
target_link_libraries(DIPDemoQt Qt5::Widgets ${OpenCV_LIBS})
