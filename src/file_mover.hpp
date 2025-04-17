#ifndef FILE_MOVER_HPP
#define FILE_MOVER_HPP

#include <map>
#include <filesystem>
#include "details/dir.hpp"

namespace fs = std::filesystem;

class FileMover
{
public:
  FileMover() = default;
  ~FileMover() = default;

private:
  std::map< fs::path, details::Dir > dirs_;
};

#endif