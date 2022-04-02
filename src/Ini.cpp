#include "Ini.h"

Ini::ini_map Ini::parse_file(const std::filesystem::path &path) {
    auto tokens = ini_parser::parse(path);

    ini_map map;
    std::string current_section = INI_DEFAULT_KEY;
    section_values ini_values;

    for (auto const &token: tokens) {
        if (token.is_section()) {
            if (!ini_values.empty()) {
                map[current_section] = ini_values;
                ini_values.clear();
            }
            current_section = token.value();
            continue;
        }

        if (token.is_key_property()) {
            auto k = token.key();
            auto v = token.value();
            ini_values[k] = ini_value(v);
        }
    }
    map[current_section] = ini_values;
    return map;
}
