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
    {
      continue;
    }

    if (c == '#' || c == ';')
    {
      break;
    }

    value += c;
  }
  section = value;

  Token::TokenData tokenData{};
  tokenData.type = Token::TokenType::Section;
  tokenData.value = value;

  return Token(tokenData);
}

// Parses a line with a key property.
static inline Token ParseKeyProperty(std::string const &line, std::string &section)
{
  bool key = true;
  std::string k{}, v{};

  for (auto const &c : line)
  {
    if (c == '#' || c == ';')
    {
      break;
    }

    if (c == '=')
    {
      key = false;
      continue;
    }

    if (key)
    {
      k += c;
    }
    else
    {
      v += c;
    }
  }

  Token::TokenData tokenData{};
  tokenData.type = Token::TokenType::KeyProperty;
  tokenData.key = k;
  tokenData.value = v;
  tokenData.section = section;

  return Token(tokenData);
}

// Returns an std::vector<Token> created from the file.
static inline std::vector<Token> Tokenize(std::filesystem::path const &path)
{
  std::stringstream ss = fileToSs(path);
  std::vector<std::string> lines = extractLines(ss);

  std::vector<Token> tokens{};
  std::string section{};

  for (auto const &line : lines)
  {
    if (line.empty())
    {
      continue;
    }

    if (startsWith(line, '#') || startsWith(line, ';'))
    {
      continue;
    }

    if (startsWith(line, '['))
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

std::optional<Result> Parser::Parse()
{
  if (_path.empty())
  {
    _error_message = "Path: " + _path.string() + " is empty.";
    return std::nullopt;
  }

  std::vector<Token> tokens = Tokenize(_path);

  if (tokens.empty())
  {
    _error_message = "File: " + _path.string() + " is not a valid .ini file.";
    return std::nullopt;
  }

  std::string current_section = DEFAULT_KEY;
  Result sections;
  SectionValues values;

  for (auto const &token : tokens)
  {
    using tt = Token::TokenType;
    switch (token.Type())
    {
    default:
    case tt::None:
    case tt::Comment:
      break;

    case tt::Section:
      if (!values.Empty())
      {
        sections.Set(current_section, values);
        values.Clear();
      }
      current_section = token.Value();
      break;

    case tt::KeyProperty:
      auto k = token.Key();
      auto v = token.Value();
      values.Set(k, Value(v));
      break;
    }
  }
  sections.Set(current_section, values);

  if (sections.Empty())
  {
    return std::nullopt;
  }

  return sections;
}

void Parser::SetPath(const std::filesystem::path &path)
{
  _path = path;
}

std::optional<Result> Parser::Parse(std::filesystem::path const &path)
{
  _error_message.clear();
  if (!exists(path))
  {
    _error_message = "File: " + path.string() + " does not exist.";
    return std::nullopt;
  }

  if (std::filesystem::is_directory(path))
  {
    _error_message = "Path: " + path.string() + " is a directory.";
    return std::nullopt;
  }

  this->SetPath(path);
  return this->Parse();
}

std::string Parser::Error()
{
  // FIXME: Maybe return an error as an enum value is instead.
  if (_error_message.empty())
  {
    return "None";
  }

  auto msg = _error_message;
  _error_message.clear();
  return msg;
}
