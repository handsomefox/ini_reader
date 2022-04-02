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
    // Just for typing less.
    using IniValues = std::unordered_map<std::string, std::string>;
    using Map = std::unordered_map<std::string, IniValues>;


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
    /// }
    /// \endcode
    /// \param path
    /// File to parse.
    /// \return
    /// A Hash Map (string pointing to another map).
    /// The other map (string to string) is all the values that belong to the section that was parsed.
    static Map parse_file(std::filesystem::path const &path);

    /// Used to fo find a section from .Ini file.
    /// Example:
    /// \code
    /// auto result = find_section(map, "name");
    /// if (!result.has_value) return -1;
    /// auto map = result.value();
    /// std::string key = "key";
    /// std::string value = map[key];
    /// \endcode
    /// \param map
    /// Map in which to search for name.
    /// \param name
    /// Section name to find inside of map, search with INI_DEFAULT_KEY as parameter
    /// for name if your key does not have a section.
    /// \return
    /// Found section wrapped in an std::optional or std::nullopt if nothing was found.
    static std::optional<IniValues> find_section(Map const &map, std::string const &name) {
        auto found = map.find(name);

        if (found == map.end())
            return std::nullopt;

        return {found->second};
    }

private:
    // This does not really need to be constructed.
    Ini() = default;
};
