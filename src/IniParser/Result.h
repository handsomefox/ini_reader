#pragma once

#include <optional>
#include <string>
#include <unordered_map>

#include "SectionValues.h"

// Result represents result after parsing.
// It is a map of [std::string] (sections), to SectionValues.
class Result
{
public:
  using _map = std::unordered_map<std::string, SectionValues>;

  Result() = delete;

  explicit Result(const _map &map);

  // Returns whether the storage is empty.
  bool is_empty();

  // Clears the storage.
  void clear();

  // Assigns the value to the key.
  void set_value(const std::string &key, SectionValues values);

  // Returns the value from the key (throws if it does not exist).
  SectionValues get_value(const std::string &key);

  // Removes the value at the given key.
  void remove(const std::string &key);

  // Returns whether the value at the given key exists.
  bool contains(const std::string &key);

  // Returns underlying data.
  _map const &data();

private:
  _map _sections;
};
