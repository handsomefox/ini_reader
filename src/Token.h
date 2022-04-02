#pragma once

#include <string>

enum class TokenType {
    None,
    KeyProperty,
    Section,
    Comment,
};

class Token {
public:
    // Creates a new Token object with parameters required for TokenType::KeyProperty.
    static Token new_key_property(TokenType, std::string const &, std::string const &, std::string const &);

    // Creates a new Token object with parameters required for TokenType::Section.
    static Token new_section(TokenType, std::string const &);

    // Returns the TokenType.
    [[nodiscard]] TokenType type() const { return type_; };

    // Returns the Token key.
    [[nodiscard]] std::string key() const { return key_; };

    // Returns the Token value.
    [[nodiscard]] std::string value() const { return value_; };

    // Returns whether the Token has a key.
    [[nodiscard]] bool has_key() const;

    // Returns whether the Token is a section.
    [[nodiscard]] bool is_section() const;

    // Returns whether the Token is a comment (not useful for now).
    [[nodiscard]] bool is_comment() const;

    // Returns whether the Token is a KeyProperty.
    [[nodiscard]] bool is_key_property() const;

    // Returns whether the Token is inside a section.
    [[nodiscard]] bool inside_section() const;


private:
    Token() = default;

    Token(TokenType type, std::string key, std::string value, std::string section);

    Token(TokenType type, std::string value);

    TokenType type_{TokenType::None};
    std::string key_, value_, section_;
};
