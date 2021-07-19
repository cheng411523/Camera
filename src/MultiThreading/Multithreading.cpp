#include "Init.hpp"
cv::Mat srcimg,srcimg0;

//int GXExpTime=4000;
//int GXGain=0;
//int fd_serial0=0;
//std::uint8_t fd_debug=0;

#if THREAD_WAY1
Multithreading::Multithreading(){

}
void Multithreading::DahengCamera(){

    DaHengCamera CameraTure;
    //链接设备
    CameraTure.StartDevice(2);
    CameraTure.StartDevice0(2);
    //设置分辨率
    CameraTure.SetResolution(2,2);
    CameraTure.SetResolution0(2,2);
    //设置触发类型
    CameraTure.SetTrigger(1);
    CameraTure.SetTrigger0(1);
    //控制设备开采
    CameraTure.SetStreamOn();
    //设置曝光值
    CameraTure.SetExposureTime(GXExpTime);
    CameraTure.SetExposureTime0(GXExpTime);
    //设置曝光增益
    CameraTure.SetGAIN(3,GXGain);
    CameraTure.SetGAIN0(3,GXGain);
    //关闭自动白平衡
    CameraTure.Set_BALANCE_AUTO(0);
    CameraTure.Set_BALANCE_AUTO0(0);

    while(1){

        static uint8_t num=0;

        sem_wait(&emptyimage);
        CameraTure.GetMat(srcimg);
        CameraTure.GetMat0(srcimg0);
        if(!srcimg.empty()&&!srcimg0.empty())
        {
            num++;
        }
        if(num>=10)
        {
            num=10;
            sem_post(&image);
        }
    }
}

void Multithreading::ImageProcess(){

    while(1){
        sem_wait(&image);
        if(!srcimg.empty()){
        namedWindow("srcimg",1);
        cv::imshow("srcimg",srcimg);
        cv::waitKey(100);
        sem_post(&senddata);
        }
        sem_post(&emptyimage);
    }
}

void Multithreading::CarMonitor(){

}
void Multithreading::Serial_Process(){
    Uart InfoPort;
    while(1){
         if(fd_serial0)
         {
             sem_wait(&senddata);
             InfoPort.GetMode(fd_serial0,MainControlInfo);
 //           InfoPort.receive_data(fd_serial0);
 //           InfoPort.send_data(fd_serial0,RobotInfo);
            serial_state=0;
            sem_post(&emptysend);
         }else if (fd_debug) {
             serial_state=1;
 //           InfoPort.receive_data(fd_debug);
         }else {
         serial_state=0;
         }
         usleep(1000);
     }
}
void Multithreading::ImageProcessVideo(){

}
Multithreading::~Multithreading(){

}
#endif

#if THREAD_WAY2
void *DahengCamera(void *arg){
    cv::Mat Src;
    DaHengCamera CameraTure;
    //链接设备
    CameraTure.StartDevice(1);
    //设置分辨率
    CameraTure.SetResolution(2,2);
    //控制设备开采
    CameraTure.SetStreamOn();
    //设置曝光值
    CameraTure.SetExposureTime(GXExpTime);
    //设置曝光增益
    CameraTure.SetGAIN(3,GXGain);
    //关闭自动白平衡
    CameraTure.Set_BALANCE_AUTO(0);
    while(1){
        CameraTure.GetMat(srcimg);
    }
}

void *ImageProcess(void *arg){

}

void *CarMonitor(void *arg){

}

void *Serial_Process(void *arg){

}

void *ImageProcessVideo(void *arg){

}

#endif
