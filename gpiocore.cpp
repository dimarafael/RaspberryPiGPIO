#include "gpiocore.h"
#include <fcntl.h>
#include <sys/mman.h>
#include <QDebug>
#include <QCoreApplication>

GPIOCore::GPIOCore(QObject *parent)
    : QObject{parent}
{
    int gpioFd = open("/dev/gpiomem", O_RDWR);
    if(gpioFd < 0){
        qDebug() << "Can not open /dev/gpiomem";
        QCoreApplication::exit(-1);
    }

    void* gpioMap = mmap(
        NULL,
        4*1024,
        0,
        0,
        gpioFd,
        0
        );
}
