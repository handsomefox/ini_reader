#include "Result.h"

#include <utility>

SectionValues Result::Get(const std::string &key)
{
  return _sections.at(key);
}

void Result::Delete(const std::string &key)
{
  _sections.erase(key);
}

bool Result::Contains(const std::string &key)
{
  return _sections.find(key) != _sections.end();
}

std::unordered_map<std::string, SectionValues> const &Result::Data()
{
  return _sections;
}

void Result::Set(const std::string &key, SectionValues values)
{
  _sections[key] = std::move(values);
}

bool Result::Empty()
{
  return _sections.empty();
}

void Result::Clear()
{
  _sections.clear();
}
