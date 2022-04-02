#include <filesystem>
#include <iostream>

#include "Ini.h"


int main() {
    const std::filesystem::path filepath = R"(C:\Users\hands\CLionProjects\ini_reader\example.ini)";

    if (!exists(filepath)) {
        return -1;
    }

    auto parsed = Ini::parse_file(filepath);

    for (auto const&[k, v]: parsed) {
        std::cout << "Key: " << k << std::endl;
        std::cout << "Values: " << std::endl;
        for (auto const&[k2, v2]: v) {
            std::cout << "    [Key, Value]: " << " [" << k2 << "," << v2.as_str() << "]" << std::endl;
        }
    }

    std::string name = "Display";
    auto result = Ini::find_section(parsed, name);

    if (result.has_value()) {
        std::string key = "fLightLODMaxStartFade";
        auto value = result.value()[key];

        if (value.empty()) {
            std::cout << "Key '" << key << "' not found." << std::endl;
            return -1;
        }
        std::cout << key << " = " << value.as_double() << std::endl;
    } else {
        std::cout << "Section '" << name << "' not found." << std::endl;
        return -1;
    }

    return 0;
}
