#ifndef _LUA_MGR_H
#define _LUA_MGR_H

//#include <luabind/luabind.hpp>
#include "Script.h"
extern "C" {
	#include <lua.h>
	#include <lualib.h>
	#include <lauxlib.h>
}

class LuaMgr: public Script
{
public:
	class SLuaValue : public ScriptValue{
	public:
		SLuaValue() {};
	/*
		SLuaValue(lua_State* L, int idx) {}
		bool	 toBoolean() ;
		int 	 toInt();
		double toDouble();
		string toString();
*/
	};

public:
	LuaMgr(lua_State* L);

	string doString(const char* scr);
	string doFile(const char* fn);
	
	ScriptValue call(const char* func);

private:
	lua_State* m_state;
}; 

#endif
