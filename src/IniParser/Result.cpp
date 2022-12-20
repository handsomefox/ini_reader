#include "Result.h"

#include <utility>

Result::Result(const _map &map)
    : _sections(map)
{
}

SectionValues Result::get_value(const std::string &key)
{
  return _sections.at(key);
}

void Result::remove(const std::string &key)
{
  _sections.erase(key);
}

bool Result::contains(const std::string &key)
{
  return _sections.find(key) != _sections.end();
}

std::unordered_map<std::string, SectionValues> const &Result::data()
{
  return _sections;
}

void Result::set_value(const std::string &key, SectionValues values)
{
  _sections[key] = std::move(values);
}

bool Result::is_empty()
{
  return _sections.empty();
}

void Result::clear()
{
  _sections.clear();
}
