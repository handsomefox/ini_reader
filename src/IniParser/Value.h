#pragma once

#include <ostream>
#include <sstream>
#include <string>

// Value represents parsed .ini key property value.
// Contains conversions to different types.
class Value
{
public:
  explicit Value(std::string value);

  Value() = default;

  // Return whether the value is empty
  [[nodiscard]] bool Empty() const;

  // Return value as str.
  [[nodiscard]] std::string ToString() const;

  // Return value as int32 using std::stoi or 0 if value is empty.
  [[nodiscard]] int32_t ToInt32() const;

  // Return value as float using std::stof or 0.0f if value is empty.
  [[nodiscard]] float ToFloat() const;

  // Return value as double using std::stod or 0.0 if value is empty.
  [[nodiscard]] double ToDouble() const;

  // Return value as bool (if string is either `0`/`1` or `true`/`false`.
  [[nodiscard]] bool ToBool() const;

  friend std::ostream &operator<<(std::ostream &stream, const Value &val);

private:
  std::string _data;
};
