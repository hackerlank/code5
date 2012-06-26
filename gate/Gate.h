#ifndef _GATE_H
#define _GATE_H

#include "net/PackData.h"
#include "NetService.h"
#include "Player.h"
#include <boost/function.hpp>
#include <map>
#include "pattern/Singleton.h"

using std::map;

#define GATE_FPS 10
const double GateFpsMillis  = 1000.0 / GATE_FPS;

typedef MessageHandler<bool>* PackHandler;

class Gate: public Singleton<Gate> {
public:
	typedef map<int, PackHandler> PHMap;
public:
	bool init();
	void update(long elapsed);	

	bool regPackHandler(int category, int msgId, PackHandler handler);
	void removePackHandler(int category, int msgId);
	
	void sendWorld(PackData* pack, int worldId);
private:
	NetService* _netService;
	PHMap _packListeners;
};

#endif
