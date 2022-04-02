#include "Ini.h"

Ini::Map Ini::parse_file(const std::filesystem::path &path) {
    auto tokens = IniParser::parse(path);

    Map map;
    std::string current_section = INI_DEFAULT_KEY;
    IniValues iniValues;

    for (auto const &token: tokens) {
        if (token.is_section()) {
            if (!iniValues.empty()) {
                map[current_section] = iniValues;
                iniValues.clear();
            }
            current_section = token.value();
            continue;
        }

        if (token.is_key_property()) {
            auto k = token.key();
            auto v = token.value();
            iniValues[k] = v;
        }
    }
    map[current_section] = iniValues;
    return map;
}