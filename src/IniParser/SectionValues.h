#pragma once

#include <string>
#include <unordered_map>

#include "Value.h"

// SectionValues is a map of std::string keys to the Value(s) parsed from .ini
class SectionValues
{
public:
  SectionValues() = default;

  // Returns whether the storage is empty.
  bool is_empty();

  // Clears the storage.
  void clear();

  // Assigns the value to the key.
  void set_value(const std::string &key, Value value);

  // Returns the value from the key (throws if it does not exist).
  Value get_value(const std::string &);

  // Removes the value at the given key.
  void remove(const std::string &);

  // Returns whether the value at the given key exists.
  bool contains(const std::string &key);

  // Returns underlying data.
  const std::unordered_map<std::string, Value> &data() const;

private:
  std::unordered_map<std::string, Value> _values;
};
