#ifndef VISITORS_HPP
#define VISITORS_HPP

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
}

#endif