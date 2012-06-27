#ifndef _CODER_MGR_H
#define _CODER_MGR_H

#include "Coder.h"
#include <map>

using std::map;

class CoderMgr
{
public:
	static CoderMgr& instance();
public:
	void reg(Coder* coders[]);
	bool addCoder(int msgId, Coder* coder);
	Message* decode(int msgId, void* data, int size);
	DataBuffer encode(int msgId, Message* msg);
private:
	typedef map<int, Coder*> CoderMap;
	CoderMap m_coders;
};

#endif
