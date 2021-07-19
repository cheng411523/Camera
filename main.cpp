#include "Init.hpp"

pthread_t ImagePro,Camera,Serial,ImageProVideo,Carmonitor;
sem_t emptysend,senddata,emptyimage,image;

int main()
{
    sem_init(&emptyimage, 0, 1);
    sem_init(&image, 0, 0);
    sem_init(&emptysend, 0, 1);
    sem_init(&senddata, 0, 0);


#if CAPTURE
#if THREAD_WAY1

      Multithreading process;

      std::thread Camera(&Multithreading::DahengCamera,process);
      std::thread ImagePro(&Multithreading::ImageProcess,process);
      std::thread Serial(&Multithreading::Serial_Process,process);
      std::thread Carmonitor(&Multithreading::CarMonitor,process);

      Camera.join();
      ImagePro.join();
      Serial.join();
      Carmonitor.join();

#endif
#if THREAD_WAY2

        pthread_create(&ImagePro,NULL,ImageProcess,NULL);
        pthread_create(&Camera,NULL,DahengCamera,NULL);
        pthread_create(&Serial,NULL,Serial_Process,NULL);
        pthread_create(&Carmonitor,NULL,CarMonitor,NULL);

        pthread_join(ImagePro,NULL);
        pthread_join(Camera,NULL);
        pthread_join(Serial,NULL);
        pthread_join(Carmonitor,NULL);

#endif
#endif

#if VIDEO
#if THREAD_WAY1

    std::thread ImageProVideo(&Multithreading::ImageProcessVideo,process);
    ImageProVideo.join();

#endif
#if THREAD_WAY2

    pthread_create(&ImageProVideo,NULL,ImageProcessVideo,NULL);
    pthread_join(ImageProVideo,NULL);

#endif
#endif

    while(1);
    return 1;
}

