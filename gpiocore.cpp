#include "gpiocore.h"
#include <fcntl.h>
#include <sys/mman.h>
#include<unistd.h>
#include <QDebug>
#include <QCoreApplication>

GPIOCore::GPIOCore(QObject *parent)
    : QObject{parent}
{
    int gpioFd = open("/dev/gpiomem", O_RDWR, O_SYNC);
    if(gpioFd < 0){
        qDebug() << "Can not open /dev/gpiomem";
//        QCoreApplication::exit(-1);
    } else {
        void* gpioMap = mmap(
            NULL,
            4*1024,
            PROT_READ|PROT_WRITE,
            MAP_SHARED,
            gpioFd,
            0
            );

        close(gpioFd);

        if(gpioMap == MAP_FAILED){
            qDebug() << "MAP_FAILED";
        } else {
            m_gpio = (volatile unsigned*)gpioMap;
        }

    }

}
