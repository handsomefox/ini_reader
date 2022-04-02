#include "Token.h"

Token::Token(TokenType type, std::string key, std::string value, std::string section)
        : type_(type), key_(std::move(key)), value_(std::move(value)), section_(std::move(section)) {}

Token::Token(TokenType type, std::string value)
        : type_(type), value_(std::move(value)) {}

Token
Token::new_key_property(TokenType type, const std::string &key, const std::string &value, const std::string &section) {
    return {type, key, value, section};
}

Token Token::new_section(TokenType type, const std::string &value) {
    return {type, value};
}


[[nodiscard]] bool Token::has_key() const {
    return type_ == TokenType::KeyProperty;
}

[[nodiscard]] bool Token::is_section() const {
    return type_ == TokenType::Section;
}


bool Token::is_key_property() const {
    return type_ == TokenType::KeyProperty;
}


[[nodiscard]] bool Token::is_comment() const {
    return type_ == TokenType::Comment;
}

[[nodiscard]] bool Token::inside_section() const {
    return section_.length() != 0;
}
