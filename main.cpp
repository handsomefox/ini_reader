#include <filesystem>
#include <iostream>

#include "Parser.h"

int main()
{
  const std::filesystem::path filepath = "example.ini";
  if (!exists(filepath))
  {
    return -1;
  }

  Parser parser = Parser(filepath);

  std::optional<Result> optional = parser.Parse();
  if (!optional.has_value())
  {
    std::cout << "Failed to parse the file: " << filepath.string() << '\n';
    return -1;
  }
  Result parsed = optional.value();

  for (auto const &[k, v] : parsed.Data())
  {
    std::cout << "Section: " << k << std::endl;
    for (auto const &[k2, v2] : v.Data())
    {
      std::cout << "    [Key, Value]: "
                << "[" << k2 << ", " << v2
                << "]" << std::endl;
    }
  }

  std::string name = "Display";
  if (!parsed.Exists(name))
  {
    std::cout << "Section '" << name << "' not found." << std::endl;
    return -1;
  }
  SectionValues section = parsed.Get(name);

  std::string key = "fLightLODMaxStartFade";
  if (!section.Exists(key))
  {
    std::cout << "Key '" << key << "' not found." << std::endl;
    return -1;
  }

  Value value = section.Get(key);
  std::cout << key << " = " << value.ToDouble() << std::endl;

  return 0;
}
