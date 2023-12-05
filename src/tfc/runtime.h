#ifndef TFCTECH_RUNTIME_H
#define TFCTECH_RUNTIME_H

#include "tfc/logger/Log.h"

#include <mpi.h>

class TFC
{
public:
  static void
  initialize(int argc, char** argv, MPI_Comm communicator = MPI_COMM_WORLD);
  static void finalize();

  static int MPI_ID();
  static int MPI_NumProcesses();

  static tfc::Log& log;

private:
  static int mpi_id_;
  static int mpi_num_processes_;
};

#endif // TFCTECH_RUNTIME_H
