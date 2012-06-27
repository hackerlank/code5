#ifndef _SCRIPT_SYS_H
#define _SCRIPT_SYS_H

#include "script/LuaMgr.h"

class ScriptSys : public LuaMgr
{
public:
	static ScriptSys& instance();

public:
	ScriptSys();
	bool init();
};

#endif
