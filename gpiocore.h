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
    void configureGPIO(int position, int mode); // 0 - input, 1 - output
    void setGPIOout(int position, bool state);
    void startReadInputs();

private:
    volatile unsigned* m_gpio = nullptr;
};

#endif // GPIOCORE_H
