#include "CoderMgr.h"

CoderMgr& CoderMgr::instance()
{
	static CoderMgr* s_mgr = 0;
	if (!s_mgr)
		s_mgr = new CoderMgr();
	
	return *s_mgr;
}

void CoderMgr::reg(Coder* coders[]) {
	size_t i = 0;

	while(true){
		Coder* coder = coders[i];
		if (!coder)
			break;
		addCoder(PackData::packId(coder->category(), coder->msgId()), coder);
		++i;
	};
}

bool CoderMgr::addCoder(int msgId, Coder* coder)
{
	m_coders[msgId] = coder;
	return true;
}

Message* CoderMgr::decode(int msgId, void* data, int size)
{
	CoderMap::iterator citr = m_coders.find(msgId);
	if (citr != m_coders.end()) 
		return citr->second->decode(data, size);
	else
		return NULL;
}

DataBuffer CoderMgr::encode(int msgId, Message* msg)
{
	const CoderMap::iterator citr = m_coders.find(msgId);
	if (citr != m_coders.end()) 
		return citr->second->encode(msg);
	else
		return DataBuffer();
}
