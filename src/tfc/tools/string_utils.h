#ifndef TFCTECH_STRING_UTILS_H
#define TFCTECH_STRING_UTILS_H

#include <string>
#include <vector>

namespace tfc
{

const std::string WHITESPACE = " \n\r\t\f\v";

/**Trims whitespace from the front of a string.*/
std::string StringLTrim(const std::string& s);

/**Trims whitespace from the back of a string.*/
std::string StringRTrim(const std::string& s);

/**Trims whitespace from the front and back of a string.*/
std::string StringTrim(const std::string& s);

/**Splits a string using the given delimiter. Consecutive delimiters
 * are treated as one.*/
std::vector<std::string> StringSplit(const std::string& input,
                                     const std::string& delim = " ");

/**The string portion, from the rear of the input string, up to
 * encountering the search_string.*/
std::string StringUpToFirstReverse(const std::string& input,
                                   const std::string& search_string);

} // namespace tfc

#endif // TFCTECH_STRING_UTILS_H
