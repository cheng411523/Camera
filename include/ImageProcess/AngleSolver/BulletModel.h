/****************************************************************************
 *  Copyright (C) 2019 RoboMaster.
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program. If not, see <http://www.gnu.org/licenses/>.
 ***************************************************************************/
#ifndef ROBORTS_DETECTION_GIMBAL_CONTROL_H
#define ROBORTS_DETECTION_GIMBAL_CONTROL_H
#include <iostream>
#include <opencv4/opencv2/opencv.hpp>

using namespace cv;

const double PI = 3.1415926535;
const float GRAVITY = 9.78;

class GimbalContrl
{
 public:
    GimbalContrl();
    float BulletModel(float x,float v,float angle);
    float GetPitch(float x,float y,float v);
 public:
    void Init();//float x,float y,float z,float pitch,float yaw, float init_v, float init_k
    void Transform(cv::Point3f &postion,float &pitch,float &yaw);

 private:
    //! Translation unit: cm
    cv::Point3f offset_;
    //! Rotation matrix unit: degree
    float offset_pitch_;
    float offset_yaw_;
    //! Initial value
    float init_v_;
    float init_k_;

};

#endif //ROBORTS_DETECTION_GIMBAL_CONTROL_H
