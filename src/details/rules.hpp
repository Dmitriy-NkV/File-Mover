#ifndef RULES_HPP
#define RULES_HPP

#include <chrono>
#include <filesystem>
#include <vector>
#include <set>
#include "../additionals/json.hpp"

using path = std::filesystem::path;
using paths = std::vector< std::filesystem::path >;
using set = std::set< path >;
using days = std::chrono::duration< int, std::ratio< 86400 > >;

namespace details
{
  struct MovingByExtRule
  {
    template< class PathT, class ExtensionsT, class ExceptionsT >
    MovingByExtRule(PathT&& targetDir, ExtensionsT&& ext, ExceptionsT&& exceptions);
    ~MovingByExtRule() = default;

    path targetDir;
    paths ext;
    set exceptions;
  };

  struct MovingByDateRule
  {
    template< class PathT, class DaysT, class isGreaterT, class ExceptionsT >
    MovingByDateRule(PathT&& targetDir, DaysT&& duration, isGreaterT&& isGreaterThanDuration, ExceptionsT&& exceptions);
    ~MovingByDateRule() = default;

    path targetDir;
    days duration;
    bool isGreaterThanDuration;
    set exceptions;
  };

  struct MovingByNameRule
  {
    template< class PathT, class NameT, class isCheckT, class ExceptionsT >
    MovingByNameRule(PathT&& targetDir, NameT&& name, isCheckT&& isCheckRegister, ExceptionsT&& exceptions);
    ~MovingByNameRule() = default;

    path targetDir;
    std::string name;
    bool isCheckRegister;
    set exceptions;
  };

  struct MovingAllRule
  {
    template< class PathT, class ExceptionsT >
    MovingAllRule(PathT&& targetDir, ExceptionsT&& exceptions);
    ~MovingAllRule() = default;

    path targetDir;
    set exceptions;
  };
}

#endif