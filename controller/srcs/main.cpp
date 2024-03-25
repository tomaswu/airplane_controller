#include <QApplication>
#include <QQmlApplicationEngine>
#include <QDebug>
#include <QDirIterator>
#include <QQmlContext>

#include "control.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QQmlApplicationEngine engine;

    control c;
    engine.rootContext()->setContextProperty("con",&c);

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



    auto r = app.exec();

    return  r;
}
