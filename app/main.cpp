#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QApplication>
#include <QIcon>
#include "core/file_mover_wrapper.h"
#include "core/tray_icon.h"

int main(int argc, char *argv[])
{
  QApplication app(argc, argv);
  app.setWindowIcon(QIcon(":/images/icon.png"));

  qmlRegisterType<TrayIcon>("TrayIcon", 1, 0, "TrayIcon");

  QQmlApplicationEngine engine;

  FileMoverWrapper wrapper;
  engine.rootContext()->setContextProperty("fileMover", &wrapper);
  engine.load(":/qml/Main.qml");

  return app.exec();
}
