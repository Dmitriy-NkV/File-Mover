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

  void execDir(fs::path dirName) const;
  void execDirs() const;

  void importConfig(fs::path config);
  json saveConfig() const;

private:
  template < class Rule, class... Args >
  void addRule(fs::path dirName, Args... args);
  set makeRelatieve(fs::path dirName, const set& exceptions) const;
  details::FileRule parseRule(const json& ruleJson) const;

  std::map< fs::path, details::Dir > dirs_;
};

template < class Rule, class... Args >
void FileMover::addRule(fs::path dirName, Args... args)
{
  dirs_.at(dirName).addRule< Rule >(std::forward< Args >(args)...);
}

#endif