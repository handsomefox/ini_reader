#include "Parser.h"
#include "Utils.h"

#include <fstream>
#include <utility>

// Parses a line with a section
static inline Token ParseSection(std::string const &line, std::string &section)
{
  std::string value;
  for (auto const &c : line)
  {
    if (c == '[' || c == ']')
      continue;
    if (c == '#' || c == ';')
      break;

    value += c;
  }
  section = value;

  Token::TokenData token_data;
  token_data.type = Token::TokenType::Section;
  token_data.value = value;

  return Token(token_data);
}

// Parses a line with a key property.
static inline Token ParseKeyProperty(std::string const &line, std::string &section)
{
  bool key = true;
  std::string k, v;
  for (auto const &c : line)
  {
    if (c == '#' || c == ';')
      break;

    if (c == '=')
    {
      key = false;
      continue;
    }
    if (key)
      k += c;
    else
      v += c;
  }

  Token::TokenData tokenData;
  tokenData.type = Token::TokenType::KeyProperty;
  tokenData.key = k;
  tokenData.value = v;
  tokenData.section = section;

  return Token(tokenData);
}

// Returns an std::vector<Token> created from the file.
static inline std::vector<Token> Tokenize(std::filesystem::path const &path)
{
  std::stringstream ss = path_to_stringstream(path);
  std::vector<std::string> lines = extract_lines(ss);

  std::vector<Token> tokens;
  std::string section;

  for (auto const &line : lines)
  {
    if (line.empty())
      continue;
    if (starts_with(line, '#') || starts_with(line, ';'))
      continue;

    if (starts_with(line, '['))
    {
      auto token = ParseSection(line, section);
      tokens.emplace_back(token);
    }
    else if (contains(line, '='))
    {
      auto token = ParseKeyProperty(line, section);
      tokens.emplace_back(token);
    }
  }
  return tokens;
}

std::optional<Result> Parser::parse()
{
  if (_path.empty())
    return std::nullopt;

  std::vector<Token> tokens = Tokenize(_path);
  if (tokens.empty())
    return std::nullopt;

  std::string current_section = "KEY_NOT_FOUND";
  SectionValues values;
  auto sections = Result::_map();

  for (auto const &token : tokens)
  {
    using tt = Token::TokenType;
    switch (token.type())
    {
    default:
    case tt::None:
    case tt::Comment:
      break;

    case tt::Section:
      if (!values.is_empty())
      {
        sections[current_section] = values;
        values.clear();
      }
      current_section = token.value();
      break;

    case tt::KeyProperty:
      auto k = token.key();
      auto v = token.value();
      values.set_value(k, Value(v));
      break;
    }
  }
  sections[current_section] = values;

  if (sections.empty())
    return std::nullopt;

  return Result(sections);
}

std::optional<Result> Parser::parse(std::filesystem::path const &path)
{
  if (!exists(path) || std::filesystem::is_directory(path))
    return std::nullopt;

  this->_path = path;
  return this->parse();
}
