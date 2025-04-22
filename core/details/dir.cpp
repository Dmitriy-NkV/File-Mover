#include "dir.hpp"

#include <iostream>

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

const std::vector< FileRule >& Dir::getRules() const
{
  return rules_;
}

json Dir::toJson() const
{
  json result = json::array();
  for (auto i = rules_.cbegin(); i != rules_.cend(); ++i)
  {
    result.push_back(std::visit(JsonVisitor(), (*i)));
  }
  return result;
}
