#ifndef FILE_MOVER_WRAPPER_H
#define FILE_MOVER_WRAPPER_H

#include <QObject>
#include <QFileSystemWatcher>
#include "rules_model.h"
#include "core/file_mover.hpp"

class FileMoverWrapper: public QObject
{
  Q_OBJECT

  Q_PROPERTY(QStringList dirs READ getDirs NOTIFY dirsChanged)
  Q_PROPERTY(RulesModel* rulesModel READ rulesModel CONSTANT)
  Q_PROPERTY(bool isWatching READ isWatching NOTIFY watchingStateChanged)

public:
  explicit FileMoverWrapper(QObject *parent = nullptr);

  Q_INVOKABLE void addDir(const QString& dirName);

  Q_INVOKABLE void addRuleToDir(const QString& dirName, const QString& targetDir, const QStringList& ext, const QStringList& exceptions);
  Q_INVOKABLE void addRuleToDir(const QString& dirName, const QString& targetDir, int durationDays, bool isGreaterThanDuration, const QStringList& exceptions);
  Q_INVOKABLE void addRuleToDir(const QString& dirName, const QString& targetDir, const QString& name, bool isCheckRegister, const QStringList& exceptions);
  Q_INVOKABLE void addRuleToDir(const QString& dirName, const QString& targetDir, const QStringList& exceptions);
  Q_INVOKABLE void addRuleToDir(const QString& dirName, const QStringList& ext, const QStringList& exceptions);
  Q_INVOKABLE void addRuleToDir(const QString& dirName, int durationDays, bool isGreaterThanDuration, const QStringList& exceptions);

  Q_INVOKABLE void deleteRuleFromDir(const QString& dirName, int id);
  Q_INVOKABLE void deleteDir(const QString& dirName);
  Q_INVOKABLE void clear();

  Q_INVOKABLE void importConfig(const QString& config);
  Q_INVOKABLE void saveConfig(const QString& config) const;

  Q_INVOKABLE void startWatching();
  Q_INVOKABLE void stopWatching();

  Q_INVOKABLE bool isWatching() const;
  Q_INVOKABLE QStringList getDirs() const;
  Q_INVOKABLE RulesModel* rulesModel() const;

signals:
  void dirsChanged();
  void watchingStateChanged();

private:
  bool isWatching_ = false;
  FileMover fileMover_;
  RulesModel* rulesModel_;
  QFileSystemWatcher fileWatcher_;
};

#endif // FILE_MOVER_WRAPPER_H
