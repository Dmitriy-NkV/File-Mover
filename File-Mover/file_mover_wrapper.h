#ifndef FILE_MOVER_WRAPPER_H
#define FILE_MOVER_WRAPPER_H

#include <QObject>
#include "C:\\Users\\Dmitr\\Documents\\File-Mover\\src\\file_mover.hpp"

class FileMoverWrapper : public QObject
{
    Q_OBJECT
public:
    explicit FileMoverWrapper(QObject *parent = nullptr);

    Q_INVOKABLE void addDir(std::filesystem::path dirName);

    Q_INVOKABLE void addRuleToDir(std::filesystem::path dirName, std::filesystem::path targetDir, std::vector< std::filesystem::path > ext, std::set< std::filesystem::path > exceptions);
    Q_INVOKABLE void addRuleToDir(std::filesystem::path dirName, std::filesystem::path targetDir, std::chrono::duration< int, std::ratio< 86400 > > duration, bool isGreaterThanDuration, std::set< std::filesystem::path > exceptions);
    Q_INVOKABLE void addRuleToDir(std::filesystem::path dirName, std::filesystem::path targetDir, std::string name, bool isCheckRegister, std::set< std::filesystem::path > exceptions);
    Q_INVOKABLE void addRuleToDir(std::filesystem::path dirName, std::filesystem::path targetDir, std::set< std::filesystem::path > exceptions);
    Q_INVOKABLE void addRuleToDir(std::filesystem::path dirName, std::vector< std::filesystem::path > ext, std::set< std::filesystem::path > exceptions);
    Q_INVOKABLE void addRuleToDir(std::filesystem::path dirName, std::chrono::duration< int, std::ratio< 86400 > > duration, bool isGreaterThanDuration, std::set< std::filesystem::path > exceptions);

    Q_INVOKABLE void deleteRuleFromDir(std::filesystem::path dirName, size_t id);
    Q_INVOKABLE void deleteDir(std::filesystem::path dirName);

    Q_INVOKABLE void importConfig(std::filesystem::path config);
    Q_INVOKABLE nlohmann::json saveConfig() const;

// signals:
//     void valueChanged();
//     void nameChanged();
//     void operationCompleted(bool success);

private:
    FileMover fileMover_;
};

#endif // FILE_MOVER_WRAPPER_H
