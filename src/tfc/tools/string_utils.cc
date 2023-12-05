#include "string_utils.h"

namespace tfc
{

// #################################################################
std::string stringLTrim(const std::string& s)
{
  size_t start = s.find_first_not_of(WHITESPACE);
  return (start == std::string::npos) ? "" : s.substr(start);
}

// #################################################################
std::string stringRTrim(const std::string& s)
{
  size_t end = s.find_last_not_of(WHITESPACE);
  return (end == std::string::npos) ? "" : s.substr(0, end + 1);
}

// #################################################################
std::string stringTrim(const std::string& s)
{
  return stringRTrim(stringLTrim(s));
}

// #################################################################
std::vector<std::string> stringSplit(const std::string& input,
                                     const std::string& delim /*=" "*/)
{
  constexpr size_t NPOS = std::string::npos;
  std::vector<std::string> output;

  std::string remainder = input;
  size_t first_scope = remainder.find_first_of(delim);

  while (first_scope != NPOS)
  {
    if (first_scope != 0) output.push_back(remainder.substr(0, first_scope));

    remainder = remainder.substr(first_scope + delim.size(), NPOS);
    first_scope = remainder.find_first_of(delim);
  }
  output.push_back(remainder);

  return output;
}

// #################################################################
std::string stringUpToFirstReverse(const std::string& input,
                                   const std::string& search_string)
{
  constexpr size_t NPOS = std::string::npos;
  std::string output = input;
  const size_t last_scope = input.find_last_of(search_string);
  if (last_scope != NPOS)
    output = input.substr(last_scope + search_string.size(), NPOS);

  return output;
}

// ##################################################################
bool stringIsBoolean(const std::string& input)
{
  return input == "true" or input == "false";
}

// ##################################################################
bool stringIsNumber(const std::string& input)
{
  if (input.empty()) return false;
  try {
    const double val = std::stod(input);
  }
  catch (const std::exception& e)
  {
    return false;
  }
  return true;
}

bool stringIsInteger(const std::string& input)
{
  if (input.empty()) return false;

  if (not stringIsNumber(input))
    return false;

  if (input.find_first_of("eE.") != std::string::npos)
    return false;

  return true;
}

bool stringIsFloat(const std::string& input)
{
  if (input.empty()) return false;

  if (not stringIsNumber(input))
    return false;

  if (input.find_first_of("eE.") == std::string::npos)
    return false;

  return true;
}

} // namespace tfc