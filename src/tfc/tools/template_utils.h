#ifndef TFCTECH_TEMPLATE_UTILS_H
#define TFCTECH_TEMPLATE_UTILS_H

#include <type_traits>
#include <string>

namespace tfc
{

template <typename T>
struct IsBool
{
  static constexpr bool value = std::is_same_v<T, bool>;
};
template <typename T>
struct IsInteger
{
  static constexpr bool value =
    std::is_integral_v<T> and not std::is_same_v<T, bool>;
};
template <typename T>
struct IsFloat
{
  static constexpr bool value = std::is_floating_point_v<T>;
};
template <typename T>
struct IsString
{
  static constexpr bool value =
    std::is_same_v<T, std::string> or std::is_same_v<T, char*>;
};

template <typename T>
struct IsSignedInteger
{
  static constexpr bool value = std::is_integral_v<T> and
                                std::is_signed_v<T> and
                                not std::is_same_v<T, bool>;
};
template <typename T>
struct IsUnsignedInteger
{
  static constexpr bool value = std::is_integral_v<T> and
                                std::is_unsigned_v<T> and
                                not std::is_same_v<T, bool>;
};

template <typename T>
using BoolType = typename std::enable_if_t<IsBool<T>::value, T>;
template <typename T>
using FloatType = typename std::enable_if_t<IsFloat<T>::value, T>;
template <typename T>
using IntegerType = typename std::enable_if_t<IsInteger<T>::value, T>;

template <typename T>
using StringType = typename std::enable_if_t<IsString<T>::value, T>;
template <typename T>
using SignedIntegerType =
  typename std::enable_if_t<IsSignedInteger<T>::value, T>;
template <typename T>
using UnsignedIntegerType =
  typename std::enable_if_t<IsUnsignedInteger<T>::value, T>;

template <typename T>
using BoolStorageType = typename std::enable_if_t<IsBool<T>::value, bool>;
template <typename T>
using FloatStorageType = typename std::enable_if_t<IsFloat<T>::value, double>;
template <typename T>
using IntegerStorageType =
  typename std::enable_if_t<IsInteger<T>::value, int64_t>;

template <typename T>
BoolStorageType<T> CastValue(const T& value)
{
  return value;
}

template <typename T>
FloatStorageType<T> CastValue(const T& value)
{
  return static_cast<double>(value);
}

template <typename T>
IntegerStorageType<T> CastValue(const T& value)
{
  return static_cast<int64_t>(value);
}

} // namespace tfc

#endif // TFCTECH_TEMPLATE_UTILS_H
