TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

DEFINES += QT_NO_WARNING_OUTPUT\
           QT_NO_DEBUG_OUTPUT

INCLUDEPATH += /usr/local/include/
INCLUDEPATH += /usr/local/include/opencv4/
INCLUDEPATH += /usr/local/include/opencv4/opencv2/
INCLUDEPATH += /usr/local/include/eigen3/
INCLUDEPATH += /home/cheng/code/Radar1/include/

#LIBS += -I/usr/local/include/opencv4/opencv -I/usr/local/include/opencv4 -L/usr/local/lib -lopencv_gapi -lopencv_stitching -lopencv_aruco -lopencv_bgsegm -lopencv_bioinspired -lopencv_ccalib -lopencv_dnn_objdetect -lopencv_dpm -lopencv_face -lopencv_freetype -lopencv_fuzzy -lopencv_hfs -lopencv_img_hash -lopencv_line_descriptor -lopencv_quality -lopencv_reg -lopencv_rgbd -lopencv_saliency -lopencv_stereo -lopencv_structured_light -lopencv_phase_unwrapping -lopencv_superres -lopencv_optflow -lopencv_surface_matching -lopencv_tracking -lopencv_datasets -lopencv_text -lopencv_dnn -lopencv_plot -lopencv_videostab -lopencv_video -lopencv_xfeatures2d -lopencv_shape -lopencv_ml -lopencv_ximgproc -lopencv_xobjdetect -lopencv_objdetect -lopencv_calib3d -lopencv_features2d -lopencv_highgui -lopencv_videoio -lopencv_imgcodecs -lopencv_flann -lopencv_xphoto -lopencv_photo -lopencv_imgproc -lopencv_core

LIBS += /usr/local/lib/*.so
LIBS += -lgxiapi \


LIBS += /home/cheng/Galaxy_camera/bin/resource/gxplugins/libPluginObject.so
#LIBS +=/home/cheng/Galaxy_camera/bin/libaudio.so.2\
#       /home/cheng/Galaxy_camera/bin/libaudio.so.2.4\
#       /home/cheng/Galaxy_camera/bin/libpng12.so.0\
#       /home/cheng/Galaxy_camera/bin/libpng12.so.0\
#       /home/cheng/Galaxy_camera/bin/libQtCore.so.4\
#       /home/cheng/Galaxy_camera/bin/libQtCore.so.4.8\
#       /home/cheng/Galaxy_camera/bin/libQtCore.so.4.8.6\
#       /home/cheng/Galaxy_camera/bin/libQtDBus.so.4\
#       /home/cheng/Galaxy_camera/bin/libQtDBus.so.4.8\
#       /home/cheng/Galaxy_camera/bin/libQtDBus.so.4.8.6\
#       /home/cheng/Galaxy_camera/bin/libQtGui.so.4\
#       /home/cheng/Galaxy_camera/bin/libQtGui.so.4.8\
#       /home/cheng/Galaxy_camera/bin/libQtGui.so.4.8.6\
#       /home/cheng/Galaxy_camera/bin/libQtNetwork.so.4\
#       /home/cheng/Galaxy_camera/bin/libQtNetwork.so.4.8\
#       /home/cheng/Galaxy_camera/bin/libQtNetwork.so.4.8.6\
#       /home/cheng/Galaxy_camera/bin/libQtXml.so.4\
#       /home/cheng/Galaxy_camera/bin/libQtXml.so.4.8\
#       /home/cheng/Galaxy_camera/bin/libQtXml.so.4.8.6\
#       /home/cheng/Galaxy_camera/bin/libz.so\
#       /home/cheng/Galaxy_camera/bin/libz.so.1\
#       /home/cheng/Galaxy_camera/bin/libz.so.1.2.11



SOURCES += main.cpp \
    src/DaHengCapture/DaHengCapture.cpp \
    src/ImageProcess/AngleSolver/AngleSolver.cpp \
    src/ImageProcess/AngleSolver/BulletModel.cpp \
    src/ImageProcess/AngleSolver/KalmanFilter.cpp \
    src/ImageProcess/ArmorFind/ArmorFind.cpp \
    src/ImageProcess/Classifiier/Classifier.cpp \
    src/MultiThreading/Multithreading.cpp \
    src/SerialPort/SerialPort.cpp \

HEADERS += \
    include/DaHengCapture/DaHengCapture.h \
    include/DaHengCapture/DxImageProc.h \
    include/DaHengCapture/GxIAPI.h \
    include/Debug.h \
    include/ImageProcess/AngleSolver/AngleSolver.h \
    include/ImageProcess/AngleSolver/BulletModel.h \
    include/ImageProcess/AngleSolver/KalmanFilter.h \
    include/ImageProcess/ArmorFind/ArmorFind.h \
    include/ImageProcess/Classifier/Classifier.h \
    include/MultiThreading/MultiThreading.h \
    include/SerialPort/SerialPort.h \
    include/Init.hpp\


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/lib/release/ -lpthread-2.27
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/lib/debug/ -lpthread-2.27
else:unix: LIBS += -L$$PWD/lib/ -lpthread-2.27

INCLUDEPATH += $$PWD/include
DEPENDPATH += $$PWD/include



win32:CONFIG(release, debug|release): LIBS += -L$$PWD/lib/release/ -lMVSDK
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/lib/debug/ -lMVSDK
else:unix: LIBS += -L$$PWD/lib/ -lMVSDK

INCLUDEPATH += $$PWD/include
DEPENDPATH += $$PWD/include



win32:CONFIG(release, debug|release): LIBS += -L$$PWD/lib/release/ -lImageConvert
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/lib/debug/ -lImageConvert
else:unix: LIBS += -L$$PWD/lib/ -lImageConvert

INCLUDEPATH += $$PWD/include
DEPENDPATH += $$PWD/include
