#ifndef TFCTECH_PRIMITIVE_H
#define TFCTECH_PRIMITIVE_H

#include "tfc/tools/template_utils.h"

#include <memory>
#include <string>
#include <stdexcept>
#include <cmath>

namespace tfc
{

enum class PrimitiveType : int
{
  Null = 0,
  Boolean = 1,
  Integer = 2, // 64-bit integers (int64_t)
  Float = 3,   // 64-bit float (double)
  String = 4,
};

/**Returns the string name of a PrimitiveType enum.*/
std::string PrimitiveTypeName(PrimitiveType type);

/**A versatile primitive data-type.*/
class Primitive
{
public:
  /**Default constructor for a null value.*/
  Primitive();
  /**Constructor for bool, integer and float*/
  template <typename T>
  explicit Primitive(T value)
  {
    constexpr bool is_supported_type =
      IsBool<T>::value or IsFloat<T>::value or IsInteger<T>::value;
    static_assert(is_supported_type,
                  "Constructor called with unsupported type");

    value_ = constructorHelper(CastValue(value));
  }
  /**String constructor.*/
  explicit Primitive(const std::string& value);
  /**C-String constructor.*/
  explicit Primitive(const char* value);

  /**Copy constructor.*/
  Primitive(const Primitive& other);

  /**Move constructor.*/
  Primitive(Primitive&& other) noexcept;

  /**Assignment operator.*/
  Primitive& operator=(const Primitive& other);

  /**Arbitrary assignment operator.*/
  template <typename T>
  Primitive& operator=(T value)
  {
    *this = Primitive(value);
    return *this;
  }

  /**Makes a primitive value from a string.*/
  static Primitive makeFromString(const std::string& input);

  PrimitiveType type() const;

  /**Returns values of type bool if able.*/
  template <typename T>
  BoolType<T> getValue() const
  {
    checkTypeMatch(type(), PrimitiveType::Boolean);

    return value_->booleanValue();
  }

  /**Returns floating point values if able.*/
  template <typename T>
  FloatType<T> getValue() const
  {
    if (type() == PrimitiveType::Integer)
    {
      const int64_t value = value_->integerValue();
      return static_cast<T>(value);
    }
    else if (type() == PrimitiveType::Float)
    {
      const double value = value_->floatValue();
      return static_cast<T>(value);
    }
    else
      typeNotAvailable(PrimitiveType::Float);
    return 0.0;
  }

  /**Returns a string if able.*/
  template <typename T>
  StringType<T> getValue() const
  {
    checkTypeMatch(type(), PrimitiveType::String);

    return value_->stringValue();
  }

  /**Returns a signed integer if able.*/
  template <typename T>
  SignedIntegerType<T> getValue() const
  {
    if (type() == PrimitiveType::Integer)
    {
      const int64_t value = value_->integerValue();
      return static_cast<T>(value);
    }
    else if (type() == PrimitiveType::Float)
    {
      const double value = value_->floatValue();
      return static_cast<T>(std::round(value));
    }
    else
      typeNotAvailable(PrimitiveType::Integer);
    return 0;
  }

  /**Returns an unsigned integer if able.*/
  template <typename T>
  UnsignedIntegerType<T> getValue() const
  {
    if (type() == PrimitiveType::Integer)
    {
      const int64_t value = value_->integerValue();
      if (value < 0)
        throw std::logic_error(
          std::string(__PRETTY_FUNCTION__) +
          ": Attempt to cast negative number to unsigned.");
      return static_cast<T>(value);
    }
    else if (type() == PrimitiveType::Float)
    {
      const double value = value_->floatValue();
      if (value < 0)
        throw std::logic_error(
          std::string(__PRETTY_FUNCTION__) +
          ": Attempt to cast negative number to unsigned.");
      return static_cast<T>(std::round(value));
    }
    else
      typeNotAvailable(PrimitiveType::Integer);
    return 0;
  }

  /**Returns a string representation of the value.*/
  std::string str() const;

private:
  /**Checks if two VaryingDataType values match. type A is matched against
   * type B.*/
  void checkTypeMatch(const PrimitiveType type_A,
                      const PrimitiveType type_B_required) const;

  void typeNotAvailable(PrimitiveType unavailable_type) const;

  /**A typebase on which to template different types.*/
  class TypeBase
  {
  public:
    TypeBase(PrimitiveType type = PrimitiveType::Null);
    PrimitiveType Type() const;
    virtual bool booleanValue() const;
    virtual int64_t integerValue() const;
    virtual double floatValue() const;
    virtual std::string stringValue() const;

    virtual bool operator==(const TypeBase& that) const;
    virtual bool operator>(const TypeBase& that) const { return false; };
    virtual bool operator<(const TypeBase& that) const { return false; };
    bool operator!=(const TypeBase& that) const;
    bool operator>=(const TypeBase& that) const;
    bool operator<=(const TypeBase& that) const;

    virtual ~TypeBase() = default;

    virtual std::unique_ptr<TypeBase> clone() const;

  private:
    PrimitiveType type_;
  };

  /**Controlled variations.*/
  template <typename T>
  class TypeVariant : public TypeBase
  {
  public:
    explicit TypeVariant(T value)
      : Primitive::TypeBase(IsBool<T>::value      ? PrimitiveType::Boolean
                            : IsInteger<T>::value ? PrimitiveType::Integer
                            : IsFloat<T>::value   ? PrimitiveType::Float
                            : IsString<T>::value  ? PrimitiveType::String
                                                  : PrimitiveType::Null),
        value_(value)
    {
    }

    bool booleanValue() const override;
    int64_t integerValue() const override;
    double floatValue() const override;
    std::string stringValue() const override;

    bool operator==(const TypeBase& that) const override
    {
      switch (Type())
      {
        case PrimitiveType::Boolean:
          return booleanValue() == that.booleanValue();
        case PrimitiveType::Integer:
          return integerValue() == that.integerValue();
        case PrimitiveType::Float:
          return floatValue() == that.floatValue();
        case PrimitiveType::String:
          return stringValue() == that.stringValue();
        default:
          return false;
      }
    }
    bool operator>(const TypeBase& that) const override
    {
      switch (Type())
      {
        case PrimitiveType::Boolean:
          return booleanValue() > that.booleanValue();
        case PrimitiveType::Integer:
          return integerValue() > that.integerValue();
        case PrimitiveType::Float:
          return floatValue() > that.floatValue();
        case PrimitiveType::String:
          return stringValue() > that.stringValue();
        default:
          return false;
      }
    }
    bool operator<(const TypeBase& that) const override
    {
      switch (Type())
      {
        case PrimitiveType::Boolean:
          return booleanValue() < that.booleanValue();
        case PrimitiveType::Integer:
          return integerValue() < that.integerValue();
        case PrimitiveType::Float:
          return floatValue() < that.floatValue();
        case PrimitiveType::String:
          return stringValue() < that.stringValue();
        default:
          return false;
      }
    }

    std::unique_ptr<TypeBase> clone() const override
    {
      return std::make_unique<TypeVariant>(value_);
    }

  private:
    T value_;
  }; // class TypeVariant

  template <typename T>
  std::unique_ptr<TypeBase> constructorHelper(T value)
  {
    return std::make_unique<TypeVariant<T>>(value);
  }

  std::unique_ptr<TypeBase> value_;
};

} // namespace tfc

/**Stream operator*/
std::ostream& operator<<(std::ostream& outstr, const tfc::Primitive& value);

#endif // TFCTECH_PRIMITIVE_H
