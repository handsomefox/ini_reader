#include <filesystem>
#include <iostream>

#include "Ini.h"


int main() {
    const std::filesystem::path filepath = R"(C:\Users\hands\CLionProjects\ini_reader\example.ini)";

    if (!exists(filepath)) {
        return -1;
    }

    auto parsed = Ini::parse_file(filepath);

    std::string name = "Display";
    auto result = Ini::find_section(parsed, name);

    if (!result.has_value()) {
        std::cout << "Section '" << name << "' not found." << std::endl;
        return -1;
    }

    std::string key = "fLightLODMaxStartFade";
    auto value = result.value()[key];

    if (value.empty()) {
        std::cout << "Key '" << key << "' not found." << std::endl;
        return -1;
    }

    std::cout << key << " = " << value.as_double() << std::endl;

    return 0;
}
