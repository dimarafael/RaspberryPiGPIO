#ifndef GPIOCORE_H
#define GPIOCORE_H

#include <QObject>

class GPIOCore : public QObject
{
    Q_OBJECT
public:
    explicit GPIOCore(QObject *parent = nullptr);

signals:

public slots:
//    void configureGPIO(int position, int mode);
//    void setGPIOout(int position, bool state);
//    void startReadInputs();

private:
    volatile unsigned* m_gpio;
};

#endif // GPIOCORE_H
