#ifndef SERIAL_H
#define SERIAL_H

//串口相关的头文件
#include <stdio.h>      /*标准输入输出定义*/
#include <stdlib.h>     /*标准函数库定义*/
#include <unistd.h>     /*Unix 标准函数定义*/
#include <fcntl.h>      /*文件控制定义*/
#include <termios.h>    /*PPSIX 终端控制定义*/
#include <errno.h>      /*错误号定义*/
#include "stdint.h"
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>

#define BAUDRATE        115200
#define UART_DEVICE     "/dev/ttyUSB0"

#define ECHOFLAGS (ECHO | ECHOE | ECHOK | ECHONL)

//Used when calling a serial port
#define FALSE -1
#define TRUE 0
#define TIMEOUT_SEC(buflen,baud) (buflen*20/baud+2)  //接收超时
#define TIMEOUT_USEC 0

typedef union
{
    float f;
    unsigned char c[4];
}float2uchar;

typedef struct
{
    float2uchar Yaw;
    float2uchar Pitch;
    float2uchar time;
    float2uchar distance;
    float2uchar y;
    float2uchar z;
}HostComputerData;
typedef struct
{
    float2uchar X_VALUE;
    float2uchar Y_VALUE;
    float2uchar Z_VALUE;
    unsigned char MODE;
    float2uchar P_Time;
}Debug_Data;
typedef struct
{
    unsigned char mode; //0 auto_attack_red 1 auto_attack_blue
    unsigned char color;
    unsigned char level;
    unsigned char close;
    unsigned char speed;
}GroundChassisData;

extern HostComputerData RobotInfo;
extern GroundChassisData MainControlInfo;

class Uart
{
public:
    Uart(int speed = 9600);
    int Init_serial(int &fdcom,int baud_speed);
    void set_speed(int fd, int speed);
    int set_Parity(int fd,int databits,int stopbits,int parity);
    int send_data(int fd, unsigned char *buffer, int Length);
    int received_data(int fd, unsigned char *buffer, int datalen, int baudrate);
    void close_serial(int fd);
    void GetMode(int &fd,GroundChassisData &data);
    void TransformTarPos(int &fd,const HostComputerData &data);
    void TransformTarPos_armor(int &fd,const HostComputerData &data);
private:
    int fd;
    int speed;
};

#endif


