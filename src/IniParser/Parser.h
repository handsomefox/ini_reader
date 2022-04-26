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
  // Everything that doesn't use a different section can be found under this key.
  // It is not const, which means it is editable.
  std::string DEFAULT_KEY = "DEFAULT_PARSER_KEY";

  // Creates a parser with an empty path.
  Parser() = default;

  /**
   * @brief Parses a given file.
   *
   * @param path path to a file
   * @return std::optional<Result> std::nullopt if any errors are encountered (which can be retrieved by Error),
   * or the Result class.
   */
  std::optional<Result> Parse(std::filesystem::path const &path);

  /**
   * @brief Returns an error message if the Parse() returned std::nullopt or "None".
   * After getting the error once, it is reset.
   *
   * @return std::string the error message.
   */
  std::string Error();

private:
  /**
   * @brief Set the Path variable
   *
   * @param path path to set
   */
  void SetPath(std::filesystem::path const &path);

  /**
   * @brief Parse() parses the path.
   * @return std::optional<Result> std::nullopt if any errors are encountered, else returns Result.
   */
  std::optional<Result> Parse();

private:
  std::filesystem::path _path;
  std::string _error_message{};
};
