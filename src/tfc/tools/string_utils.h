#ifndef TFCTECH_STRING_UTILS_H
#define TFCTECH_STRING_UTILS_H

#include <string>
#include <vector>

namespace tfc
{

static const std::string WHITESPACE = " \n\r\t\f\v";

/**Trims whitespace from the front of a string.*/
std::string stringLTrim(const std::string& s);

/**Trims whitespace from the back of a string.*/
std::string stringRTrim(const std::string& s);

/**Trims whitespace from the front and back of a string.*/
std::string stringTrim(const std::string& s);

/**Splits a string using the given delimiter. Consecutive delimiters
 * are treated as one.*/
std::vector<std::string> stringSplit(const std::string& input,
                                     const std::string& delim = " ");

/**The string portion, from the rear of the input string, up to
 * encountering the search_string.*/
std::string stringUpToFirstReverse(const std::string& input,
                                   const std::string& search_string);

/**Determines if a string is a boolean.*/
bool stringIsBoolean(const std::string& input);

/**Determines if a string is an integer.*/
bool stringIsInteger(const std::string& input);

/**Determines if a string is a floating point value*/
bool stringIsFloat(const std::string& input);

/**Determines if a string is a number.*/
bool stringIsNumber(const std::string& input);

} // namespace tfc

#endif // TFCTECH_STRING_UTILS_H
