#include "Value.h"
#include "Utils.h"

Value::Value(std::string value) : _data(std::move(value)) {}

bool Value::is_empty() const
{
  return _data.empty();
}

std::string Value::to_string() const
{
  return _data;
}

int32_t Value::to_i32() const
{
  if (_data.empty())
  {
    return 0;
  }

  return std::stoi(_data);
}

float Value::to_f32() const
{
  if (_data.empty())
  {
    return 0.0f;
  }

  return std::stof(_data);
}

double Value::to_f64() const
{
  if (_data.empty())
  {
    return 0.0;
  }

  return std::stod(_data);
}

bool Value::to_bool() const
{
  bool is_alpha = true;

  if (contains(_data, '1') || contains(_data, '0'))
  {
    is_alpha = false;
  }

  bool ret;

  if (is_alpha)
  {
    std::istringstream(_data) >> std::boolalpha >> ret;
  }
  else
  {
    std::istringstream(_data) >> ret;
  }

  return ret;
}

std::ostream &operator<<(std::ostream &stream, const Value &val)
{
  stream << val._data;
  return stream;
}
