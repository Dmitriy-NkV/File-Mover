#include "file_mover.hpp"

void FileMover::addDir(fs::path dirName)
{
  auto pair = dirs_.insert({ dirName, details::Dir() });
  if (pair.second == false)
  {
    throw std::logic_error("Error: The directory already exists");
  }
}