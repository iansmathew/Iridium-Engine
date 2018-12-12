#include "stdafx.h"
#include "Engine/Lua/LuaScriptManager.h"


LuaScriptManager::LuaScriptManager()
{
}



LuaScriptManager::~LuaScriptManager()
{
}

bool LuaScriptManager::Initialize()
{
	lua_State* L = luaL_newstate();
	luaL_dofile(L, "script.lua");
	luaL_openlibs(L);
	lua_pcall(L, 0, 0, 0);
	LuaRef s = getGlobal(L, "testString");
	LuaRef n = getGlobal(L, "number");
	std::string luaString = s.cast<std::string>();
	std::string answer = n.cast<std::string>();
	OutputDebugStringA(luaString.c_str());
	OutputDebugStringA(answer.c_str());
	return false;
}