#include "Init.hpp"
Debug_Data dbug_data;
bool serial_state=0;

HostComputerData send_data;
HostComputerData RobotInfo;
GroundChassisData MainControlInfo;

unsigned char rdata[255];
unsigned char Sdata[255];
static double serialtimer,timerlast;

//VisionData information;
void Uart::TransformTarPos_armor(int &fd,const HostComputerData &data)
{
    Sdata[0] = 0xA5;
    Sdata[1] = data.Pitch.c[0];
    Sdata[2] = data.Pitch.c[1];
    Sdata[3] = data.Pitch.c[2];
    Sdata[4] = data.Pitch.c[3];
    Sdata[5] = data.Yaw.c[0];
    Sdata[6] = data.Yaw.c[1];
    Sdata[7] = data.Yaw.c[2];
    Sdata[8] = data.Yaw.c[3];
    Sdata[9] = data.distance.c[0];
    Sdata[10] = data.distance.c[1];
    Sdata[11] = data.distance.c[2];
    Sdata[12] = data.distance.c[3];
    Sdata[13] = data.y.c[0];
    Sdata[14] = data.y.c[1];
    Sdata[15] = data.y.c[2];
    Sdata[16] = data.y.c[3];
    Sdata[17] = data.z.c[0];
    Sdata[18] = data.z.c[1];
    Sdata[19] = data.z.c[2];
    Sdata[20] = data.z.c[3];
    Sdata[21] = 0x5A;

    write(fd,Sdata,22);

    printf("angle Yaw =%f\n",RobotInfo.Yaw.f);
    printf("angle Pitch =%f\n",RobotInfo.Pitch.f);
    printf("\n");
}

void Uart::TransformTarPos(int &fd,const HostComputerData &data)
{
    Sdata[0] = 0xA5;
    Sdata[1] = data.Pitch.c[0];
    Sdata[2] = data.Pitch.c[1];
    Sdata[3] = data.Pitch.c[2];
    Sdata[4] = data.Pitch.c[3];
    Sdata[5] = data.Yaw.c[0];
    Sdata[6] = data.Yaw.c[1];
    Sdata[7] = data.Yaw.c[2];
    Sdata[8] = data.Yaw.c[3];
    Sdata[9] = data.distance.c[0];
    Sdata[10] = data.distance.c[1];
    Sdata[11] = data.distance.c[2];
    Sdata[12] = data.distance.c[3];
    Sdata[13] = data.y.c[0];
    Sdata[14] = data.y.c[1];
    Sdata[15] = data.y.c[2];
    Sdata[16] = data.y.c[3];
    Sdata[17] = data.z.c[0];
    Sdata[18] = data.z.c[1];
    Sdata[19] = data.z.c[2];
    Sdata[20] = data.z.c[3];
    Sdata[21] = 0x5A;

    write(fd,Sdata,22);

    printf("angle Yaw =%f\n",RobotInfo.Yaw.f);
    printf("angle Pitch =%f\n",RobotInfo.Pitch.f);
    printf("\n");
}

// 0xA5 | mode | level | 0x5A |
void Uart::GetMode(int &fd,GroundChassisData &data)
{
    int bytes;
    ioctl(fd, FIONREAD, &bytes);
//    std::cout << "bytes:" << bytes <<std::endl;
    if(bytes == 0) return;
    bytes = read(fd,rdata,7);
//    std::cout << "4:" << (int)rdata[4] << std::endl;
//    std::cout << "5:" << (int)rdata[5] << std::endl;
//    std::cout << "6:" << (int)rdata[6] << std::endl;
//    std::cout << "7:" << (int)rdata[7] << std::endl;
//    std::cout << "mode:" << (int)rdata[1] <<std::endl;
    if(rdata[0] == 0x5a && rdata[6] == 0xa5)//&& Verify_CRC8_Check_Sum(rdata,6)
    {
        data.mode  = (int)rdata[1];
        data.level = (int)rdata[2];
        data.color = (int)rdata[3];
        data.close = (int)rdata[4];
        data.speed = (int)rdata[5];
//        data.pitch_relative.c[1] = rdata[4];
//        data.pitch_relative.c[2] = rdata[5];
//        data.pitch_relative.c[3] = rdata[6];
//        std::cout << "mode:" << data.mode << std::endl;
//        std::cout << "level:" << data.level << std::endl;
//    else
//    {
//        std::cout << "get data is wrong!" << std::endl;
//    }
//        std::cout << "0:" << (int)rdata[0] << std::endl;
//        std::cout << "1:" << (int)rdata[1] << std::endl;
//        std::cout << "2:" << (int)rdata[2] << std::endl;
//        std::cout << "3:" << (int)rdata[3] << std::endl;
    }
    ioctl(fd, FIONREAD, &bytes);
    if(bytes>0)
    {
        read(fd,rdata,bytes);
    }
}


Uart::Uart(int speed)
{

}
/**
*@brief 设置串口通信速率
*@param fd 类型 int 打开串口的文件句柄
*@param speed 类型 int 串口速度
*@return void
*/
static int speed_arr[] = { B921600, B115200, B38400, B19200, B9600, B4800, B2400, B1200, B300,
                    B38400, B19200, B9600, B4800, B2400, B1200, B300, };
static int name_arr[] =  { 921600, 115200, 38400, 19200, 9600, 4800, 2400, 1200, 300, 38400,
                    19200, 9600, 4800, 2400, 1200, 300, };
void Uart::set_speed(int fd, int speed)
{
    int i;
    int status;
    struct termios Opt;
    tcgetattr(fd, &Opt);
    for ( i= 0; i < sizeof(speed_arr) / sizeof(int); i++)
    {
        if (speed == name_arr[i])
        {
            tcflush(fd, TCIOFLUSH);
            cfsetispeed(&Opt, speed_arr[i]);
            cfsetospeed(&Opt, speed_arr[i]);
            status = tcsetattr(fd, TCSANOW, &Opt);//
            if (status != 0)
            {
                perror("tcsetattr fd1");
                return;
            }
            tcflush(fd,TCIOFLUSH);
        }
    }
}

/**
*@brief 设置串口数据位，停止位和效验位
*@param fd 类型 int 打开的串口文件句柄
*@param databits 类型 int 数据位 取值 为 7 或者8
*@param stopbits 类型 int 停止位 取值为 1 或者2
*@param parity 类型 int 效验类型 取值为N,E,O,S
*/
int Uart::set_Parity(int fd,int databits,int stopbits,int parity)
{
    struct termios options;

    if ( tcgetattr( fd,&options) != 0)
    {
       perror("SetupSerial 1");
       return(FALSE);
    }

    options.c_cflag &= ~CSIZE;
    switch (databits) /*设置数据位数*/
    {
        case 7:
        options.c_cflag |= CS7;
        break;
        case 8:
        options.c_cflag |= CS8;
        break;
        default:
        fprintf(stderr,"Unsupported data sizen"); return (FALSE);
    }

    switch (parity)
    {
        case 'N':
        {
        options.c_cflag &= ~PARENB; /* Clear parity enable */
        options.c_iflag &= ~INPCK;  /* Enable parity checking */
        }
        break;

        case 'O':
        {
        options.c_cflag |= (PARODD | PARENB); /* 设置为奇效验*/
        options.c_iflag |= INPCK; /* Disnable parity checking */
        }
        break;

        case 'E':
        {
        options.c_cflag |= PARENB; /* Enable parity */
        options.c_cflag &= ~PARODD; /* 转换为偶效验*/
        options.c_iflag |= INPCK; /* Disnable parity checking */
        }
        break;

        case 'S': /*as no parity*/
        {
        options.c_cflag &= ~PARENB;
        options.c_cflag &= ~CSTOPB;
        }
        break;

        default:
        {fprintf(stderr,"Unsupported parityn");
        return (FALSE);}
    }
/* 设置停止位*/
    switch (stopbits)
    {
        case 1:
        options.c_cflag &= ~CSTOPB;
        break;
        case 2:
        options.c_cflag |= CSTOPB;
        break;
        default:
        fprintf(stderr,"Unsupported stop bitsn");
        return (FALSE);
    }
    /* Set input parity option */
    if (parity != 'n')
    options.c_iflag |= INPCK;

    options.c_cc[VTIME] = 150; /* 设置超时15 seconds*/
    options.c_cc[VMIN] = 0; /* Update the options and do it NOW */

    options.c_cflag &= ~HUPCL;
    options.c_iflag &= ~INPCK;
    options.c_iflag |= IGNBRK;
    options.c_iflag &= ~ICRNL;
    options.c_iflag &= ~IXON;
    options.c_lflag &= IEXTEN;
    options.c_lflag &= ~ECHOK;
    options.c_lflag &= ~ECHOCTL;
    options.c_lflag &= ~ECHOKE;
    options.c_lflag &= ~ONLCR;
    options.c_oflag =  ~ICANON;

    tcflush(fd,TCIFLUSH);
    if (tcsetattr(fd,TCSANOW,&options) != 0)
    {
        perror("SetupSerial 3");
        return (FALSE);
    }
    return(TRUE);
}

int Uart::send_data(int fd, unsigned char *buffer, int Length)
{
//    char buffer[1024];
    int nByte=0;
    nByte = write(fd, buffer ,Length);//实际写入的长度
    if(nByte == Length)
    {
        return (nByte);
    }
    else
    {
        tcflush(fd, TCOFLUSH);
        return -1;
    }
}

int Uart::received_data(int fd, unsigned char *buffer, int datalen, int baudrate)
{
//    char buff[1024];
    int readlen, fs_sel;
    fd_set  fs_read;
    struct timeval tv_timeout;

    FD_ZERO(&fs_read);
    FD_SET(fd, &fs_read);

    tv_timeout.tv_sec = TIMEOUT_SEC(datalen, baudrate);//!!!check check check
    tv_timeout.tv_usec = TIMEOUT_USEC;

    fs_sel = select(fd+1, &fs_read, NULL, NULL, &tv_timeout);
    if(fs_sel)
    {
        readlen = read(fd, buffer, datalen);
        return(readlen);
    }
    else
    {
        return(-1);
    }
    return (readlen);
}

void Uart::close_serial(int fd)
{
    close(fd);
}

int Uart::Init_serial(int &fdcom,int baud_speed)
{
   // fdcom = open("/dev/my_serial0", O_RDWR | O_NONBLOCK);//O_NOCTTY | O_NDELAY
    fdcom = open("/dev/ttyUSB0", O_RDWR | O_NONBLOCK);//O_NOCTTY | O_NDELAY
    if(fdcom == -1 )
    {
        fdcom = open("/dev/ttyUSB1", O_RDWR | O_NONBLOCK);//
    }
    printf("fdcom:%d\n",fdcom);
    if(-1 == fdcom)
    {
        /* 不能打开串口*/
        perror(" Can''t Open Serial Port\n");
        return -1;
    }
    else perror(" Open Serial Port success\n");
    set_speed(fdcom,baud_speed);
    if(set_Parity(fdcom,8,1,'N') ==  FALSE)
    {
        printf("Set Parity Errorn\n");
        exit(0);
    }
//    set_disp_mode(fdcom,0);
    return 0;
}

int set_disp_mode(int fd,int option)
{
   int err;
   struct termios term;
   if(tcgetattr(fd,&term)==-1)
   {
     perror("Cannot get the attribution of the terminal");
     return 1;
   }
   if(option)
        term.c_lflag|=ECHOFLAGS;
   else
        term.c_lflag &=~ECHOFLAGS;
   err=tcsetattr(fd,TCSAFLUSH,&term);
   if(err==-1 && err==EINTR)
   {
        perror("Cannot set the attribution of the terminal");
        return 1;
   }
   return 0;
}
