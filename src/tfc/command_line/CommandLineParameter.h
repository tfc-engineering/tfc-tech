#ifndef TFCTECH_COMMANDLINEPARAMETER_H
#define TFCTECH_COMMANDLINEPARAMETER_H

#include "tfc/tools/Primitive.h"
#include "tfc/runtime.h"
#include "tfc/tools/macro_utils.h"

#include <string>

namespace tfc
{

class CommandLineParameter
{
public:
  /**Constructs a command line parameter with a specified type. All identifiers
   * will have a "-" prefixed so do not supply it.*/
  CommandLineParameter(const std::string& identifier,
                       PrimitiveType type,
                       const std::string& doc_string);

  PrimitiveType type() const;

  CommandLineParameter(const CommandLineParameter& other);

  const std::string& identifier() const;
  const Primitive& value() const;
  const std::string& docString() const;

  void assignFromArray(int argc, char** argv);

  bool hasBeenSupplied() const;

private:
  const std::string identifier_;
  Primitive value_;
  const std::string doc_string_;
  bool assigned_ = false;
};

} // namespace tfc

#endif // TFCTECH_COMMANDLINEPARAMETER_H
