#include "Player.h"
#include "NetService.h"

Player::Player(player_id pid, session_id sid)
	:playerId(pid), sessionId(sid)
{
}

void Player::send(PackData* pack)
{
	NetService::instance().sendSession((session_id)pack->player, pack, false);
}
