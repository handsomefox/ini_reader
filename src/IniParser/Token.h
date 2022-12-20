#pragma once

#include <string>

// Token represents possible tokens when parsing .ini file.
class Token
{
public:
  // TokenType describes possible token types.
  enum class TokenType
  {
    None,
    KeyProperty,
    Section,
    Comment,
  };

  // TokenData is the data required for the tokens.
  struct TokenData
  {
    TokenType type;
    std::string key;
    std::string value;
    std::string section;
  };

  // Creates a token from the TokenData struct.
  explicit Token(TokenData);

  // Returns the Token type.
  [[nodiscard]] Token::TokenType type() const;

  // Returns the Token key.
  [[nodiscard]] std::string key() const;

  // Returns the Token value.
  [[nodiscard]] std::string value() const;

  // Returns whether the Token has a Key.
  [[nodiscard]] bool has_key() const;

  // Returns whether the Token is a section.
  [[nodiscard]] bool is_section() const;

  // Returns whether the Token is a comment (not useful for now).
  [[nodiscard]] bool is_comment() const;

  // Returns whether the Token is a KeyProperty.
  [[nodiscard]] bool is_keyproperty() const;

  // Returns whether the Token is inside a section.
  [[nodiscard]] bool is_inside_of_section() const;

private:
  Token() = default;

  TokenData _data;
};
