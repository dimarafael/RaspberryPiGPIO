#include "gpiocore.h"
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
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

void GPIOCore::configureGPIO(int position, int mode)  // 0 - input, 1 - output
{
    qDebug() << "configureGPIO: GPIO=" << position << ", mode=" << mode;
    if (m_gpio != nullptr){
        *(m_gpio + (unsigned)(position/10)) &= ~(7<<((position%10)*3));
        if (mode == 1)
            *(m_gpio + (unsigned)(position/10)) |= (1<<((position%10)*3));
    }
}

void GPIOCore::setGPIOout(int position, bool state)
{
    qDebug() << "setGPIOout: GPIO=" << position << ", state=" << state;
    if (m_gpio != nullptr){
        if(state){ // ON
            *(m_gpio + 7) = 1 << position;
        } else {// OFF
            *(m_gpio + 10) = 1 << position;
        }
    }
}

void GPIOCore::startReadInputs()
{
    qDebug() << "startReadInputs";
}
