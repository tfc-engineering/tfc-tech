#ifndef TFCTECH_CONSOLE_H
#define TFCTECH_CONSOLE_H

#include "tfc/lua/lua.h"
#include "tfc/tools/macro_utils.h"

#include <map>
#include <string>
#include <vector>

#define RegisterLuaCFunction(function, namespace_name, func_name)              \
  static char JoinWords(unique_var_name_luacfunc_##func_name##_,               \
                        __COUNTER__) =                                         \
    tfc::Console::addLuaCFunctionToRegistry(                                   \
      function, #namespace_name, #func_name)

namespace tfc
{

/**The base lua-console singleton.*/
class Console
{
public:
  Console(const Console&) = delete;
  Console(Console&&) = delete;

  /**Returns the singleton instance.*/
  static Console& instance();

  /**Returns the lua console state.*/
  lua_State* state();

  /**Adds a lua_CFunction into the console registry.*/
  static char addLuaCFunctionToRegistry(lua_CFunction function_ptr,
                                        const std::string& namespace_name,
                                        const std::string& function_name);

  /**Loads all statically registered items into the lua console.*/
  void loadRegisteredItems();

  /**Executes the given command as a string.*/
  bool performCommand(const std::string& command_string);

private:
  Console() noexcept;

  /**\brief Makes sure a table structure exists for the list of table names.*/
  void fleshOutLuaTableStructure(const std::vector<std::string>& table_names,
                                 bool pop_last);

  lua_State* console_state_;
  std::map<std::string, lua_CFunction> lua_c_function_registry_;
};

} // namespace tfc

#endif // TFCTECH_CONSOLE_H
