#include "visitors.hpp"

using namespace details;
namespace fs = std::filesystem;

json JsonVisitor::operator()(const MovingByExtRule& rule) const
{
  return {
    { "ruleType", "MovingByExtRule" },
    { "targetDir", rule.targetDir },
    { "ext", rule.ext },
    { "exceptions", rule.exceptions }
  };
}

json JsonVisitor::operator()(const MovingByDateRule& rule) const
{
  return {
    { "ruleType", "MovingByDateRule" },
    { "targetDir", rule.targetDir },
    { "duration", rule.duration.count() },
    { "isGreaterThanDuration", rule.isGreaterThanDuration },
    { "exceptions", rule.exceptions }
  };
}

json JsonVisitor::operator()(const MovingByNameRule& rule) const
{
  return {
    { "ruleType", "MovingByNameRule" },
    { "targetDir", rule.targetDir },
    { "name", rule.name },
    { "isCheckRegister", rule.isCheckRegister },
    { "exceptions", rule.exceptions }
  };
}

json JsonVisitor::operator()(const MovingAllRule& rule) const
{
  return {
    { "ruleType", "MovingAllRule" },
    { "targetDir", rule.targetDir },
    { "exceptions", rule.exceptions }
  };
}

json JsonVisitor::operator()(const DeletingByExtRule& rule) const
{
  return {
    { "ruleType", "DeletingByExtRule" },
    { "ext", rule.ext },
    { "exceptions", rule.exceptions }
  };
}

json JsonVisitor::operator()(const DeletingByDateRule& rule) const
{
  return {
    { "ruleType", "DeletingByDateRule" },
    { "duration", rule.duration.count() },
    { "isGreaterThanDuration", rule.isGreaterThanDuration },
    { "exceptions", rule.exceptions }
  };
}

void RuleVisitor::moveFile(const path& oldPath, const path& newPath) const
{
  if (fs::exists(oldPath) && fs::exists(newPath) && !fs::exists(fs::path(newPath) / fs::path(oldPath).filename()))
  {
    fs::rename(oldPath, fs::path(newPath) /= fs::path(oldPath).filename());
  }
}

void RuleVisitor::deleteFile(const path& fileName) const
{
  fs::remove(fileName);
}

bool RuleVisitor::checkFile(const path& fileName, const set& exceptions) const
{
  return exceptions.find(fileName) != exceptions.cend();
}