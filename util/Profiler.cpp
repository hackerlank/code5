#include "Profiler.h"
int Profiler::s_tabIdentity = 0;
Profiler::Profiler(const char* lineInfo, int line, const char* function, bool addTab)
	:mFile(lineInfo), mLine(line), mFunction(function)
{
	if (addTab)
		s_tabIdentity++;

	mStartMS = Timer::getMilliSecond();
};

Profiler::~Profiler()
{
	mElapsed = Timer::getMilliSecond() - mStartMS;
	printf("%s\n", toString().c_str());
}

string Profiler::toString()
{
	string s;
	if (s_tabIdentity)
		s.reserve(s_tabIdentity);

	char msg[256];
	sprintf(msg, "%s%s:%d:%s, %ld ms", s.c_str(), mFile, mLine, mFunction, mElapsed);
	return string(msg);
}
