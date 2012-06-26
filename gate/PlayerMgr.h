#ifndef _PLAYERMGR_H
#define _PLAYERMGR_H

#include <map>
#include <string>
#include "net/PackData.h"
#include "Player.h"
#include "pattern/Singleton.h"

using std::map;
using std::string;

class PlayerMgr : public Singleton<PlayerMgr> {
public:
	typedef map<player_id, Player*> PlayerMap;
	typedef map<session_id, Player*> SessionMap;

	Player* getBySessionId(session_id sessionId);
	Player* get(player_id playerId);

	void add(Player* player);
	void remove(player_id playerId);

	PlayerMap _players;
	SessionMap _sessions;

	void login(const string& user, const string& pwd, session_id sessionId);
};
#endif