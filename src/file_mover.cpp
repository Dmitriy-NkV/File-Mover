#include "file_mover.hpp"

void FileMover::addDir(fs::path dirName)
{
  auto pair = dirs_.insert({ dirName, details::Dir() });
  if (pair.second == false)
  {
    throw std::logic_error("Error: The directory already exists");
  }
}

set FileMover::makeRelatieve(fs::path dirName, const set& exceptions) const
{
  set relatieveExceptions;
  std::transform(exceptions.begin(), exceptions.end(), std::inserter(relatieveExceptions, relatieveExceptions.begin()),
    [&dirName](const path& exception)
    {
      return fs::relative(exception, dirName);
    });
  return relatieveExceptions;
}