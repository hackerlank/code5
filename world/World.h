#ifndef _WORLD_H
#define _WORLD_H

#include "pattern/Singleton.h"
#include "schedule/PQScheduler.h"

class World: public Singleton<World>
{
public:
	enum{
		MsgHandlePerFrame = 3000, 
		WorldFps = 10,
		FrameTime = 1000 / WorldFps
	};

	int init(const char* userName, const char* pwd, const char* serverName);
	void update(long elapsed);

private:
	bool _gateConntectd;
};

extern PQScheduler Scheduler;

#endif