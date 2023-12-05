#include "tfc/runtime.h"

int main(int argc, char** argv)
{
  TFC::initialize(argc, argv);

  TFC::finalize();
  return 0;
}
