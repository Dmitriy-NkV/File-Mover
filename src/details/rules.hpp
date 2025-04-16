#ifndef RULES_HPP
#define RULES_HPP

#include <filesystem>
#include <vector>
#include <set>
#include "../additionals/json.hpp"

using path = std::filesystem::path;
using paths = std::vector< std::filesystem::path >;
using set = std::set< path >;

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
}

#endif