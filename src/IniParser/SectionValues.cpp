#include "SectionValues.h"

#include <utility>

void SectionValues::Set(const std::string &key, Value value)
{
  _values[key] = std::move(value);
}

Value SectionValues::Get(const std::string &key)
{
  return _values.at(key);
}

void SectionValues::Delete(const std::string &key)
{
  _values.erase(key);
}

bool SectionValues::Contains(const std::string &key)
{
  return _values.find(key) != _values.end();
}

const std::unordered_map<std::string, Value> &SectionValues::Data() const
{
  return _values;
}

bool SectionValues::Empty()
{
  return _values.empty();
}

void SectionValues::Clear()
{
  _values.clear();
}
