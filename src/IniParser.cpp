#include "IniParser.h"

std::stringstream IniParser::rd_file_to_ss(const std::filesystem::path &fpath) {
    std::ifstream ifs(fpath);
    std::stringstream buf;
    buf << ifs.rdbuf();
    return buf;
}

std::vector<std::string> IniParser::extract_lines(std::stringstream &ss) {
    std::vector<std::string> vec;
    std::string line;
    while (std::getline(ss, line, '\n')) {
        vec.push_back(line);
    }
    return vec;
}

bool IniParser::starts_with(const std::string &str, const char c) {
    if (str.length() == 0)
        return false;

    return str[0] == c;
}

bool IniParser::ends_with(const std::string &str, const char c) {
    if (str.length() == 0)
        return false;

    return str[str.length() - 1] == c;
}

bool IniParser::contains(const std::string &str, const char c) {
    return str.find(c) != std::string::npos;
}

std::vector<Token> IniParser::parse(std::filesystem::path const &path) {
    auto ss = rd_file_to_ss(path);
    auto vec = extract_lines(ss);

    std::vector<Token> tokens;
    std::string section;

    auto for_section = [&](std::string const &line) {
        std::string value;

        for (auto const &c: line) {
            if (c == '[' || c == ']')
                continue;

            if (c == '#')
                break;

            value += c;
        }
        section = value;
        tokens.emplace_back(Token::new_section(TokenType::Section, value));
    };

    auto for_key_property = [&](std::string const &line) {
        bool key = true;
        std::string k, v;
        for (auto const &c: line) {
            if (c == ' ') continue;
            if (c == '#') break;
            if (c == '=') {
                key = false;
                continue;
            }

            if (key) k += c;
            else v += c;
        }
        tokens.emplace_back(Token::new_key_property(TokenType::KeyProperty, k, v, section));
    };

    for (auto const &line: vec) {
        if (line.empty())
            continue;

        if (starts_with(line, '#'))
            continue;

        if (starts_with(line, '['))
            for_section(line);

        if (contains(line, '='))
            for_key_property(line);
    }
    return tokens;
}
