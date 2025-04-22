#include "tray_icon.h"
#include <QApplication>
#include <QMainWindow>
#include <QWindow>

TrayIcon::TrayIcon(QObject *parent):
  QObject(parent)
{
  trayIcon_ = new QSystemTrayIcon(this);
  trayIcon_->setIcon(QIcon("C:/Users/Dmitr/Documents/File-Mover/File-Mover/images/icon.png"));

  menu_ = new QMenu();
  QAction* restoreAction = menu_->addAction("Restore");
  QAction* quitAction = menu_->addAction("Quit");
  connect(quitAction, &QAction::triggered, this, &TrayIcon::quitApplication);

  connect(restoreAction, &QAction::triggered, this, &TrayIcon::activated);

  trayIcon_->setContextMenu(menu_);

  connect(trayIcon_, &QSystemTrayIcon::activated, this, [this](QSystemTrayIcon::ActivationReason reason)
  {
    if (reason == QSystemTrayIcon::DoubleClick)
      {
        emit activated();
      }
  });

  connect(trayIcon_, &QSystemTrayIcon::messageClicked, this, &TrayIcon::messageClicked);
}

void TrayIcon::show()
{
  trayIcon_->show();
}

void TrayIcon::hide()
{
  trayIcon_->hide();
}

void TrayIcon::showMessage(const QString &title, const QString &message)
{
  trayIcon_->showMessage(title, message);
}

void TrayIcon::minimizeToTray()
{
  QWindow* window = nullptr;
  foreach (QWindow* w, QGuiApplication::topLevelWindows())
  {
    if (w->isVisible())
    {
      window = w;
      break;
    }
  }

  if (window)
  {
    window->hide();
  }
  trayIcon_->show();
}

void TrayIcon::quitApplication()
{
  trayIcon_->hide();
  QApplication::quit();
}
