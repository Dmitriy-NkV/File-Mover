#ifndef FILE_MOVER_HPP
#define FILE_MOVER_HPP

#include <map>
#include <filesystem>
#include <fstream>
#include "details/dir.hpp"

namespace fs = std::filesystem;

class FileMover
{
public:
  FileMover() = default;
  ~FileMover() = default;

  void addDir(fs::path dirName);

  void addRuleToDir(fs::path dirName, fs::path targetDir, paths ext, set exceptions);
  void addRuleToDir(fs::path dirName, fs::path targetDir, days duration, bool isGreaterThanDuration, set exceptions);
  void addRuleToDir(fs::path dirName, fs::path targetDir, std::string name, bool isCheckRegister, set exceptions);
  void addRuleToDir(fs::path dirName, fs::path targetDir, set exceptions);
  void addRuleToDir(fs::path dirName, paths ext, set exceptions);
  void addRuleToDir(fs::path dirName, days duration, bool isGreaterThanDuration, set exceptions);

  void deleteRuleFromDir(fs::path dirName, size_t id);
  void deleteDir(fs::path dirName);

private:
  std::map< fs::path, details::Dir > dirs_;
};

#endif