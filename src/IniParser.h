#pragma once

#include <filesystem>
#include <sstream>
#include <vector>
#include <string>
#include <fstream>

#include "Token.h"


class IniParser {
public:
    // Parses a file into a std::vector<Token>. Does not check if path exists.
    static std::vector<Token> parse(std::filesystem::path const &path);

private:
    IniParser() = default;

    // Reads a file into std::stringstream.
    static std::stringstream rd_file_to_ss(std::filesystem::path const &fpath);

    // Extract lines from std::stringstream to std::vector<std::string>.
    static std::vector<std::string> extract_lines(std::stringstream &ss);

    // Checks if the string starts with a specified character.
    static bool starts_with(std::string const &str, char c);

    // Checks if the string ends with a specified character.
    static bool ends_with(std::string const &str, char c);

    // Checks if the string contains the specified character.
    static bool contains(std::string const &str, char c);
};
