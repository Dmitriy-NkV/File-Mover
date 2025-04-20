#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "file_mover_wrapper.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    FileMoverWrapper wrapper;

    QQmlApplicationEngine engine;
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);

    engine.rootContext()->setContextProperty("fileMover", &wrapper);
    engine.load("C:/Users/Dmitr/Documents/File-Mover/File-Mover/Main.qml");

    return app.exec();
}
