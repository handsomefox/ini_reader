#include "Token.h"

#include <utility>

Token::Token(Token::TokenData data)
        : _data(std::move(data)) {
}

Token::TokenType Token::Type() const {
    return _data.type;
}

std::string Token::Key() const {
    return _data.key;
}

std::string Token::Value() const {
    return _data.value;
}

[[nodiscard]] bool Token::HasKey() const {
    return _data.type == TokenType::KeyProperty;
}

[[nodiscard]] bool Token::IsSection() const {
    return _data.type == TokenType::Section;
}


bool Token::IsKeyProperty() const {
    return _data.type == TokenType::KeyProperty;
}


[[nodiscard]] bool Token::IsComment() const {
    return _data.type == TokenType::Comment;
}

[[nodiscard]] bool Token::InsideOfSection() const {
    return _data.section.length() != 0;
}
