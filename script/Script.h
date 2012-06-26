#pragma once

#include <string>
using std::string;

/*
enum ScriptType
{
	STypeNil,
	STypeBoolean,
	STypeInt,
	STypeDouble,
	STypeString
};
*/

class ScriptValue
{
/*
public:
	SValue()
		:type(STypeNil)
	{}

	ScriptType type;

	virtual bool	 toBoolean() = 0;
	virtual int 	 toInt() = 0;
	virtual double toDouble() = 0;
	virtual string toString() = 0;
	
	virtual bool	 isNil() = 0;	
*/
};

class Script{
public:
	virtual ~Script() {};

	virtual bool	 init() = 0;
	virtual string doString(const char* src) = 0;
	virtual string doFile(const char* fn) = 0;

	virtual ScriptValue call(const char* func) = 0;
};
