#pragma once

#include <string>
#include <unordered_map>

#include "Value.h"

class SectionValues {
public:
    SectionValues() = default;

    // Returns whether the storage is empty.
    bool Empty();

    // Clears the storage.
    void Clear();

    // Assigns the value to the key.
    void Set(const std::string &key, Value value);

    // Returns the value from the key (throws if it does not exist).
    Value Get(const std::string &);

    // Removes the value at the given key.
    void Delete(const std::string &);

    // Returns whether the value at the given key exists.
    bool Exists(const std::string &key);

    // Returns underlying data.
    const std::unordered_map<std::string, Value> &Data() const;

private:
    std::unordered_map<std::string, Value> _values;
};
