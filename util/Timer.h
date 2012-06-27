#ifndef _TIMER_H
#define _TIMER_H

#ifdef _WIN32
#include <Windows.h>
#include <Mmsystem.h>
#else
#include <sys/time.h>
#endif

enum TimeUnit {
	UnitMilliSecond,
	UnitSecond,
	UnitMinute,	
	UnitHours
};

const int MilliUnitScale[] = {1, 1000, 1000*60, 1000*60*60};

inline long timeToMs(long time, TimeUnit unit)
{
	return MilliUnitScale[unit] * time;
}

class Timer 
{
public:
	static long getMilliSecond()
	{
#ifdef _WIN32
		return timeGetTime();
#else
		timeval tv;
		gettimeofday(&tv, 0);

		return tv.tv_sec * 1000 + tv.tv_usec / 1000;
#endif
	}
};

#endif
