#pragma once

#include <filesystem>
#include <optional>
#include <sstream>
#include <string>
#include <vector>

#include "Result.h"
#include "SectionValues.h"
#include "Token.h"
#include "Value.h"

class Parser
{
public:
  Parser() = default;

  /**
   * @brief Parses a given file.
   *
   * @param path path to a file
   * @return std::optional<Result> std::nullopt if any errors are encountered (which can be retrieved by Error),
   * or the Result class.
   */
  std::optional<Result> parse(std::filesystem::path const &path);

private:
  std::optional<Result> parse();

private:
  std::filesystem::path _path;
};
