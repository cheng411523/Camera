#pragma once
#ifndef MULTITHREADING_H
#define MULTITHREADING_H
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>
#include "fstream"
#include "time.h"
#include "vector"
#include "utility"
#include <cstdlib>
#include <thread>
#include "opencv.hpp"
#pragma comment(lib,"pthreadVC2.lib")

using namespace cv;
using namespace std;

class Multithreading{
public:
    int GXExpTime=4000;
    int GXGain=0;
    int fd_serial0=0;
    std::uint8_t fd_debug=0;

    Multithreading();
    void ImageProcess();
    void ImageProcessVideo();
    void DahengCamera();
    void CarMonitor();
    void Serial_Process();
    ~Multithreading();
private:
};

//void *ImageProcess(void *arg);
//void *ImageProcessVideo(void *arg);
//void *DahengCamera(void *arg);
//void *CarMonitor(void *arg);
//void *Serial_Process(void *arg);

#endif

