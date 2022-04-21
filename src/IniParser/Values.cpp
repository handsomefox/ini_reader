//
// Created by hands on 21.04.2022.
//

#include "Values.h"

#include <utility>

void Values::Set(const std::string &key, Value value) {
    _values[key] = std::move(value);
}

Value Values::Get(const std::string &key) {
    return _values.at(key);
}

void Values::Delete(const std::string &key) {
    _values.erase(key);
}

bool Values::Exists(const std::string &key) {
    return _values.find(key) != _values.end();
}

const std::unordered_map<std::string, Value> &Values::Data() const {
    return _values;
}

bool Values::Empty() {
    return _values.empty();
}

void Values::Clear() {
    _values.clear();
}
