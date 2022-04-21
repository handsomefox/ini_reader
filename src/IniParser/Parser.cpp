#include "Parser.h"
#include "Utils.h"

#include <fstream>
#include <utility>

static inline Token ParseSection(std::string const &line, std::string &section) {
    std::string value;
    for (auto const &c: line) {
        if (c == '[' || c == ']')
            continue;

        if (c == '#' || c == ';')
            break;

        value += c;
    }
    section = value;
    auto tokenData = Token::TokenData{
            Token::TokenType::Section,
            "",
            value,
            ""
    };
    return Token(tokenData);
}

static inline Token ParseKeyProperty(std::string const &line, std::string &section) {
    bool key = true;
    std::string k, v;
    for (auto const &c: line) {
        // FIXME: Figure out how to properly handle spaces.
        //        i.e. should we ignore all the spaces, or
        //        only in keys? only in values?
        // if (c == ' ') continue;
        if (c == '#' || c == ';')
            break;
        if (c == '=') {
            key = false;
            continue;
        }

        if (key) k += c;
        else v += c;
    }
    auto tokenData = Token::TokenData{
            Token::TokenType::KeyProperty,
            k,
            v,
            section
    };

    return Token(tokenData);
}

// Returns an std::vector<Token> created from the file.
static inline std::vector<Token> Tokenize(std::filesystem::path const &path) {
    auto ss = fileToSs(path);
    auto lines = extractLines(ss);

    std::vector<Token> tokens{};
    std::string section{};

    for (auto const &line: lines) {
        if (line.empty())
            continue;

        if (startsWith(line, '#') || startsWith(line, ';'))
            continue;

        if (startsWith(line, '[')) {
            auto token = ParseSection(line, section);
            tokens.emplace_back(token);
        }
        if (contains(line, '=')) {
            auto token = ParseKeyProperty(line, section);
            tokens.emplace_back(token);
        }
    }
    return tokens;
}

std::optional<Sections> Parser::Parse() {
    auto tokens = Tokenize(_path);

    if (tokens.empty()) {
        return std::nullopt;
    }

    std::string current_section = DEFAULT_KEY;

    Sections sections;
    Values values;

    for (auto const &token: tokens) {
        if (token.IsSection()) {
            if (!values.Empty()) {
                sections.Set(current_section, values);
                values.Clear();
            }
            current_section = token.Value();
            continue;
        }

        if (token.IsKeyProperty()) {
            auto k = token.Key();
            auto v = token.Value();
            values.Set(k, Value(v));
        }
    }
    sections.Set(current_section, values);

    if (sections.Empty()) {
        return std::nullopt;
    }

    return sections;

}

void Parser::SetPath(const std::filesystem::path &path) {
    _path = path;
}

Parser::Parser(std::filesystem::path path)
        : _path(std::move(path)) {}
