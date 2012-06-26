#include "Gate.h"

#include "../util/Timer.h"
#include "WorldMgr.h"
#include <stdio.h>

void exitSingal(int sig)
{

}

int main(int argc, char* argv[])
{
	Gate::instance().init();

	WorldMgr::instance().init("passwd");

	long lastFrameTime = Timer::getMilliSecond();
	long frameTimeAcc = 0;

	while(true) {
		usleep(1);
		long now = Timer::getMilliSecond();
		frameTimeAcc += now - lastFrameTime;
		if (frameTimeAcc >= GateFpsMillis) {
			Gate::instance().update(frameTimeAcc);	
			printf("xxxx %ld \n", frameTimeAcc);
			frameTimeAcc -= GateFpsMillis;
		}
		lastFrameTime = now;
	}
}


