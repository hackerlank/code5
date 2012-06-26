#ifndef _LOG_H
#define _LOG_H

#include "pattern/Singleton.h"

enum LogLevel
{
	LogInfo,
	LogWarnning,
	LogError
};

class Log: public Singleton<Log>
{
public:
	Log();
	~Log();

	bool init(const char* fn);

	void log(const char* info, LogLevel level);
	void print(const char* info);

	void dumpHex(const void* data, int size);
};

#endif