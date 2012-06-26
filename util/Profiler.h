#pragma once

#include <string>
#include <stdio.h>
#include "Timer.h"

using namespace std;

#define PROFILER(tab) Profiler xxxx(__FILE__, __LINE__, __FUNCTION__, tab)

class Profiler {
	static int s_tabIdentity;
public:
	Profiler(const char* lineInfo, int line, const char* function, bool addTab);
	~Profiler();

	string toString();

	long mStartMS;
	long mElapsed;

	const char* mFile;
	const int mLine;
	const char* mFunction;
};

