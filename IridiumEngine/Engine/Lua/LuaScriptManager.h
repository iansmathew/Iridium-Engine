#pragma once

extern "C" {
# include "lua.h"
# include "lauxlib.h"
# include "lualib.h"
}

#include <LuaBridge.h>
#include <iostream>

using namespace luabridge;

class LuaScriptManager
{
public:
	LuaScriptManager();
	bool Initialize();
	~LuaScriptManager();

private:

};


