#include "SectionValues.h"

#include <utility>

void SectionValues::set_value(const std::string &key, Value value)
{
  _values[key] = std::move(value);
}

Value SectionValues::get_value(const std::string &key)
{
  return _values.at(key);
}

void SectionValues::remove(const std::string &key)
{
  _values.erase(key);
}

bool SectionValues::contains(const std::string &key)
{
  return _values.find(key) != _values.end();
}

const std::unordered_map<std::string, Value> &SectionValues::data() const
{
  return _values;
}

bool SectionValues::is_empty()
{
  return _values.empty();
}

void SectionValues::clear()
{
  _values.clear();
}
