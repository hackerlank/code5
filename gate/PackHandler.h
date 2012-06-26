#ifndef _BEHAVIOUR_H
#define	_BEHAVIOUR_H

#include "WorldMgr.h"
#include "Coder.h"
#include "PackData.h"

class Behaviour: public Singleton<Behaviour> {
public:
	void serverLogin(PackData* pack, Message* msg);
};

#endif
