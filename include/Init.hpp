#ifndef WATCHER_HPP
#define WATCHER_HPP

#define VIDEO 0
#define CAPTURE !VIDEO

#define THREAD_WAY1 1
#define THREAD_WAY2 !THREAD_WAY1


#include "opencv.hpp"
#include <memory.h>
#include <stdio.h>
#include <sys/time.h>
#include <semaphore.h>
#include "ctime"
#include "iostream"

#include "./ImageProcess/AngleSolver/AngleSolver.h"

#include"./ImageProcess/ArmorFind/ArmorFind.h"

#include"./ImageProcess/AngleSolver/BulletModel.h"

#include"./ImageProcess/Classifier/Classifier.h"

#include"./MultiThreading/MultiThreading.h"

#include"./DaHengCapture/DaHengCapture.h"

#include"./SerialPort/SerialPort.h"

#include"./Parameter/Parameter.hpp"

#include"./include/Debug.h"

using namespace cv;
using namespace std;

extern cv::Mat srcimg;
extern cv::Mat srcimg0;

extern pthread_t ImagePro,Camera,Serial,ImageProVideo,Carmonitor;;

//信号量
extern sem_t emptysend;
extern sem_t senddata;
extern sem_t emptyimage;
extern sem_t image;

extern ArmorParam armorParam;

extern bool Camera_state;
extern bool Grab_state;
extern bool Size_state;
extern bool serial_state;



#endif
