#include "Console.h"

#include "tfc/tools/string_utils.h"

#include <stdexcept>
#include <iostream>

namespace tfc
{

// ##################################################################
Console::Console() noexcept { console_state_ = luaL_newstate(); }

// ##################################################################
Console& Console::instance()
{
  static Console singleton;
  return singleton;
}

// ##################################################################
lua_State* Console::state() { return console_state_; }

// ##################################################################
char Console::addLuaCFunctionToRegistry(lua_CFunction function_ptr,
                                        const std::string& namespace_name,
                                        const std::string& function_name)
{
  auto& console = Console::instance();

  const std::string full_name = namespace_name + "::" + function_name;

  if (console.lua_c_function_registry_.count(full_name))
    throw std::logic_error("Attempting to register the lua_CFunction \"" +
                           full_name +
                           "\", however, a register-entry for it "
                           "already exists.");

  console.lua_c_function_registry_.insert(
    std::make_pair(full_name, function_ptr));

  return 0;
}

// ##################################################################
void Console::loadRegisteredItems()
{
  //=================================== Initializing console
  auto& L = console_state_;

  luaL_openlibs(L);

  //=================================== Register version
  // lua_pushstring(L, PROJECT_VERSION);      lua_setglobal(L,"chi_version");
  // lua_pushinteger(L,PROJECT_MAJOR_VERSION);lua_setglobal(L,"chi_major_version");
  // lua_pushinteger(L,PROJECT_MINOR_VERSION);lua_setglobal(L,"chi_minor_version");
  // lua_pushinteger(L,PROJECT_PATCH_VERSION);lua_setglobal(L,"chi_patch_version");

  //=================================== Registering functions
  for (const auto& [full_name, function_ptr] : lua_c_function_registry_)
  {
    const std::string function_name = StringUpToFirstReverse(full_name, ":");
    const auto namespace_names = StringSplit(full_name, "::");

    fleshOutLuaTableStructure(namespace_names,
                              /*pop_last=*/namespace_names.size() > 1);

    lua_pushstring(L, function_name.c_str());
    lua_pushcfunction(L, function_ptr);
    lua_settable(L, -3);
  }
}

// ##################################################################
/**Fleshes out a path in a table tree. For example, given
 * "fee::foo::fah::koo, this routine will make sure that
 * fee.foo.fah.koo is defined as a table tree structure. The routine will
 * create a table structure where one is needed and leave existing ones alone.
 *
 * At the end of the routine the last table in the structure will be on top
 * of the stack.*/
void Console::fleshOutLuaTableStructure(
  const std::vector<std::string>& table_names, bool pop_last)
{
  auto real_table_names = table_names;
  if (pop_last) real_table_names.pop_back();
  auto L = console_state_;

  for (const auto& table_name : real_table_names)
  {
    // The first entry needs to be in lua's global scope,
    // so it looks a little different
    if (table_name == table_names.front())
    {
      lua_getglobal(L, table_name.c_str());
      if (not lua_istable(L, -1))
      {
        lua_pop(L, 1);
        lua_newtable(L);
        lua_setglobal(L, table_name.c_str());
        lua_getglobal(L, table_name.c_str());
      }
    }
    else
    {
      lua_getfield(L, -1, table_name.c_str());
      if (not lua_istable(L, -1))
      {
        lua_pop(L, 1);
        lua_pushstring(L, table_name.c_str());
        lua_newtable(L);
        lua_settable(L, -3);
        lua_getfield(L, -1, table_name.c_str());
      }
    }
  } // for table_key in table_keys

  // do not lua_pop here
}

bool Console::performCommand(const std::string& command_string)
{
  auto& L = console_state_;
  bool error = luaL_dostring(L, command_string.c_str());
  if (error)
  {
    std::cout << lua_tostring(L, -1) << "\n";
    lua_pop(L, lua_gettop(L));
    return false;
  }

  return true;
}

} // namespace tfc