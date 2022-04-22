#pragma once

#include <string>
#include <unordered_map>

#include "SectionValues.h"

// Result represents result after parsing.
// It is a map of [std::string] (sections), to SectionValues.
class Result
{
public:
  Result() = default;

  // Returns whether the storage is empty.
  bool Empty();

  // Clears the storage.
  void Clear();

  // Assigns the value to the key.
  void Set(const std::string &key, SectionValues values);

  // Returns the value from the key (throws if it does not exist).
  SectionValues Get(const std::string &key);

  // Removes the value at the given key.
  void Delete(const std::string &key);

  // Returns whether the value at the given key exists.
  bool Exists(const std::string &key);

  // Returns underlying data.
  std::unordered_map<std::string, SectionValues> const &Data();

private:
  std::unordered_map<std::string, SectionValues> _sections;
};
