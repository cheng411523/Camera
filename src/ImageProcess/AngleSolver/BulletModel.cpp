#include <cmath>
#include <stdio.h>

#include "Init.hpp"

GimbalContrl::GimbalContrl()
{

}

void GimbalContrl::Init()// float x,float y,float z,float pitch,float yaw, float init_v, float init_k
{

    offset_.x = 0.0;
    offset_.y = 8;
    offset_.z = 11;
    offset_pitch_ = atan2(offset_.y,offset_.z);
    offset_yaw_ = atan2(offset_.x,offset_.z);
    init_v_ = 22;
    init_k_ = 0.026;
}

//air friction is considered
float GimbalContrl::BulletModel(float x, float v, float angle) //x:m,v:m/s,angle:rad
{
  float t, y;
  t = (float)((exp(init_k_ * x) - 1) / (init_k_ * v * cos(angle)));
  y = (float)(v * sin(angle) * t - GRAVITY * t * t / 2);
  return y;
}

//x:distance , y: height
float GimbalContrl::GetPitch(float x, float y, float v)
{
  float y_temp, y_actual, dy;
  float a;
  y_temp = y;
  // by iteration
  for (int i = 0; i < 20; i++)
  {
    a = (float) atan2(y_temp, x);
    y_actual = BulletModel(x, v, a);
    dy = y - y_actual;
    y_temp = y_temp + dy;

    if (fabsf(dy) < 0.001)
    {
      break;
    }
    //printf("iteration num %d: angle %f,temp target y:%f,err of y:%f\n",i+1,a*180/3.1415926535,yTemp,dy);
  }
  return a;
}

void GimbalContrl::Transform(cv::Point3f &postion, float &pitch, float &yaw)
{
  pitch = -(float)GetPitch((postion.z + offset_.z) / 1000, -(postion.y + offset_.y) / 1000, init_v_) + (float)(offset_pitch_ * 3.1415926535 / 180);
  //yaw positive direction :anticlockwise
  yaw = -(float)(atan2(postion.x + offset_.x, postion.z + offset_.z)) ;
}

