#include <filesystem>
#include <iostream>

#include "IniParser/Parser.h"

int main()
{
  const std::filesystem::path filepath = "example.ini";
  Parser parser = Parser();

  // Parser checks if the path exists and that it is a file.
  std::optional<Result> parser_result = parser.parse(filepath);
  if (!parser_result.has_value())
  {
    std::cout << "Failed to parse the file: " << filepath.string() << '\n';
    return -1;
  }
  Result parsed_data = parser_result.value();

  // Iterates over all the sections in the file
  // section_key is the name of the section, for [Display] section, the name would be "Display".
  // section_values is another map, which contains key and a value for a given section.
  // If a file has a definition of value such as KeyExample=ValueExample
  // key would be equal to "KeyExample"
  // value would be equal to "ValueExample"
  // This way we can iterate over every single value that we got from the parser.
  for (auto const &[section_key, section_value] : parsed_data.data())
  {
    std::cout << "Section: " << section_key << std::endl;
    for (auto const &[key, value] : section_value.data())
    {
      std::cout << "\t[Key, Value]: "
                << "[" << key << ", " << value
                << "]" << std::endl;
    }
  }

  // This is an example of how to get a section values from the file
  // The section in this example is [Display]
  std::string name = "Display";
  // Just a sanity check.
  if (!parsed_data.contains(name))
  {
    std::cout << "Section '" << name << "' not found." << std::endl;
    return -1;
  }
  // The [Display] Section
  SectionValues section = parsed_data.get_value(name);

  // Example of how to get an exact key from the section
  std::string key = "fLightLODMaxStartFade";
  if (!section.contains(key))
  {
    std::cout << "Key '" << key << "' not found." << std::endl;
    return -1;
  }

  // Example of how to get every single key
  // Basically the same as the example for every section
  std::cout << "Section [" << name << "] data:" << std::endl;
  for (const auto &[k, v] : section.data())
  {
    std::cout << "[Key, Value]: "
              << "[" << k << ", " << v.to_string() << "]" << std::endl;
  }

  // The fLightLODMaxStartFade key, which can be then converted to the needed value, such as float/double.
  Value value = section.get_value(key);
  std::cout << key << " = " << value.to_f64() << std::endl;

  return 0;
}
