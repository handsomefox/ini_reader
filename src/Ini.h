#pragma once

#include "Token.h"
#include "IniParser.h"

#include <vector>
#include <unordered_map>
#include <sstream>
#include <string>
#include <optional>

// Everything that doesn't use a different section can be found under this key.
#define INI_DEFAULT_KEY "ABSOLUTELYRANDOMSTRINGNOBODYSHOULDEVERYUSE";

class Ini {
public:
    struct ini_value {
        ini_value() = default;

        explicit ini_value(std::string v) : value(std::move(v)) {}

        // Return whether the value is empty
        [[nodiscard]] bool empty() const {
            return value.empty();
        }

        // Return value as str.
        [[nodiscard]] std::string as_str() const {
            return value;
        }

        // Return value as int32 using std::stoi or 0 if value is empty.
        [[nodiscard]] int32_t as_int32() const {
            if (value.empty())
                return 0;

            return std::stoi(value);
        };

        // Return value as float using std::stof or 0.0f if value is empty.
        [[nodiscard]] float as_float() const {
            if (value.empty())
                return 0.0f;

            return std::stof(value);
        };

        // Return value as double using std::stod or 0.0 if value is empty.
        [[nodiscard]] double as_double() const {
            if (value.empty())
                return 0.0;

            return std::stod(value);
        };

        // Return value as bool (if string is either `0`/`1` or `true`/`false`.
        [[nodiscard]] bool as_bool() const {
            bool is_alpha;

            if (contains(value, '1') || contains(value, '0'))
                is_alpha = false;
            else is_alpha = true;

            bool ret;

            if (is_alpha) std::istringstream(value) >> std::boolalpha >> ret;
            else std::istringstream(value) >> ret;

            return ret;
        };
    private:
        static bool contains(const std::string &str, const char c) {
            return str.find(c) != std::string::npos;
        }

        std::string value;
    };
    // Just for typing less.
    using section_values = std::unordered_map<std::string, ini_value>;
    using ini_map = std::unordered_map<std::string, section_values>;

    /// Parses a file into a hash map (string to another map)
    ///
    /// It does not check if the file exists.
    /// \code
    /// Example:
    ///  File: `[Section]
    ///          key=value`
    /// \endcode
    ///   For this file, to get the value of key, you would need to do :
    /// \code
    /// auto found = find_section(map, "Section")
    /// if (found) {
    ///  auto section = *found;
    ///  auto value = section[key];
    ///  std::string str = value.as_str();
    /// }
    /// \endcode
    /// \param path
    /// File to parse.
    /// \return
    /// A Hash ini_map (string pointing to another map).
    /// The other map (string to string) is all the values that belong to the section that was parsed.
    static ini_map parse_file(std::filesystem::path const &path);

    /// Used to fo find a section from .Ini file.
    /// Example:
    /// \code
    /// auto result = find_section(map, "name");
    /// if (!result.has_value) return -1;
    /// auto map = result.value();
    /// std::string key = "key";
    /// auto value = map[key];
    /// double d = value.as_double();
    /// \endcode
    /// \param map
    /// ini_map in which to search for name.
    /// \param name
    /// Section name to find inside of map, search with INI_DEFAULT_KEY as parameter
    /// for name if your key does not have a section.
    /// \return
    /// Found section wrapped in an std::optional or std::nullopt if nothing was found.
    static std::optional<section_values> find_section(ini_map const &map, std::string const &name) {
        auto found = map.find(name);

        if (found == map.end())
            return std::nullopt;

        return {found->second};
    }

private:
    // This does not really need to be constructed.
    Ini() = default;
};
