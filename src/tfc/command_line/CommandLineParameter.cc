#include "CommandLineParameter.h"

#include "tfc/runtime.h"
#include "tfc/tools/string_utils.h"

#include <iomanip>

namespace tfc
{

CommandLineParameter::CommandLineParameter(const std::string& identifier,
                                           tfc::PrimitiveType type,
                                           const std::string& doc_string)
  : identifier_(identifier), doc_string_(doc_string)
{
  switch (type)
  {
    case PrimitiveType::Null:
      value_ = Primitive();
      break;
    case PrimitiveType::Boolean:
      value_ = false;
      break;
    case PrimitiveType::Integer:
      value_ = 0;
      break;
    case PrimitiveType::Float:
      value_ = 0.0;
      break;
    case PrimitiveType::String:
      value_ = "";
      break;
    default:
      value_ = Primitive();
  }
}

PrimitiveType CommandLineParameter::type() const { return value_.type(); }

CommandLineParameter::CommandLineParameter(
  const tfc::CommandLineParameter& other)
  : identifier_(other.identifier_),
    value_(other.value_),
    doc_string_(other.doc_string_)
{
}

const std::string& CommandLineParameter::identifier() const
{
  return identifier_;
}

const std::string& CommandLineParameter::docString() const
{
  return doc_string_;
}

const Primitive& CommandLineParameter::value() const { return value_; }

void CommandLineParameter::assignFromArray(int argc, char** argv)
{
  for (int c = 0; c < argc; ++c)
  {
    const std::string argv_str(argv[c]);
    if (argv_str == ("-" + identifier_))
    {
      TFCLogicalErrorIf(
        c + 1 >= argc,
        "Cannot process argument " + identifier_ +
          ". Requires to be followed by whitespace then a value.");
      const std::string value_str(argv[c + 1]);

      PrimitiveType argtype = PrimitiveType::String;
      if (stringIsBoolean(value_str)) argtype = PrimitiveType::Boolean;
      else if (stringIsInteger(value_str))
        argtype = PrimitiveType::Integer;
      else if (stringIsFloat(value_str))
        argtype = PrimitiveType::Float;

      if (argtype == value_.type())
      {
        value_ = Primitive::makeFromString(value_str);
        assigned_ = true;
        TFC::log() << "Parameter: " << std::setw(6) << ("-" + identifier_)
                   << " " << value_.str();
      }
    }
  }
}

bool CommandLineParameter::hasBeenSupplied() const { return assigned_; }

} // namespace tfc