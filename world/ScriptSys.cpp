#include "ScriptSys.h"

ScriptSys& ScriptSys::instance()
{
	static ScriptSys* _script = 0;
	if (!_script) {
		_script = new ScriptSys();
		_script->init();
	}

	return *_script;
}

ScriptSys::ScriptSys()
	:LuaMgr(luaL_newstate())
{
//	luaL_openlibs(m_state);
}

bool ScriptSys::init()
{
	return true;
}

