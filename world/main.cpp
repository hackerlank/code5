//// WingsServer.cpp : Defines the entry point for the console application.
////
//
#include "util/Timer.h"
#include "World.h"

#include <iostream>

int main(int argc, char* argv[])
{
	//PROFILER(true);



	//PQScheduler scheduler;

	// scheduler.schedule( f1, 10, UnitSecond);
	// scheduler.schedule( f2, 5, UnitSecond);
	World::instance().init("user", "passwd", "server007");

	long lastMs = Timer::getMilliSecond();
	while (true ) {
		long now = Timer::getMilliSecond();
		long elapsed = now - lastMs;

		if (elapsed > 0) {
			World::instance().update(elapsed);
			lastMs = now;
		}
		
		sleep(1);
	}

	return 0;
}

