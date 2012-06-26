#ifndef _WORLDMGR_H
#define _WORLDMGR_H

#include <map>
#include <string>
#include "net/Coder.h"
#include "pattern/Singleton.h"

using std::map;
using std::string;

class WorldMgr: public Singleton<WorldMgr> {
public:
	struct World {
		World(const string& n, session_id s)
			:name(n), sessionId(s)
		{}
		
		string  name;
		session_id sessionId;
	};
public:
	bool init(const string& passwd);

	bool send(Message* msg);
	bool send(PackData* pack);

	void loginGate(const string& pwd, const string& serverName, session_id sessionId);

	bool change(const string& serverName);
private:
	typedef map<string, World*> WorldMap;
	WorldMap _worlds;
	World* _currworld;	
	string _gatePwd;
};


#endif
