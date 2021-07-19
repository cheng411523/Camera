#ifndef PARAMETER_H
#define PARAMETER_H

#include "./include/ImageProcess/AngleSolver/AngleSolver.h"
#include "opencv.hpp"
#include "iostream"

using namespace cv;
using namespace std;

typedef struct
{
    string camera_path;
}ArmorParam;

typedef struct
{
    int fd;
    int time;
    int w_s;
    Mat srcimg;
    light_color color;
    string camera_path;

    int KERNEL_DILATE;
    int KERNEL_ERODE;
    int THREAHSH_RGR2GRAY;
    int THREAHSH_SUBIMAGE;
    int AREA_FAN_UP;
    int AREA_FAN_DOWN;
    int RATIO_FAN_UP;
    int RATIO_FAN_DOWN;
    int RATIO_ARMOR_AREA_UP;
    int RATIO_ARMOR_AREA_DOWN;
    int RATIO_ARMOR_SIZE_UP;
    int RATIO_ARMOR_SIZE_DOWN;
    float RATIO_RECT_SIZE;
    float RATIO_RECT_AREA;
}EnergyParam;

typedef struct
{

}ClassParam;
#endif
