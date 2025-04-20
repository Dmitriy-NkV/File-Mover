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

RuleVisitor::RuleVisitor(fs::path dirPath):
  dirPath_(dirPath)
{}

void RuleVisitor::operator()(const MovingByExtRule& rule) const
{
  std::vector< path > files;
  auto options = fs::directory_options::skip_permission_denied;
  for (auto i = fs::recursive_directory_iterator(dirPath_, options); i != fs::recursive_directory_iterator(); ++i)
  {
    bool shouldIgnore = checkFile(fs::relative((*i), dirPath_), rule.exceptions)
      || fs::equivalent(*i, rule.targetDir);

    if (shouldIgnore && fs::is_directory(*i))
    {
      i.disable_recursion_pending();
    }
    else if (!shouldIgnore && fs::is_regular_file(*i))
    {
      for (auto j = rule.ext.cbegin(); j != rule.ext.cend(); ++j)
      {
        if (fs::equivalent((*i).path().extension(), *j))
        {
          files.push_back(*i);
          break;
        }
      }
    }
  }

  for (auto i = files.begin(); i != files.end(); ++i)
  {
    moveFile(dirPath_ / (*i), rule.targetDir);
  }
}

void RuleVisitor::operator()(const MovingByDateRule& rule) const
{
  std::vector< path > files;
  auto options = fs::directory_options::skip_permission_denied;
  for (auto i = fs::recursive_directory_iterator(dirPath_, options); i != fs::recursive_directory_iterator(); ++i)
  {
    bool shouldIgnore = checkFile(fs::relative((*i), dirPath_), rule.exceptions)
      || fs::equivalent(*i, rule.targetDir);

    if (shouldIgnore && fs::is_directory(*i))
    {
      i.disable_recursion_pending();
    }
    else if (!shouldIgnore && fs::is_regular_file(*i))
    {
      auto now = fs::__file_clock::now();
      bool isGreater = std::chrono::duration_cast< days >(now - (*i).last_write_time()).count() > rule.duration.count();
      if (rule.isGreaterThanDuration == isGreater)
      {
        files.push_back(*i);
      }
    }
  }

  for (auto i = files.begin(); i != files.end(); ++i)
  {
    moveFile(dirPath_ / (*i), rule.targetDir);
  }
}

void RuleVisitor::operator()(const MovingByNameRule& rule) const
{
  std::regex pattern(rule.name);
  if (!rule.isCheckRegister)
  {
    pattern = std::regex(rule.name, std::regex::icase);
  }

  std::vector< path > files;
  auto options = fs::directory_options::skip_permission_denied;
  for (auto i = fs::recursive_directory_iterator(dirPath_, options); i != fs::recursive_directory_iterator(); ++i)
  {
    bool shouldIgnore = checkFile(fs::relative((*i), dirPath_), rule.exceptions)
      || fs::equivalent(*i, rule.targetDir);

    if (shouldIgnore && fs::is_directory(*i))
    {
      i.disable_recursion_pending();
    }
    else if (!shouldIgnore && std::regex_search((*i).path().filename().string(), pattern))
    {
      files.push_back(*i);
    }
  }

  for (auto i = files.begin(); i != files.end(); ++i)
  {
    moveFile(dirPath_ / (*i), rule.targetDir);
  }
}

void RuleVisitor::operator()(const MovingAllRule& rule) const
{
  std::vector< path > files;
  auto options = fs::directory_options::skip_permission_denied;
  for (auto i = fs::recursive_directory_iterator(dirPath_, options); i != fs::recursive_directory_iterator(); ++i)
  {
    bool shouldIgnore = checkFile(fs::relative((*i), dirPath_), rule.exceptions)
      || fs::equivalent(*i, rule.targetDir);

    if (shouldIgnore && fs::is_directory(*i))
    {
      i.disable_recursion_pending();
    }
    else if (!shouldIgnore)
    {
      files.push_back(*i);
    }
  }

  for (auto i = files.begin(); i != files.end(); ++i)
  {
    moveFile(dirPath_ / (*i), rule.targetDir);
  }
}

void RuleVisitor::operator()(const DeletingByExtRule& rule) const
{
  std::vector< path > files;
  auto options = fs::directory_options::skip_permission_denied;
  for (auto i = fs::recursive_directory_iterator(dirPath_, options); i != fs::recursive_directory_iterator(); ++i)
  {
    bool shouldIgnore = checkFile(fs::relative((*i), dirPath_), rule.exceptions);

    if (shouldIgnore && fs::is_directory(*i))
    {
      i.disable_recursion_pending();
    }
    else if (! shouldIgnore && fs::is_regular_file(*i))
    {
      for (auto j = rule.ext.cbegin(); j != rule.ext.cend(); ++j)
      {
        if (fs::equivalent((*i).path().extension(), *j))
        {
          files.push_back(*i);
          break;
        }
      }
    }
  }

  for (auto i = files.begin(); i != files.end(); ++i)
  {
    deleteFile(dirPath_ / (*i));
  }
}

void RuleVisitor::operator()(const DeletingByDateRule& rule) const
{
  std::vector< path > files;
  auto options = fs::directory_options::skip_permission_denied;
  for (auto i = fs::recursive_directory_iterator(dirPath_, options); i != fs::recursive_directory_iterator(); ++i)
  {
    bool shouldIgnore = checkFile(fs::relative((*i), dirPath_), rule.exceptions);

    if (shouldIgnore && fs::is_directory(*i))
    {
      i.disable_recursion_pending();
    }
    else if (!shouldIgnore && fs::is_regular_file(*i))
    {
      auto now = fs::__file_clock::now();
      bool isGreater = std::chrono::duration_cast< days >(now - (*i).last_write_time()).count() > rule.duration.count();
      if (rule.isGreaterThanDuration == isGreater)
      {
        files.push_back(*i);
      }
    }
  }

  for (auto i = files.begin(); i != files.end(); ++i)
  {
    deleteFile(dirPath_ / (*i));
  }
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
