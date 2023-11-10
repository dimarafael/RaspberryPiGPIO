#include "gpioitem.h"

GPIOitem::GPIOitem(QObject *parent)
    : QObject{parent}
{

}

QString GPIOitem::name() const
{
    return m_name;
}

void GPIOitem::setName(const QString &newName)
{
    if (m_name == newName)
        return;
    m_name = newName;
    emit nameChanged();
}

int GPIOitem::GPIOnumber() const
{
    return m_GPIOnumber;
}

void GPIOitem::setGPIOnumber(int newGPIOnumber)
{
    if (m_GPIOnumber == newGPIOnumber)
        return;
    m_GPIOnumber = newGPIOnumber;
    emit GPIOnumberChanged();
}

bool GPIOitem::state() const
{
    return m_state;
}

void GPIOitem::setState(bool newState)
{
    if (m_state == newState)
        return;
    m_state = newState;
    emit stateChanged();
}

int GPIOitem::mode() const
{
    return m_mode;
}

void GPIOitem::setMode(int newMode)
{
    if (m_mode == newMode)
        return;
    m_mode = newMode;
    emit modeChanged();
}
