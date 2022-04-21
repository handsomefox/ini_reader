#pragma once

#include <string>
#include <unordered_map>

#include "Values.h"

class Sections {
public:
    Sections() = default;

    // Returns whether the storage is empty.
    bool Empty();

    // Clears the storage.
    void Clear();

    // Assigns the value to the key.
    void Set(const std::string &key, Values values);

    // Returns the value from the key (throws if it does not exist).
    Values Get(const std::string &key);

    // Removes the value at the given key.
    void Delete(const std::string &key);

    // Returns whether the value at the given key exists.
    bool Exists(const std::string &key);

    // Returns underlying data.
    std::unordered_map<std::string, Values> const &Data();


private:
    std::unordered_map<std::string, Values> _sections;
};
