#ifndef TFCTECH_RUNTIME_H
#define TFCTECH_RUNTIME_H

#include "tfc/logger/Log.h"

#include <mpi.h>
#include <vector>
#include <map>

namespace tfc
{
class Timer;
}

class TFC
{
public:
  static void
  initialize(int argc, char** argv, MPI_Comm communicator = MPI_COMM_WORLD);
  static void finalize();

  static int MPI_ID();
  static int MPI_NumProcesses();
  static MPI_Comm MPI_MainComm();

  static tfc::Log& log;

  static std::string input_file_name_;
  static std::string petsc_options_;
  static tfc::Timer program_timer_;

private:
  static int mpi_id_;
  static int mpi_num_processes_;
  static MPI_Comm communicator_;
};

#endif // TFCTECH_RUNTIME_H
