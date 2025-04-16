#ifndef DIR_HPP
#define DIR_HPP

#include <vector>
#include <filesystem>
#include "../additionals/json.hpp"
#include "rules.hpp"

namespace details
{
  class Dir
  {
  public:
    Dir() = default;
    Dir(const std::vector< FileRule >& rules);
    ~Dir() = default;

  private:
    std::vector< FileRule > rules_;
  };
}

#endif