#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "gpiocore.h"
#include "gpiolistmodel.h"
#include <QThread>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    GPIOListModel *gpioListModel = new GPIOListModel(&app);
    qmlRegisterSingletonInstance("com.dima.GPIOListModel", 1, 0, "GPIOListModel", gpioListModel);

    GPIOCore *gpioCore = new GPIOCore();
    QThread *threadGpioCore = new QThread;
    QObject::connect(threadGpioCore, &QThread::started, gpioCore, &GPIOCore::startReadInputs);
    gpioCore->moveToThread(threadGpioCore);
    threadGpioCore->start();

    QObject::connect(gpioListModel, &GPIOListModel::configureGPIO, gpioCore, &GPIOCore::configureGPIO);
    QObject::connect(gpioListModel, &GPIOListModel::setGPIOout, gpioCore, &GPIOCore::setGPIOout);

    gpioListModel->initialConfiguration();

    const QUrl url(u"qrc:/RaspberryPiGPIO/Main.qml"_qs);
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreationFailed,
        &app, []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
