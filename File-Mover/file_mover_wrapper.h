#ifndef FILE_MOVER_WRAPPER_H
#define FILE_MOVER_WRAPPER_H

#include <QObject>
#include <filesystem>
#include <chrono>
#include <set>

class FileMoverWrapper : public QObject
{
    Q_OBJECT
public:
    explicit FileMoverWrapper(QObject *parent = nullptr);

    Q_INVOKABLE void addDir(std::filesystem::path dirName);
    Q_INVOKABLE void addRuleToDir(std::filesystem::path dirName, std::filesystem::path targetDir, std::chrono::duration< int, std::ratio< 86400 > > duration, bool isGreaterThan);

    Q_INVOKABLE void addRuleToDir(std::filesystem::path dirName, std::filesystem::path targetDir, std::vector< std::filesystem::path > ext, std::set< std::filesystem::path > exceptions);
    Q_INVOKABLE void addRuleToDir(std::filesystem::path dirName, std::filesystem::path targetDir, std::chrono::duration< int, std::ratio< 86400 > > duration, bool isGreaterThanDuration, std::set< std::filesystem::path > exceptions);
    Q_INVOKABLE void addRuleToDir(std::filesystem::path dirName, std::filesystem::path targetDir, std::string name, bool isCheckRegister, std::set< std::filesystem::path > exceptions);
    Q_INVOKABLE void addRuleToDir(std::filesystem::path dirName, std::filesystem::path targetDir, std::set< std::filesystem::path > exceptions);
    Q_INVOKABLE void addRuleToDir(std::filesystem::path dirName, std::vector< std::filesystem::path > ext, std::set< std::filesystem::path > exceptions);
    Q_INVOKABLE void addRuleToDir(std::filesystem::path dirName, std::chrono::duration< int, std::ratio< 86400 > > duration, bool isGreaterThanDuration, std::set< std::filesystem::path > exceptions);

    void deleteRuleFromDir(std::filesystem::path dirName, size_t id);
    void deleteDir(std::filesystem::path dirName);

signals:
};

#endif // FILE_MOVER_WRAPPER_H
