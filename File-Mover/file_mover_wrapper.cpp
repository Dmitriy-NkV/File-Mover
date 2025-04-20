#include "file_mover_wrapper.h"

FileMoverWrapper::FileMoverWrapper(QObject *parent)
    : QObject{parent}
{}

void FileMoverWrapper::addDir(std::filesystem::path dirName)
{
    fileMover_.addDir(dirName);
}

void FileMoverWrapper::addRuleToDir(std::filesystem::path dirName, std::filesystem::path targetDir, std::vector< std::filesystem::path > ext, std::set< std::filesystem::path > exceptions)
{
    fileMover_.addRuleToDir(dirName, targetDir, ext, exceptions);
}

void FileMoverWrapper::addRuleToDir(std::filesystem::path dirName, std::filesystem::path targetDir, std::chrono::duration< int, std::ratio< 86400 > > duration, bool isGreaterThanDuration, std::set< std::filesystem::path > exceptions)
{
    fileMover_.addRuleToDir(dirName, targetDir, duration, isGreaterThanDuration, exceptions);
}

void FileMoverWrapper::addRuleToDir(std::filesystem::path dirName, std::filesystem::path targetDir, std::string name, bool isCheckRegister, std::set< std::filesystem::path > exceptions)
{
    fileMover_.addRuleToDir(dirName, targetDir, name, isCheckRegister, exceptions);
}

void FileMoverWrapper::addRuleToDir(std::filesystem::path dirName, std::filesystem::path targetDir, std::set< std::filesystem::path > exceptions)
{
    fileMover_.addRuleToDir(dirName, targetDir, exceptions);
}

void FileMoverWrapper::addRuleToDir(std::filesystem::path dirName, std::vector< std::filesystem::path > ext, std::set< std::filesystem::path > exceptions)
{
    fileMover_.addRuleToDir(dirName, ext, exceptions);
}

void FileMoverWrapper::addRuleToDir(std::filesystem::path dirName, std::chrono::duration< int, std::ratio< 86400 > > duration, bool isGreaterThanDuration, std::set< std::filesystem::path > exceptions)
{
    fileMover_.addRuleToDir(dirName, duration, isGreaterThanDuration, exceptions);
}

void FileMoverWrapper::deleteRuleFromDir(std::filesystem::path dirName, size_t id)
{
    fileMover_.deleteRuleFromDir(dirName, id);
}

void FileMoverWrapper::deleteDir(std::filesystem::path dirName)
{
    fileMover_.deleteDir(dirName);
}

void FileMoverWrapper::importConfig(std::filesystem::path config)
{
    fileMover_.importConfig(config);
}

nlohmann::json FileMoverWrapper::saveConfig() const
{
    return fileMover_.saveConfig();
}
