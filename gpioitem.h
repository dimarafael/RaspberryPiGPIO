#ifndef GPIOITEM_H
#define GPIOITEM_H

#include <QObject>

class GPIOitem : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged FINAL)
    Q_PROPERTY(int GPIOnumber READ GPIOnumber WRITE setGPIOnumber NOTIFY GPIOnumberChanged FINAL)
    Q_PROPERTY(bool state READ state WRITE setState NOTIFY stateChanged FINAL)
    Q_PROPERTY(int mode READ mode WRITE setMode NOTIFY modeChanged FINAL)
public:
    explicit GPIOitem(QObject *parent = nullptr);

    QString name() const;
    void setName(const QString &newName);

    int GPIOnumber() const;
    void setGPIOnumber(int newGPIOnumber);

    bool state() const;
    void setState(bool newState);

    int mode() const;
    void setMode(int newMode);

signals:

    void nameChanged();

    void GPIOnumberChanged();

    void stateChanged();

    void modeChanged();

private:

    QString m_name = "";
    int m_GPIOnumber = -1;
    bool m_state = false;
    int m_mode = 0; // 0 - input, 1 - output
};

#endif // GPIOITEM_H
