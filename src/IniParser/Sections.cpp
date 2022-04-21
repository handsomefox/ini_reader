#include "Sections.h"

#include <utility>

Values Sections::Get(const std::string &key) {
    return _sections.at(key);
}

void Sections::Delete(const std::string &key) {
    _sections.erase(key);
}

bool Sections::Exists(const std::string &key) {
    return _sections.find(key) != _sections.end();
}

std::unordered_map<std::string, Values> const &Sections::Data() {
    return _sections;
}

void Sections::Set(const std::string &key, Values values) {
    _sections[key] = std::move(values);
}

bool Sections::Empty() {
    return _sections.empty();
}

void Sections::Clear() {
    _sections.clear();
}
