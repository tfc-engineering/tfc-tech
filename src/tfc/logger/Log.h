#ifndef TFCTECH_LOG_H
#define TFCTECH_LOG_H

#include "LogStream.h"

#include <iostream>

namespace tfc
{

/**Logging levels used in the logger.*/
enum class LogLevel : int
{
  Warning = 1,      ///< Home location, Warning only for location 0
  Error = 2,        ///< Home location, Error only for location 0
  Verbose_0 = 3,    ///< Home location, Default verbosity level
  Verbose_1 = 4,    ///< Home location, Used only if verbosity level equals 1
  Verbose_2 = 5,    ///< Home location, Used only if verbosity level equals 2
  AllWarning = 6,   ///< All locations, Warning for any location
  AllError = 7,     ///< All locations, Error for any location
  AllVerbose_0 = 8, ///< All locations, Default verbosity level
  AllVerbose_1 = 9, ///< All locations, Used only if verbosity level equals 1
  AllVerbose_2 = 10 ///< All locations, Used only if verbosity level equals 2
};                  ///< Used only if verbosity level equals 2

/**Main log class.*/
class Log
{
public:
  /**Deleted copy constructor.*/
  Log(const Log&) = delete;
  /**Deleted move constructor.*/
  Log(Log&&) = delete;

  /**Returns the singleton instance*/
  static Log& instance();

  LogStream operator()(LogLevel level = LogLevel::Verbose_0);

private:
  /**Private constructor.*/
  Log() = default;
  DummyStream dummy_stream_;
  int verbosity_ = 0;
};

} // namespace tfc

#define TFCInvalidArgumentIf(condition, message)                               \
  if (condition)                                                               \
  throw std::invalid_argument(                                                 \
    std::string("TFC - ") + std::string(__PRETTY_FUNCTION__) + ": " + message)
#define TFCInvalidArgument(message)                                            \
  throw std::invalid_argument(                                                 \
    std::string("TFC - ") + std::string(__PRETTY_FUNCTION__) + ": " + message)

#define TFCLogicalErrorIf(condition, message)                                  \
  if (condition)                                                               \
  throw std::logic_error(std::string("TFC - ") +                               \
                         std::string(__PRETTY_FUNCTION__) + ": " + message)

#define TFCLogicalError(message)                                               \
  throw std::logic_error(std::string("TFC - ") +                               \
                         std::string(__PRETTY_FUNCTION__) + ": " + message)

#endif // TFCTECH_LOG_H
