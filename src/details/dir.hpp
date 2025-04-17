#ifndef DIR_HPP
#define DIR_HPP

#include <vector>
#include <filesystem>
#include "../additionals/json.hpp"
#include "rules.hpp"
#include "visitors.hpp"

using json = nlohmann::json;

namespace details
{
  class Dir
  {
  public:
    Dir() = default;
    Dir(const std::vector< FileRule >& rules);
    ~Dir() = default;

    template < class T, class... Args >
    void addRule(Args... args);

    void deleteRule(size_t id);
    const std::vector< FileRule >& getRules() const;

    json toJson() const;

  private:
    std::vector< FileRule > rules_;
  };

  template < class T, class... Args >
  void Dir::addRule(Args... args)
  {
    rules_.emplace_back(std::in_place_type_t< T >{}, std::forward< Args >(args)...);
  }
}

#endif