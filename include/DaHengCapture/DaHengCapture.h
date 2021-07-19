#ifndef DAHENGCAPTURE_H
#define DAHENGCAPTURE_H
/*********************************************************************************
  *Copyright(C),2018-2020,??????Horizon??All Rights Reserved
  *FileName:  DaHengCamera.h
  *Author:  ???
  *Version: 1.3.1.200513_RC
  *Date:  2020.05.13
  *Description: ????MER_139_210U3C SDK
  *Function List:
     1.DaHengCamera ??????
     2.StartDevice    ????
     3.SetStreamOn ????
     4.SetResolution  ?????
     5.SetExposureTime   ?????
     6.SetGAIN   ????
     7.Set_BALANCE_AUTO  ???????
     8.GetMat   ??Mat??
**********************************************************************************/
#include<include/DaHengCapture/DxImageProc.h>
#include<include/DaHengCapture/GxIAPI.h>
#include<iostream>
#include <opencv2/core/core.hpp>

using namespace std;
using namespace cv;

//大恒双目相机
class DaHengCamera{
private:
    //枚举操作成功与失败信息
    GX_STATUS status = GX_STATUS_SUCCESS;
    GX_STATUS status0 = GX_STATUS_SUCCESS;
    //
    GX_OPEN_PARAM openParam;
    GX_OPEN_PARAM openParam0;
    //相机设备
    GX_DEV_HANDLE hDevice;
    GX_DEV_HANDLE hDevice0;
    //定 义 GXDQBuf 的 传 入 参 数,包含图片内存，大小等信息
    PGX_FRAME_BUFFER pFrameBuffer;
    PGX_FRAME_BUFFER pFrameBuffer0;


public:
    //构造函数，初始化库
    DaHengCamera();
    //打开设备
    int StartDevice(int serial_number);
    int StartDevice0(int serial_number);
    //设置触发类型
    bool SetTrigger(uint8_t i);
    bool SetTrigger0(uint8_t i);
    //使设备开始采集
    bool SetStreamOn();
    //设置分辨率，支持1:1(最大1280*1024),1:2,2:1,2:2(最小640*512),默认1:1
    bool SetResolution(int width_scale = 1 , int height_scale = 1);
    bool SetResolution0(int width_scale = 1 , int height_scale = 1);
    //手动设置曝光值,单位us,正常大小应在2000至8000
    bool SetExposureTime(int ExposureTime);
    bool SetExposureTime0(int ExposureTime);
    //设置曝光增益
    bool SetGAIN(int value,int ExpGain);
    bool SetGAIN0(int value,int ExpGain);
    //设置自动白平衡,0表示关闭，1表示开启
    bool Set_BALANCE_AUTO(int value);
    bool Set_BALANCE_AUTO0(int value);
    //手动设置白平衡,value表示平衡通道，value_number表示具体值,0、1、2对应B、G、R，value_number范围为10到80,10表示正常
    bool Set_BALANCE(int value , int value_number);
    bool Set_BALANCE0(int value, int value_number);
    //采集图像
    bool GetMat(Mat & Src);
    bool GetMat0(Mat & Src0);
    //读取相机时间戳
    double Get_TIMESTAMP();
    //析构函数释放资源
    ~DaHengCamera();

};

#endif // DAHENGCAMERA_H
