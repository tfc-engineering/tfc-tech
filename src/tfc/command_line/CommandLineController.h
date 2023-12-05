#ifndef TFCTECH_COMMANDLINECONTROLLER_H
#define TFCTECH_COMMANDLINECONTROLLER_H

#include "CommandLineParameter.h"

#include <map>

#define registerCLArg(identifier, type, doc_string)                            \
  static char JoinWords(unique_var_name_clarg_v##identifier##_, __COUNTER__) = \
    tfc::CommandLineController::addCommandLineParameter(                        \
      tfc::CommandLineParameter(#identifier, type, doc_string))

namespace tfc
{

class CommandLineController
{
public:
  /**Deleted copy constructor.*/
  CommandLineController(const CommandLineController&) = delete;
  /**Deleted move constructor.*/
  CommandLineController(CommandLineController&&) = delete;

  /**Returns the singleton instance.*/
  static CommandLineController& instance();

  /**Adds a command line parameter. This method is meant to be called during
  * static initialization.*/
  static char addCommandLineParameter(tfc::CommandLineParameter param);

  /**Assigns the command line parameters from program arguments.*/
  void assignCommandlineParameters(int argc, char** argv);

  /**Determines if the command line parameter was assigned.*/
  bool hasParam(const std::string& identifier);

  /**Returns the parameter with the given identifier.*/
  const CommandLineParameter& getParam(const std::string& identifier) const;

private:
  CommandLineController() = default;
  std::map<std::string, tfc::CommandLineParameter> command_line_params_;
};

} // namespace tfc

#endif // TFCTECH_COMMANDLINECONTROLLER_H
