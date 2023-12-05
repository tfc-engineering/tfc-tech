#include "Primitive.h"

#include "tfc/runtime.h"

#define NullError() TFCLogicalError("Routine not defined for type Null")

#define IllegalValue(x, y)                                                     \
  throw std::logic_error("Primitive data type " +                              \
                         PrimitiveTypeName(PrimitiveType::Boolean) +           \
                         " does not correspond to the required type, " +       \
                         PrimitiveTypeName(PrimitiveType::Integer))

namespace tfc
{

std::string PrimitiveTypeName(PrimitiveType type)
{
#pragma GCC diagnostic push
#pragma GCC diagnostic error "-Wswitch-enum"
  switch (type)
  {
    case PrimitiveType::Null:
      return "Null";
    case PrimitiveType::Boolean:
      return "Boolean";
    case PrimitiveType::Integer:
      return "Integer";
    case PrimitiveType::Float:
      return "Float";
    case PrimitiveType::String:
      return "String";
  }
#pragma GCC diagnostic push
  TFCLogicalError("Unhandled type");
}

Primitive::Primitive() : value_(std::make_unique<Primitive::TypeBase>()) {}

Primitive::Primitive(const std::string& value)
  : value_(std::make_unique<Primitive::TypeVariant<std::string>>(value))
{
}
Primitive::Primitive(const char* value)
  : value_(
      std::make_unique<Primitive::TypeVariant<std::string>>(std::string(value)))
{
}

Primitive::Primitive(const tfc::Primitive& other)
{
  value_ = other.value_->clone();
}

Primitive::Primitive(tfc::Primitive&& other) noexcept :
value_(std::move(other.value_))
{}

Primitive& Primitive::operator=(const tfc::Primitive& other)
{
  value_ = other.value_->clone();

  return *this;
}

PrimitiveType Primitive::type() const { return value_->Type(); }

void Primitive::checkTypeMatch(const PrimitiveType type_A,
                               const PrimitiveType type_B_required) const
{
  if (type_A != type_B_required)
    throw std::logic_error("Primitive data type " + PrimitiveTypeName(type()) +
                           " does not "
                           "correspond to the required type, " +
                           PrimitiveTypeName(type_B_required));
}

void Primitive::typeNotAvailable(PrimitiveType unavailable_type) const
{
  throw std::logic_error("Primitive data type " + PrimitiveTypeName(type()) +
                         " cannot produce data type " +
                         PrimitiveTypeName(unavailable_type));
}

std::string Primitive::str() const
{
#pragma GCC diagnostic push
#pragma GCC diagnostic error "-Wswitch-enum"
  switch (type())
  {
    case PrimitiveType::Null:
      return "Null";
    case PrimitiveType::Boolean:
      return std::string(value_->booleanValue() ? "true" : "false");
    case PrimitiveType::Integer:
      return std::to_string(value_->integerValue());
    case PrimitiveType::Float:
      return std::to_string(value_->floatValue());
    case PrimitiveType::String:
      return value_->stringValue();
  }
#pragma GCC diagnostic push
  TFCLogicalError("Unhandled type");
}

// ##################################################################
// TypeBase
Primitive::TypeBase::TypeBase(tfc::PrimitiveType type) : type_(type) {}

PrimitiveType Primitive::TypeBase::Type() const { return type_; }

bool Primitive::TypeBase::booleanValue() const { NullError(); }

int64_t Primitive::TypeBase::integerValue() const { NullError(); }

double Primitive::TypeBase::floatValue() const { NullError(); }

std::string Primitive::TypeBase::stringValue() const { NullError(); }

bool Primitive::TypeBase::operator==(const tfc::Primitive::TypeBase& that) const
{
  return this->Type() == that.Type();
}

bool Primitive::TypeBase::operator!=(const tfc::Primitive::TypeBase& that) const
{
  return not((*this) == that);
}

bool Primitive::TypeBase::operator>=(const tfc::Primitive::TypeBase& that) const
{
  return (*this) == that or (*this) > that;
}

bool Primitive::TypeBase::operator<=(const tfc::Primitive::TypeBase& that) const
{
  return (*this) == that or (*this) < that;
}

std::unique_ptr<Primitive::TypeBase> Primitive::TypeBase::clone() const
{
  return std::make_unique<TypeBase>();
}

// ##################################################################
// TypeVariant bool
// The only valid return type is bool
template <>
bool Primitive::TypeVariant<bool>::booleanValue() const
{
  return value_;
}
template <>
int64_t Primitive::TypeVariant<bool>::integerValue() const
{
  IllegalValue(PrimitiveType::Boolean, PrimitiveType::Integer);
}
template <>
double Primitive::TypeVariant<bool>::floatValue() const
{
  IllegalValue(PrimitiveType::Boolean, PrimitiveType::Float);
}
template <>
std::string Primitive::TypeVariant<bool>::stringValue() const
{
  IllegalValue(PrimitiveType::Boolean, PrimitiveType::String);
}
// ##################################################################
// TypeVariant integer
// The integer type can return an integer or a float.
template <>
bool Primitive::TypeVariant<int64_t>::booleanValue() const
{
  IllegalValue(PrimitiveType::Integer, PrimitiveType::Boolean);
}
template <>
int64_t Primitive::TypeVariant<int64_t>::integerValue() const
{
  return value_;
}
template <>
double Primitive::TypeVariant<int64_t>::floatValue() const
{
  return static_cast<double>(value_);
}
template <>
std::string Primitive::TypeVariant<int64_t>::stringValue() const
{
  IllegalValue(PrimitiveType::Integer, PrimitiveType::String);
}
// ##################################################################
// TypeVariant float
// The float type can return an integer or a float.
template <>
bool Primitive::TypeVariant<double>::booleanValue() const
{
  IllegalValue(PrimitiveType::Float, PrimitiveType::Boolean);
}
template <>
int64_t Primitive::TypeVariant<double>::integerValue() const
{
  return static_cast<int64_t>(std::round(value_));
}
template <>
double Primitive::TypeVariant<double>::floatValue() const
{
  return value_;
}
template <>
std::string Primitive::TypeVariant<double>::stringValue() const
{
  IllegalValue(PrimitiveType::Float, PrimitiveType::String);
}
// ##################################################################
// TypeVariant string
// The string type can only return a string
template <>
bool Primitive::TypeVariant<std::string>::booleanValue() const
{
  IllegalValue(PrimitiveType::String, PrimitiveType::Boolean);
}
template <>
int64_t Primitive::TypeVariant<std::string>::integerValue() const
{
  IllegalValue(PrimitiveType::String, PrimitiveType::Integer);
}
template <>
double Primitive::TypeVariant<std::string>::floatValue() const
{
  IllegalValue(PrimitiveType::String, PrimitiveType::Float);
}
template <>
std::string Primitive::TypeVariant<std::string>::stringValue() const
{
  return value_;
}

} // namespace tfc

std::ostream& operator<<(std::ostream& outstr, const tfc::Primitive& value)
{
  outstr << value.str();
  return outstr;
}