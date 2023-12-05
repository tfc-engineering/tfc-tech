#include "tfc/runtime.h"
#include "tfc/console/Console.h"
#include "tfc/tools/Primitive.h"

#define TryCatchError(x)                                                       \
  try                                                                          \
  {                                                                            \
    x;                                                                         \
  }                                                                            \
  catch (const std::exception& e)                                              \
  {                                                                            \
    TFC::log(LogLevel::Warning) << e.what();                                   \
  }                                                                            \
  ++counter

namespace tfc
{

int test_Primitive(lua_State* L);
RegisterLuaCFunction(/*function*/ test_Primitive,
                     /*namespace*/ tfc,
                     /*function_name_in_lua*/ test_Primitive);

int test_Primitive(lua_State*)
{
  TFC::log() << __PRETTY_FUNCTION__ << "\n";

  size_t counter = 0; // this does nothing, just helps clang-format align

  //============================================= Null
  {
    Primitive p;

    TryCatchError(TFC::log() << p.getValue<bool>());
    TryCatchError(TFC::log() << p.getValue<int64_t>());
    TryCatchError(TFC::log() << p.getValue<double>());
    TryCatchError(TFC::log() << p.getValue<std::string>());

    TFC::log() << "p " << p.str();
  }
  {
    Primitive p(false);

    TryCatchError(TFC::log() << p.getValue<bool>());
    TryCatchError(TFC::log() << p.getValue<int64_t>());
    TryCatchError(TFC::log() << p.getValue<double>());
    TryCatchError(TFC::log() << p.getValue<std::string>());

    TFC::log() << "p " << p.str();
  }
  {
    Primitive p(123);

    TryCatchError(TFC::log() << p.getValue<bool>());
    TryCatchError(TFC::log() << p.getValue<int64_t>());
    TryCatchError(TFC::log() << p.getValue<double>());
    TryCatchError(TFC::log() << p.getValue<std::string>());

    TFC::log() << "p " << p.str();
  }
  {
    Primitive p(0.123);

    TryCatchError(TFC::log() << p.getValue<bool>());
    TryCatchError(TFC::log() << p.getValue<int64_t>());
    TryCatchError(TFC::log() << p.getValue<double>());
    TryCatchError(TFC::log() << p.getValue<std::string>());

    TFC::log() << "p " << p.str();
  }

  {
    Primitive p(12.123);

    TryCatchError(TFC::log() << p.getValue<size_t>());

    TFC::log() << "p " << p.str();
  }
  {
    Primitive p(-12.123);

    TryCatchError(TFC::log() << p.getValue<size_t>());

    TFC::log() << "p " << p.str();
  }
  {
    Primitive p("0.123");

    TryCatchError(TFC::log() << p.getValue<bool>());
    TryCatchError(TFC::log() << p.getValue<int64_t>());
    TryCatchError(TFC::log() << p.getValue<double>());
    TryCatchError(TFC::log() << p.getValue<std::string>());

    TFC::log() << "p " << p.str();
  }
  {
    Primitive p1(15);
    Primitive p2(12.213);
    TFC::log() << "p1 " << p1.str();
    TFC::log() << "p2 " << p2.str();
    p1 = p2;
    TFC::log() << "p1 " << p1.str();
  }

  {
    Primitive p;

    p = false;
    TFC::log() << "p " << p.str();
    p = 123;
    TFC::log() << "p " << p.str();
    p = 123.123;
    TFC::log() << "p " << p.str();
    p = "123.xxx";
    TFC::log() << "p " << p.str();
  }

  TFC::log() << counter;

  return 0;
}

} // namespace tfc