#include "CommandLineController.h"

namespace tfc
{

CommandLineController& CommandLineController::instance()
{
  static CommandLineController singleton;
  return singleton;
}

char CommandLineController::addCommandLineParameter(
  tfc::CommandLineParameter param)
{
  auto& inst = CommandLineController::instance();
  const std::string id = param.identifier();
  TFCLogicalErrorIf(inst.command_line_params_.count(id) != 0,
                    "Command line parameter \"" + id +
                      "\" already registered.");

  inst.command_line_params_.insert(std::make_pair(id, param));

  return 0;
}

void CommandLineController::assignCommandlineParameters(int argc, char** argv)
{
  for (auto& [id, param] : command_line_params_)
    param.assignFromArray(argc, argv);
}

bool CommandLineController::hasParam(const std::string& identifier)
{
  auto it = command_line_params_.find(identifier);
  TFCLogicalErrorIf(it == command_line_params_.end(),
                    "CommmandLineParameter "
                    "\" " +
                      identifier + "\" not registered.");

  auto& param = it->second;
  return param.hasBeenSupplied();
}

const CommandLineParameter&
CommandLineController::getParam(const std::string& identifier) const
{
  auto it = command_line_params_.find(identifier);
  TFCLogicalErrorIf(it == command_line_params_.end(),
                    "CommmandLineParameter "
                    "\" " +
                      identifier + "\" not registered.");

  return it->second;
}

} // namespace tfc