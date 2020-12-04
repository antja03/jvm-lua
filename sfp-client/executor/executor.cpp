#include "executor.h"

lua_State* executor:: state;

void executor::initialize()
{
	state = luaL_newstate();
}