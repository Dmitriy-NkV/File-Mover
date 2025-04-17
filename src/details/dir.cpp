#include "dir.hpp"

using namespace details;

Dir::Dir(const std::vector< FileRule >& rules):
  rules_(rules)
{}

void Dir::deleteRule(size_t index)
{
  if (index < rules_.size())
  {
    auto iterator = rules_.cbegin();
    std::advance(iterator, index);
    rules_.erase(iterator);
  }
  else
  {
    throw std::out_of_range("Error: Index is out of range");
  }
}
