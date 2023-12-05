#include "runtime.h"

#include "tfc/console/Console.h"

tfc::Log& TFC::log = tfc::Log::instance();

int TFC::mpi_id_ = 0;
int TFC::mpi_num_processes_ = 1;

void TFC::initialize(int argc, char** argv, MPI_Comm communicator)
{
  MPI_Init(&argc, &argv);
  int comm_rank, comm_size;
  MPI_Comm_rank(communicator, &comm_rank);
  MPI_Comm_size(communicator, &comm_size);

  mpi_id_ = comm_rank;
  mpi_num_processes_ = comm_size;

  tfc::Console::instance().loadRegisteredItems();
}

void TFC::finalize() { MPI_Finalize(); }

int TFC::MPI_ID() { return mpi_id_; }

int TFC::MPI_NumProcesses() { return mpi_num_processes_; }
