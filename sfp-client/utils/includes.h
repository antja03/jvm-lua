#pragma once

#ifndef sfp_includes
#define sfp_includes

#include "jni.h"
#include "jvmti.h"


extern "C" {
#include "lua54/include/lauxlib.h"
#include "lua54/include/lua.h"
#include "lua54/include/lua.hpp"
#include "lua54/include/luaconf.h"
#include "lua54/include/lualib.h"
}

#include <LuaBridge/LuaBridge.h>

#include <string>
#include <cstdint>
#include <memory>
#include <vector>
#include <filesystem>

#include "console.h"

#endif