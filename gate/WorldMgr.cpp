#include "WorldMgr.h"
#include <stdio.h>
#include <assert.h>
#include "NetService.h"

bool WorldMgr::init(const string& pwd) {
	_gatePwd  = pwd;
	_currworld = 0;
	return true;
}

bool WorldMgr::send(Message* msg) {
	if (!_currworld)
		return false;
	assert(0);
	return true;
}

bool WorldMgr::send(PackData* msg) {
	if (!_currworld)
		return false;

	NetService::instance().sendSession(_currworld->sessionId, msg, true);

	return true;
}

void WorldMgr::loginGate(const string& pwd, const string& serverName, session_id sessionId) {
	WorldMap::const_iterator citr = _worlds.find(serverName);
	if (citr != _worlds.end()) {
		// disconnect socket
		NetService::instance().cutSession(citr->second->sessionId);
		delete citr->second;
	}

	World* pworld = new World(serverName, sessionId);
	_worlds[serverName] = pworld;

	if (_currworld)
		(void)0; //TODO new world exchange

	printf("world login: %s, session: %ld", serverName.c_str(), (long)sessionId);
	_currworld = pworld;
}

bool WorldMgr::change(const string& serverName) {
	WorldMap::iterator itr = _worlds.find(serverName);
	if (itr == _worlds.end())
		return false;
	_currworld = &(*itr->second);
	return true;
}

