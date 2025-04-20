#ifndef VISITORS_HPP
#define VISITORS_HPP

#include <regex>
#include "../additionals/json.hpp"
#include "rules.hpp"

using json = nlohmann::json;

namespace details
{
  struct JsonVisitor
  {
    json operator()(const MovingByExtRule& rule) const;
    json operator()(const MovingByDateRule& rule) const;
    json operator()(const MovingByNameRule& rule) const;
    json operator()(const MovingAllRule& rule) const;
    json operator()(const DeletingByExtRule& rule) const;
    json operator()(const DeletingByDateRule& rule) const;
  };

  struct RuleVisitor
  {
  public:
    RuleVisitor(path dirName);

    void operator()(const MovingByExtRule& rule) const;
    void operator()(const MovingByDateRule& rule) const;
    void operator()(const MovingByNameRule& rule) const;
    void operator()(const MovingAllRule& rule) const;
    void operator()(const DeletingByExtRule& rule) const;
    void operator()(const DeletingByDateRule& rule) const;

  private:
    void moveFile(const path& oldPath, const path& newPath) const;
    void deleteFile(const path& fileName) const;
    bool checkFile(const path& fileName, const set& exceptions) const;
    path dirPath_;
  };
}

#endif
