#include "file_mover_wrapper.h"

FileMoverWrapper::FileMoverWrapper(QObject* parent):
  QObject(parent),
  rulesModel_(new RulesModel(fileMover_, this))
{
  connect(&fileWatcher_, &QFileSystemWatcher::directoryChanged, this, [this](const QString& path)
  {
    try
    {
      fileMover_.execDir(path.toStdString());
    }
    catch(const std::exception& e)
    {
      qDebug() << e.what() << '\n';
    }
  });
}

void FileMoverWrapper::addDir(const QString& dirName)
{
  try
  {
    fileMover_.addDir(dirName.toStdString());
    emit dirsChanged();
  }
  catch(const std::exception& e)
  {
    qDebug() << e.what() << '\n';
  }
}

void FileMoverWrapper::addRuleToDir(const QString& dirName, const QString& targetDir, const QStringList& ext, const QStringList& exceptions)
{
  std::vector< std::filesystem::path > extVec;
  for (const auto& e: ext)
  {
    extVec.push_back(e.toStdString());
  }

  std::set< std::filesystem::path > exceptionsSet;
  for (const auto& ex: exceptions)
  {
    exceptionsSet.insert(ex.toStdString());
  }

  try
  {
    fileMover_.addRuleToDir(dirName.toStdString(), targetDir.toStdString(), extVec, exceptionsSet);
  }
  catch(const std::exception& e)
  {
    qDebug() << e.what() << '\n';
  }
}

void FileMoverWrapper::addRuleToDir(const QString& dirName, const QString& targetDir, int durationDays, bool isGreaterThanDuration, const QStringList& exceptions)
{
  std::set < std::filesystem::path > exceptionsSet;
  for (const auto& ex: exceptions)
  {
    exceptionsSet.insert(ex.toStdString());
  }

  auto duration = std::chrono::duration< int, std::ratio< 86400 > >(durationDays);

  try
  {
    fileMover_.addRuleToDir(dirName.toStdString(), targetDir.toStdString(), duration, isGreaterThanDuration, exceptionsSet);
  }
  catch(const std::exception& e)
  {
    qDebug() << e.what() << '\n';
  }

}

void FileMoverWrapper::addRuleToDir(const QString& dirName, const QString& targetDir, const QString& name, bool isCheckRegister,const QStringList& exceptions)
{
  std::set< std::filesystem::path > exceptionsSet;
  for (const auto& ex: exceptions)
  {
    exceptionsSet.insert(ex.toStdString());
  }

  try
  {
    fileMover_.addRuleToDir(dirName.toStdString(), targetDir.toStdString(), name.toStdString(), isCheckRegister, exceptionsSet);
  }
  catch(const std::exception& e)
  {
    qDebug() << e.what() << '\n';
  }

}

void FileMoverWrapper::addRuleToDir(const QString& dirName, const QString& targetDir, const QStringList& exceptions)
{
  std::set< std::filesystem::path > exceptionsSet;
  for (const auto& ex: exceptions)
  {
    exceptionsSet.insert(ex.toStdString());
  }

  try
  {
    fileMover_.addRuleToDir(dirName.toStdString(), targetDir.toStdString(), exceptionsSet);
  }
  catch(const std::exception& e)
  {
    qDebug() << e.what() << '\n';
  }
}

void FileMoverWrapper::addRuleToDir(const QString& dirName, const QStringList& ext, const QStringList& exceptions)
{
  std::vector< std::filesystem::path > extVec;
  for (const auto& e: ext)
  {
    extVec.push_back(e.toStdString());
  }

  std::set< std::filesystem::path > exceptionsSet;
  for (const auto& ex: exceptions)
  {
    exceptionsSet.insert(ex.toStdString());
  }

  try
  {
    fileMover_.addRuleToDir(dirName.toStdString(), extVec, exceptionsSet);
  }
  catch(const std::exception& e)
  {
    qDebug() << e.what() << '\n';
  }
}

void FileMoverWrapper::addRuleToDir(const QString& dirName, int durationDays, bool isGreaterThanDuration, const QStringList& exceptions)
{
  std::set< std::filesystem::path > exceptionsSet;
  for (const auto& ex: exceptions)
  {
    exceptionsSet.insert(ex.toStdString());
  }

  auto duration = std::chrono::duration< int, std::ratio< 86400 > >(durationDays);

  try
  {
    fileMover_.addRuleToDir(dirName.toStdString(), duration, isGreaterThanDuration, exceptionsSet);
  }
  catch(const std::exception& e)
  {
    qDebug() << e.what() << '\n';
  }
}

void FileMoverWrapper::deleteRuleFromDir(const QString& dirName, int id)
{
  try
  {
    fileMover_.deleteRuleFromDir(dirName.toStdString(), static_cast< size_t >(id));
  }
  catch(const std::exception& e)
  {
    qDebug() << e.what() << '\n';
  }
}

void FileMoverWrapper::deleteDir(const QString& dirName)
{
  try
  {
    fileMover_.deleteDir(dirName.toStdString());
    emit dirsChanged();
  }
  catch(const std::exception& e)
  {
    qDebug() << e.what() << '\n';
  }
}

Q_INVOKABLE void FileMoverWrapper::clear()
{
  auto dirs = fileMover_.getDirs();
  for (auto i = dirs.cbegin(); i != dirs.cend(); ++i)
  {
    fileMover_.deleteDir(*i);
  }
}

void FileMoverWrapper::importConfig(const QString& config)
{
  try
  {
    fileMover_.importConfig(config.toStdString());
  }
  catch(const std::exception& e)
  {
    qDebug() << e.what() << '\n';
  }
}

void FileMoverWrapper::saveConfig(const QString& config) const
{
  try
  {
    fileMover_.saveConfig(config.toStdString());
  }
  catch(const std::exception& e)
  {
    qDebug() << e.what() << '\n';
  }
}

void FileMoverWrapper::startWatching()
{
  try
  {
    if (!isWatching_ && !getDirs().empty())
    {
      fileMover_.execDirs();
      fileWatcher_.addPaths(getDirs());
      isWatching_ = true;
      emit watchingStateChanged();
    }
  }
  catch (const std::exception& e)
  {
    qDebug() << e.what() << '\n';
    stopWatching();
  }
}

void FileMoverWrapper::stopWatching()
{
  try
  {
    if (isWatching_)
    {
      fileWatcher_.removePaths(fileWatcher_.directories());
      isWatching_ = false;
      emit watchingStateChanged();
    }
  }
  catch (const std::exception& e)
  {
    qDebug() << e.what() << '\n';
  }
}

bool FileMoverWrapper::isWatching() const
{
  return isWatching_;
}

QStringList FileMoverWrapper::getDirs() const
{
  QStringList list;
  for (const auto& dir: fileMover_.getDirs())
  {
    list << QString::fromStdString(dir.string());
  }
  return list;
}

RulesModel* FileMoverWrapper::rulesModel() const
{
  return rulesModel_;
}
