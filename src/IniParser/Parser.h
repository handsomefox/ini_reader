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

// Parser is a class used for .ini format file parsing.
class Parser
{
public:
  // Everything that doesn't use a different section can be found under this
  // Key.
  const std::string DEFAULT_KEY = "===please_provide_a_section===";

  // Creates a parser with an empty path.
  Parser() = default;

  // Creates a parser with a given path.
  explicit Parser(std::filesystem::path path);

  // Sets the internal path to the parameter.
  void SetPath(std::filesystem::path const &path);

  /// Parse() parses the path.
  /// \return std::nullopt if any errors are encountered, else returns Result.
  std::optional<Result> Parse();

private:
  std::filesystem::path _path;
};
