#ifndef TFCTECH_COMMANDLINEPARAMETERS_H
#define TFCTECH_COMMANDLINEPARAMETERS_H

#include <vector>
#include <string>

namespace tfc
{

class CommandLineParameters
{
public:
  void AssignCommandLineArguments(int argc, char** argv);

private:
  std::vector<std::string> cli_commands_;
};

} // namespace tfc

#endif // TFCTECH_COMMANDLINEPARAMETERS_H
