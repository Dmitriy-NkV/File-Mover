#ifndef TRAY_ICON_H
#define TRAY_ICON_H

#include <QObject>
#include <QSystemTrayIcon>
#include <QMenu>

class TrayIcon: public QObject
{
  Q_OBJECT
public:
  explicit TrayIcon(QObject* parent = nullptr);

  Q_INVOKABLE void show();
  Q_INVOKABLE void hide();
  Q_INVOKABLE void showMessage(const QString& title, const QString& message);
  Q_INVOKABLE void minimizeToTray();
  Q_INVOKABLE void quitApplication();

signals:
  void activated();
  void messageClicked();

private:
  QSystemTrayIcon* trayIcon_;
  QMenu* menu_;
};

#endif // TRAY_ICON_H
