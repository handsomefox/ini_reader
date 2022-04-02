#include <filesystem>
#include <iostream>

#include "Ini.h"


int main() {
    const std::filesystem::path filepath = R"(C:\Users\hands\CLionProjects\ini_reader\example.ini)";

    if (!exists(filepath)) {
        return -1;
    }

    auto parsed = Ini::parse_file(filepath);

    std::string name = "Structure";
    auto result = Ini::find_section(parsed, name);

    if (!result) {
        std::cout << "Section '" << name << "' not found." << std::endl;
        return -1;
    }

    auto section = *result;

    std::string key = "ValuableInformation";
    std::string value = section[key];

    if (value.empty()) {
        std::cout << "Key '" << key << "' not found." << std::endl;
        return -1;
    }

    std::cout << key << " = " << value << std::endl;

    return 0;
}
