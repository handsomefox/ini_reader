#pragma once

#include <vector>
#include <filesystem>
#include <sstream>
#include <string>
#include <optional>

#include "Token.h"
#include "Value.h"
#include "SectionValues.h"
#include "Result.h"

class Parser {
public:
    // Everything that doesn't use a different section can be found under this Key.
    std::string DEFAULT_KEY = "ABSOLUTELYRANDOMSTRINGNOBODYSHOULDEVERYUSE";

    // Creates a parser with an empty path.
    Parser() = default;

    // Creates a parser with a given path.
    explicit Parser(std::filesystem::path path);

    // Sets the internal path to the parameter.
    void SetPath(std::filesystem::path const &path);

/// Parse() parses the path.
/// \return std::nullopt if any errors are encountered, else returns Result.
    std::optional<Result> Parse();

private:
    std::filesystem::path _path;
};
