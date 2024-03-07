#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QDebug>
#include <QDirIterator>
#include "socketcommu.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;
    const QUrl url(u"qrc:/qt/qml/airplane_controller/srcs/Main.qml"_qs);
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.load(url);

    // QDirIterator it(":", QDirIterator::Subdirectories);
    // while (it.hasNext()) {
    //     qDebug() << it.next();
    // }
    auto s = new SocketCommu(nullptr,&engine);

    auto r = app.exec();

    delete s;
    return  r;
}
