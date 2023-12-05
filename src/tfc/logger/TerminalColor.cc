#include "TerminalColor.h"

namespace tfc
{

std::string TerminalColor(TerminalColorCode code)
{
  return std::string("\033[") + std::to_string(code) + "m";
}

} // namespace tfc