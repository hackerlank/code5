#pragma once

#include "script/LuaMgr.h"

class ScriptSys : public LuaMgr
{
public:
	static ScriptSys& instance();

public:
	ScriptSys();
	bool init();
};
