#include "Token.h"

#include <utility>

Token::Token(Token::TokenData data) : _data(std::move(data)) {}

Token::TokenType Token::type() const
{
  return _data.type;
}

std::string Token::key() const
{
  return _data.key;
}

std::string Token::value() const
{
  return _data.value;
}

[[nodiscard]] bool Token::has_key() const
{
  return _data.type == TokenType::KeyProperty;
}

[[nodiscard]] bool Token::is_section() const
{
  return _data.type == TokenType::Section;
}

bool Token::is_keyproperty() const
{
  return _data.type == TokenType::KeyProperty;
}

[[nodiscard]] bool Token::is_comment() const
{
  return _data.type == TokenType::Comment;
}

[[nodiscard]] bool Token::is_inside_of_section() const
{
  return _data.section.length() != 0;
}
