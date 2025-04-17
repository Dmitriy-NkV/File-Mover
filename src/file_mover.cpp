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