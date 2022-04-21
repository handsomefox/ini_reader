#pragma once

#include <vector>
#include <string>
#include <filesystem>
#include <sstream>
#include <fstream>

// Reads a file into std::stringstream.
inline static std::stringstream fileToSs(const std::filesystem::path &path) {
    std::ifstream ifs(path);
    std::stringstream buf;
    buf << ifs.rdbuf();
    return buf;
}

// Extract lines from std::stringstream to std::vector<std::string>.
inline static std::vector<std::string> extractLines(std::stringstream &ss) {
    std::vector<std::string> vec{};

    while (!ss.eof()) {
        std::string line{};
        std::getline(ss, line, '\n');
        vec.push_back(line);
    }
    return vec;
}

// Checks if the string starts with a specified character.
inline static bool startsWith(const std::string &str, const char c) {
    if (str.length() == 0)
        return false;

    return str[0] == c;
}

// Checks if the string ends with a specified character.
inline static bool endsWith(const std::string &str, const char c) {
    if (str.length() == 0)
        return false;

    return str[str.length() - 1] == c;
}

// Checks if the string contains the specified character.
inline static bool contains(const std::string &str, const char c) {
    return str.find(c) != std::string::npos;
}
