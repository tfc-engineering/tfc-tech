#include "Log.h"

#include "tfc/runtime.h"

namespace tfc
{

// ###################################################################
Log& Log::instance()
{
  static Log singleton;
  return singleton;
}

LogStream Log::operator()(LogLevel level /*=Verbose_0*/)
{
  switch (level)
  {
    case LogLevel::Warning:
    {
      if (TFC::MPI_ID() == 0)
      {
        std::string header = "[" + std::to_string(TFC::MPI_ID()) + "]  ";
        header += TerminalColor(FG_YELLOW) + "**WARNING** ";
        return {&std::cout, header};
      }
      else
      {
        std::string header = " ";
        return {&dummy_stream_, header, true};
      }
    }
    case LogLevel::Error:
    {
      if (TFC::MPI_ID() == 0)
      {
        std::string header = "[" + std::to_string(TFC::MPI_ID()) + "]  ";
        header += TerminalColor(FG_RED) + "**!**ERROR**!** ";
        return {&std::cerr, header};
      }
      else
      {
        std::string header = " ";
        return {&dummy_stream_, header, true};
      }
    }
    case LogLevel::Verbose_0:
    {
      if (TFC::MPI_ID() == 0)
      {
        std::string header = "[" + std::to_string(TFC::MPI_ID()) + "]  ";
        return {&std::cout, header};
      }
      else
      {
        std::string header = " ";
        return {&dummy_stream_, header, true};
      }
    }

    case LogLevel::Verbose_1:
    {
      if ((TFC::MPI_ID() == 0) && (verbosity_ >= 1))
      {
        std::string header = "[" + std::to_string(TFC::MPI_ID()) + "]  ";
        header += TerminalColor(FG_CYAN);
        return {&std::cout, header};
      }
      else
      {
        std::string header = " ";
        return {&dummy_stream_, header, true};
      }
    }
    case LogLevel::Verbose_2:
    {
      if ((TFC::MPI_ID() == 0) && (verbosity_ >= 2))
      {
        std::string header = "[" + std::to_string(TFC::MPI_ID()) + "]  ";
        header += TerminalColor(FG_MAGENTA);
        return {&std::cout, header};
      }
      else
      {
        std::string header = " ";
        return {&dummy_stream_, header, true};
      }
    }
    case LogLevel::AllWarning:
    {
      std::string header = "[" + std::to_string(TFC::MPI_ID()) + "]  ";
      header += TerminalColor(FG_YELLOW) + "**WARNING** ";
      return {&std::cout, header};
    }
    case LogLevel::AllError:
    {
      std::string header = "[" + std::to_string(TFC::MPI_ID()) + "]  ";
      header += TerminalColor(FG_RED) + "**!**ERROR**!** ";
      return {&std::cerr, header};
    }
    case LogLevel::AllVerbose_0:
    {
      std::string header = "[" + std::to_string(TFC::MPI_ID()) + "]  ";
      return {&std::cout, header};
    }
    case LogLevel::AllVerbose_1:
    {
      if (verbosity_ >= 1)
      {
        std::string header = "[" + std::to_string(TFC::MPI_ID()) + "]  ";
        header += TerminalColor(FG_CYAN);
        return {&std::cout, header};
      }
      else
      {
        std::string header = " ";
        return {&dummy_stream_, header, true};
      }
    }
    case LogLevel::AllVerbose_2:
    {
      if (verbosity_ >= 2)
      {
        std::string header = "[" + std::to_string(TFC::MPI_ID()) + "]  ";
        header += TerminalColor(FG_MAGENTA);
        return {&std::cout, header};
      }
      else
      {
        std::string header = " ";
        return {&dummy_stream_, header, true};
      }
    }
    default:
      std::string header = " ";
      return {&dummy_stream_, header};
  }
}

} // namespace tfc
