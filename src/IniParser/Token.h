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
  [[nodiscard]] Token::TokenType Type() const;

  // Returns the Token key.
  [[nodiscard]] std::string Key() const;

  // Returns the Token value.
  [[nodiscard]] std::string Value() const;

  // Returns whether the Token has a Key.
  [[nodiscard]] bool HasKey() const;

  // Returns whether the Token is a section.
  [[nodiscard]] bool IsSection() const;

  // Returns whether the Token is a comment (not useful for now).
  [[nodiscard]] bool IsComment() const;

  // Returns whether the Token is a KeyProperty.
  [[nodiscard]] bool IsKeyProperty() const;

  // Returns whether the Token is inside a section.
  [[nodiscard]] bool InsideOfSection() const;

private:
  Token() = default;

  TokenData _data;
};
