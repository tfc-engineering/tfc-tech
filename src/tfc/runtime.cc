#include "runtime.h"

#include "tfc/console/Console.h"
#include "tfc/command_line/CommandLineController.h"
#include "tfc/tools/Timer.h"

registerCLArg(i, tfc::PrimitiveType::String, "Input file to be executed.");
registerCLArg(lua, tfc::PrimitiveType::String, "Lua-commands to perform.");
registerCLArg(petsc,
              tfc::PrimitiveType::String,
              "PETSc arguments to pass along.");
registerCLArg(debug_delay,
              tfc::PrimitiveType::Integer,
              "Time in seconds to delay running the input file. (Useful for "
              "attaching debuggers).");

tfc::Log& TFC::log = tfc::Log::instance();
std::string TFC::input_file_name_;
std::string TFC::petsc_options_;
tfc::Timer TFC::program_timer_;

int TFC::mpi_id_ = 0;
int TFC::mpi_num_processes_ = 1;
MPI_Comm TFC::communicator_;

void TFC::initialize(int argc, char** argv, MPI_Comm communicator)
{
  MPI_Init(&argc, &argv);
  int comm_rank, comm_size;
  MPI_Comm_rank(communicator, &comm_rank);
  MPI_Comm_size(communicator, &comm_size);

  mpi_id_ = comm_rank;
  mpi_num_processes_ = comm_size;
  communicator_ = communicator;

  std::stringstream header;
  header << "\nTFC Runtime initialized:\n";
  header << "Number of MPI-processes = " << comm_size << "\n";

  TFC::log() << header.str();

  auto& cmdline_controller = tfc::CommandLineController::instance();
  cmdline_controller.assignCommandlineParameters(argc, argv);

  if (cmdline_controller.hasParam("i"))
  {
    const auto& param = cmdline_controller.getParam("i");
    input_file_name_ = param.value().getValue<std::string>();
  }

  std::string lua_commands;
  if (cmdline_controller.hasParam("lua"))
  {
    const auto& param = cmdline_controller.getParam("lua");
    lua_commands = param.value().getValue<std::string>();
  }

  if (cmdline_controller.hasParam("petsc"))
  {
    const auto& param = cmdline_controller.getParam("petsc");
    petsc_options_ = param.value().getValue<std::string>();
  }

  int debug_delay = 0;
  if (cmdline_controller.hasParam("debug_delay"))
  {
    const auto& param = cmdline_controller.getParam("debug_delay");
    debug_delay = param.value().getValue<int>();
  }

  tfc::Console::instance().loadRegisteredItems();

  if (debug_delay > 0)
  {
    TFC::log() << "Delaying " << debug_delay
               << " secs for attachment of a debugger";
    for (int t = 0; t < debug_delay; ++t)
    {
      tfc::Sleep(std::chrono::seconds(1));
      TFC::log() << debug_delay - t - 1 << " seconds";
    }
    MPI_Barrier(MPI_MainComm());
  }

  TFC::log() << "Executing lua commands and input file \"" << input_file_name_
             << "\"\n\n";
  tfc::Console::instance().performCommand(lua_commands);
  tfc::Console::instance().performCommand("dofile(\"" + input_file_name_ +
                                          "\");");
}

void TFC::finalize() { MPI_Finalize(); }

int TFC::MPI_ID() { return mpi_id_; }

int TFC::MPI_NumProcesses() { return mpi_num_processes_; }

MPI_Comm TFC::MPI_MainComm()
{
  return communicator_;
}
