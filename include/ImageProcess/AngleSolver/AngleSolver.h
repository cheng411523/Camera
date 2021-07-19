#ifndef ANGLESOLVER_H
#define ANGLESOLVER_H

#define CONTROL false

#include"iostream"
#include"opencv.hpp"
#include"./include/ImageProcess/AngleSolver/BulletModel.h"

using namespace cv;
using namespace std;

enum light_color
{
    Red = 0,
    Blue = 1
};

enum armor_race
{
    SMALL = 0,
    BIG = 1,
    RUNE = 2,
    BASE = 3,
    None = 4
};

class AngleSolver : public GimbalContrl
{
public:
    AngleSolver(cv::String path,float scale_z = 0);
    int ReadCameraData(cv::String path);
    void SetCameraPoints(Point2f * points, Point2f offset = Point2f(0,0));
    void SetWorldPoints(armor_race type);
    void SolvePnP(int type = 0);
    double GetTargetDistance(bool real = false,bool scale = false);
    double CalculateAngle(float& angle_Yaw,float& angle_Pitch,int model = 1);
    void GetAngle(Point2f* points,float& angle_Yaw,float& angle_Pitch,armor_race type,int model = 1,int pnp = 0);
    void Control();

    ~AngleSolver();
private:
    Mat rot;
    Mat trans;
    Mat ReferenceMatrix;
    Mat DistortionMatrix;

private:
    double _x;
    double _y;
    double _z;
    double offset_x;
    double offset_y;
    double offset_z;
    float target_width;
    float target_height;
    float scale_z;
    float distance;

public:
    vector<Point2f>Points_in_Camera;
    vector<Point3f>Points_in_World;
};

#endif
