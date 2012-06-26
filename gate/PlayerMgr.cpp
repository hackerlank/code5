#include "PlayerMgr.h"
#include <stdio.h>

Player* PlayerMgr::getBySessionId(session_id sessionId)
{
	SessionMap::iterator itr = _sessions.find(sessionId);
	return itr != _sessions.end() ? itr->second : NULL;
}

Player* PlayerMgr::get(player_id playerId)
{
	PlayerMap::iterator itr = _players.find(playerId);
	return itr != _players.end() ? itr->second : NULL;
}

void PlayerMgr::add(Player* player)
{
	_players[player->playerId] = player;
	_sessions[player->sessionId] = player;
}

void PlayerMgr::remove(player_id playerId)
{
	Player* player = get(playerId);
	if (player) {
		_players.erase(playerId);
		_sessions.erase(player->sessionId);

		delete player;
	}
}

void PlayerMgr::login(const string& user, const string& pwd, session_id sessionId)
{
	bool pwdOk = true;
	if (!pwdOk)
		return;

	static player_id s_pidAcc = 1;

	Player* player = getBySessionId(sessionId);
	if (player) {
		//session changed
		printf("new player login: %s \n ", user.c_str());
	} else {
		player = new Player(s_pidAcc++, sessionId);
		add(player);

		printf("new player login: %s \n ", user.c_str());
	}
}
