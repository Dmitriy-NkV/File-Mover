#ifndef RULES_HPP
#define RULES_HPP

#include <chrono>
#include <filesystem>
#include <variant>
#include <vector>
#include <set>

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

  template< class PathT, class ExtensionsT, class ExceptionsT >
  MovingByExtRule::MovingByExtRule(PathT&& targetDir, ExtensionsT&& ext, ExceptionsT&& exceptions):
    targetDir(std::forward< PathT >(targetDir)),
    ext(std::forward< ExtensionsT >(ext)),
    exceptions(std::forward< ExceptionsT >(exceptions))
  {}

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

  template< class PathT, class DaysT, class isGreaterT, class ExceptionsT >
  MovingByDateRule::MovingByDateRule(PathT&& targetDir, DaysT&& duration, isGreaterT&& isGreaterThanDuration, ExceptionsT&& exceptions):
    targetDir(std::forward< PathT >(targetDir)),
    duration(std::forward< DaysT >(duration)),
    isGreaterThanDuration(std::forward< isGreaterT >(isGreaterThanDuration)),
    exceptions(std::forward< ExceptionsT >(exceptions))
  {}

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

  template< class PathT, class NameT, class isCheckT, class ExceptionsT >
  MovingByNameRule::MovingByNameRule(PathT&& targetDir, NameT&& name, isCheckT&& isCheckRegister, ExceptionsT&& exceptions):
  targetDir(std::forward< PathT >(targetDir)),
  name(std::forward< NameT >(name)),
  isCheckRegister(std::forward< isCheckT >(isCheckRegister)),
  exceptions(std::forward< ExceptionsT >(exceptions))
{}

  struct MovingAllRule
  {
    template< class PathT, class ExceptionsT >
    MovingAllRule(PathT&& targetDir, ExceptionsT&& exceptions);
    ~MovingAllRule() = default;

    path targetDir;
    set exceptions;
  };

  template< class PathT, class ExceptionsT >
  MovingAllRule::MovingAllRule(PathT&& targetDir, ExceptionsT&& exceptions):
    targetDir(std::forward< PathT >(targetDir)),
    exceptions(std::forward< ExceptionsT >(exceptions))
  {}

  struct DeletingByExtRule
  {
    template< class ExtensionsT, class ExceptionsT >
    DeletingByExtRule(ExtensionsT&& ext, ExceptionsT&& exceptions);
    ~DeletingByExtRule() = default;

    paths ext;
    set exceptions;
  };

  template< class ExtensionsT, class ExceptionsT >
  DeletingByExtRule::DeletingByExtRule(ExtensionsT&& ext, ExceptionsT&& exceptions):
    ext(std::forward< ExtensionsT >(ext)),
    exceptions(std::forward< ExceptionsT >(exceptions))
  {}


  struct DeletingByDateRule
  {
    template< class DaysT, class isGreaterT, class ExceptionsT >
    DeletingByDateRule(DaysT&& duration, isGreaterT&& isGreaterThanDuration, ExceptionsT&& exceptions);
    ~DeletingByDateRule() = default;

    days duration;
    bool isGreaterThanDuration;
    set exceptions;
  };

  template< class DaysT, class isGreaterT, class ExceptionsT >
  DeletingByDateRule::DeletingByDateRule(DaysT&& duration, isGreaterT&& isGreaterThanDuration, ExceptionsT&& exceptions):
    duration(std::forward< DaysT >(duration)),
    isGreaterThanDuration(std::forward< isGreaterT >(isGreaterThanDuration)),
    exceptions(std::forward< ExceptionsT >(exceptions))
  {}

  using FileRule = std::variant<
    MovingByExtRule,
    MovingByDateRule,
    MovingByNameRule,
    MovingAllRule,
    DeletingByExtRule,
    DeletingByDateRule
  >;
}

#endif