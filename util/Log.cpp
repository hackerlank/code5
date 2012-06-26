#include "Log.h"

#include <assert.h>
#include <stdio.h>

#include "Timer.h"

bool Log::init(const char* fn)
{

	return true;
}

Log::Log()
{

}

Log::~Log()
{
}

void Log::log(const char* info, LogLevel level)
{

}

void Log::print(const char* info)
{

}

void Log::dumpHex(const void* data, int size) 
{
	static char s_hexChar[] = {'0', '1', '2', '3', '4', '5', '6', '7',
						'8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
	char* text = new char[size * 2 + 1];
	text[size * 2] =0;

	const char* buffer = reinterpret_cast<const char*>(data);
	for (int i = 0; i< size; ++i) {
		text[i*2] = s_hexChar[buffer[i] & 0xF];
		text[i*2 + 1] = s_hexChar[(buffer[i] >> 4) & 0xF];
	}
	puts(text);
	delete[] text;
}