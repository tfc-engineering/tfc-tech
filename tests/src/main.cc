#include "tfc/runtime.h"

#include "tfc/console/Console.h"

int main(int argc, char** argv)
{
  TFC::initialize(argc, argv);

  auto& console = tfc::Console::instance();

  console.performCommand("tfc.test_Primitive()");

  TFC::finalize();
  return 0;
}