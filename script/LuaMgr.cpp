#include "LuaMgr.h"

/*
bool LuaMgr::SLuaValue::toBoolean()
{
	return ;
}

LuaMgr::SValue::SLuaValue(lua_State* L, int idx)
	:
{
}
*/
////////////////////////////////////////////////////
LuaMgr::LuaMgr(lua_State* L)
	:m_state(L)
{}


string LuaMgr::doString(const char* src)
{
	if (luaL_dostring(m_state, src) )
		return lua_tostring(m_state, -1);
	else
	  return string();
}


string LuaMgr::doFile(const char* fn)
{
	if (luaL_dofile(m_state, fn))
		return string(lua_tostring(m_state, -1));
	else
		return string();
}

ScriptValue LuaMgr::call(const char* func)
{
	return SLuaValue();
}


