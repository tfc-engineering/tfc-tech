#ifndef TFCTECH_LOGSTREAM_H
#define TFCTECH_LOGSTREAM_H

#include <sstream>
#include "TerminalColor.h"

namespace tfc
{

/** Log stream for adding header information to a string stream.*/
class LogStream : public std::stringstream
{
private:
  std::ostream* log_stream_;
  std::string log_header_;
  const bool dummy_ = false;

public:
  /** Creates a string stream.*/
  LogStream(std::ostream* output_stream,
            std::string header,
            bool dummy_flag = false)
    : log_stream_(output_stream),
      log_header_(std::move(header)),
      dummy_(dummy_flag)
  {
  }

  /** Flushes the broken-up/headered stream to the output.*/
  ~LogStream() override
  {
    if (dummy_) return;

    std::string line, oline;
    while (std::getline(*this, line))
      oline += log_header_ + line + '\n' + TerminalColor(RESET);

    if (!oline.empty()) *log_stream_ << oline << std::flush;
  }

  LogStream(const LogStream& other)
  {
    log_stream_ = other.log_stream_;
    log_header_ = other.log_header_;
  }
};

/**Structure to throw away text if needed.*/
struct DummyStream : public std::ostream
{
  struct DummyStreamBuffer : std::streambuf
  {
    int overflow(int c) override { return c; };
  } buffer;

  DummyStream() : std::ostream(&buffer) {}

  ~DummyStream() override = default;
};

}

#endif // TFCTECH_LOGSTREAM_H
