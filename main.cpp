#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "gpiolistmodel.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    GPIOListModel *gpioListModel = new GPIOListModel(&app);
    qmlRegisterSingletonInstance("com.dima.GPIOListModel", 1, 0, "GPIOListModel", gpioListModel);

    QObject::connect(gpioListModel,&GPIOListModel::setGPIOout,&app, [](int GPIOnumber, bool state){
        qDebug() << "GPIOnumber =" << GPIOnumber << " state =" << state;
    });

    const QUrl url(u"qrc:/RaspberryPiGPIO/Main.qml"_qs);
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreationFailed,
        &app, []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
