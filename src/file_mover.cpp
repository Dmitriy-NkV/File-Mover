#include "file_mover.hpp"

void FileMover::addDir(fs::path dirName)
{
  auto pair = dirs_.insert({ dirName, details::Dir() });
  if (pair.second == false)
  {
    throw std::logic_error("Error: The directory already exists");
  }
}

void FileMover::addRuleToDir(fs::path dirName, fs::path targetDir, paths ext, set exceptions)
{
  set relatieveExceptions = makeRelatieve(dirName, exceptions);
  addRule< details::MovingByExtRule >(dirName, targetDir, ext, relatieveExceptions);
}

void FileMover::addRuleToDir(fs::path dirName, fs::path targetDir, days duration, bool isGreaterThanDuration,
  set exceptions)
{
  set relatieveExceptions = makeRelatieve(dirName, exceptions);
  addRule< details::MovingByDateRule >(dirName, targetDir, duration, isGreaterThanDuration, relatieveExceptions);
}

void FileMover::addRuleToDir(fs::path dirName, fs::path targetDir, std::string name, bool isCheckRegister,
  set exceptions)
{
  set relatieveExceptions = makeRelatieve(dirName, exceptions);
  addRule< details::MovingByNameRule >(dirName, targetDir, name, isCheckRegister, relatieveExceptions);
}

void FileMover::addRuleToDir(fs::path dirName, fs::path targetDir, set exceptions)
{
  set relatieveExceptions = makeRelatieve(dirName, exceptions);
  addRule< details::MovingAllRule >(dirName, targetDir, relatieveExceptions);
}

void FileMover::addRuleToDir(fs::path dirName, paths ext, set exceptions)
{
  set relatieveExceptions = makeRelatieve(dirName, exceptions);
  addRule< details::DeletingByExtRule >(dirName, ext, relatieveExceptions);
}

void FileMover::addRuleToDir(fs::path dirName, days duration, bool isGreaterThanDuration, set exceptions)
{
  set relatieveExceptions = makeRelatieve(dirName, exceptions);
  addRule< details::DeletingByDateRule >(dirName, duration, isGreaterThanDuration, relatieveExceptions);
}

void FileMover::deleteRuleFromDir(fs::path dirName, size_t id)
{
  dirs_.at(dirName).deleteRule(id);
}

void FileMover::deleteDir(fs::path dirName)
{
  size_t count = dirs_.erase(dirName);
  if (!count)
  {
    throw std::logic_error("Error: Nothing to delete");
  }
}

void FileMover::execDir(fs::path dirName) const
{
  auto rules = dirs_.at(dirName).getRules();
  details::RuleVisitor visitor(dirName);
  for (auto i = rules.cbegin(); i != rules.cend(); ++i)
  {
    std::visit(visitor, (*i));
  }
}

void FileMover::execDirs() const
{
  for (auto i = dirs_.cbegin(); i != dirs_.cend(); ++i)
  {
    execDir(i->first);
  }
}

void FileMover::importConfig(fs::path configPath)
{
  std::ifstream file(configPath);
  if (!file.is_open())
  {
    throw std::runtime_error("Error: Config not found");
  }
  json config = json::parse(file);
  std::map< fs::path, details::Dir > newDirs;
  for (auto& [dirName, rulesArray]: config.items())
  {
    std::vector< details::FileRule > rules;
    for (auto& ruleJson: rulesArray)
    {
      rules.push_back(parseRule(ruleJson));
    }
    newDirs[dirName] = details::Dir(rules);
  }
  dirs_ = newDirs;
}

json FileMover::saveConfig() const
{
  json result = json::object();
  for (auto i = dirs_.cbegin(); i != dirs_.cend(); ++i)
  {
    result[i->first] = i->second.toJson();
  }
  return result;
}

set FileMover::makeRelatieve(fs::path dirName, const set& exceptions) const
{
  set relatieveExceptions;
  std::transform(exceptions.begin(), exceptions.end(), std::inserter(relatieveExceptions, relatieveExceptions.begin()),
    [&dirName](const path& exception)
    {
      return fs::relative(exception, dirName);
    });
  return relatieveExceptions;
}

details::FileRule FileMover::parseRule(const json& ruleJson) const
{
  std::string ruleType = ruleJson.at("ruleType").get<std::string>();
  if (ruleType == "MovingByExtRule")
  {
    path targetDir = ruleJson.at("targetDir");
    paths ext = ruleJson.at("ext");
    set exceptions = ruleJson.at("exceptions");
    return details::MovingByExtRule(targetDir, ext, exceptions);
  }
  else if (ruleType == "MovingByDateRule")
  {
    path targetDir = ruleJson.at("targetDir");
    size_t duration = ruleJson.at("duration");
    bool isGreaterThanDuration = ruleJson.at("isGreaterThanDuration");
    set exceptions = ruleJson.at("exceptions");
    return details::MovingByDateRule(targetDir, duration, isGreaterThanDuration, exceptions);
  }
  else if (ruleType == "MovingByNameRule")
  {
    path targetDir = ruleJson.at("targetDir");
    std::string name = ruleJson.at("name");
    bool isCheckRegister = ruleJson.at("isCheckRegister");
    set exceptions = ruleJson.at("exceptions");
    return details::MovingByNameRule(targetDir, name, isCheckRegister, exceptions);
  }
  else if (ruleType == "MovingAllRule")
  {
    path targetDir = ruleJson.at("targetDir");
    set exceptions = ruleJson.at("exceptions");
    return details::MovingAllRule(targetDir, exceptions);
  }
  else if (ruleType == "DeletingByExtRule")
  {
    paths ext = ruleJson.at("ext");
    set exceptions = ruleJson.at("exceptions");
    return details::DeletingByExtRule(ext, exceptions);
  }
  else if (ruleType == "DeletingByDateRule")
  {
    paths ext = ruleJson.at("ext");
    size_t duration = ruleJson.at("duration");
    bool isGreaterThanDuration = ruleJson.at("isGreaterThanDuration");
    set exceptions = ruleJson.at("exceptions");
    return details::DeletingByDateRule(duration, isGreaterThanDuration, exceptions);
  }
  else
  {
    throw std::runtime_error("Error: Unknown rule type: " + ruleType);
  }
}