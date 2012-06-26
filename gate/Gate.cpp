#include "Gate.h"
#include "PlayerMgr.h"
#include "WorldMgr.h"
#include "net/CoderMgr.h"

#include "proto/login.pb.h"
using netmsg::LoginRequest;

#include <stdio.h>

static bool playerLogin(player_id sessionId, LoginRequest* msg)
{
	PlayerMgr::instance().login(msg->username(), msg->passwd(), (session_id)sessionId);
	NetService::instance().setSessionState((session_id)sessionId);
	return true;
}

#define REG_MSG_HANDLER(Msg, f) regPackHandler(Msg::_category, Msg::_msgId, new AnyMsgHandler<bool, Msg>(f))
bool Gate::init()
{
	//regPackHandler(PackRequest, netmsg::LoginRequest::_msgId, new AnyMsgHandler<bool, LoginRequest>(playerLogin));
	REG_MSG_HANDLER(netmsg::LoginRequest, playerLogin);

	NetService::instance().init("127.0.0.1", 9913);
	NetService::instance().start();

	return true;
}

void Gate::update(long eslapsed)
{
	//handle messages
	int cnt = 3000;
	PackData* pack = 0;
	while( (--cnt) > 0 && (pack = NetService::instance().pop()) != NULL) {		
		Player* player = PlayerMgr::instance().getBySessionId(pack->player);

		const PHMap::const_iterator itr = _packListeners.find(pack->packMsgId);
		bool propagate = true;
		Message* msg = 0;
		if (itr != _packListeners.end() && \
			(msg = CoderMgr::instance().decode(pack->packMsgId, pack->data, pack->size - sizeof(short))) != 0) {
			propagate = (*itr->second)(player ? player->playerId : pack->player, msg);
			delete msg;
		}
		
		if (propagate && player)  {
			if (pack->fromServer) {
				if (pack->category != PackSys)
					player->send(pack);
			} else {
				pack->player = player->playerId;
				WorldMgr::instance().send(pack);
			}
		} 

		free(pack); 
	}	

	//do my own update
	static int s_cnt = 0;
	if (++s_cnt % 20 == 0) {
		s_cnt = 0;
		double s1, s2;
		NetService::instance().speed(s1, s2);
		printf("speed: %f bps, %f pps\n", s1, s2);
	}
}

bool Gate::regPackHandler(int category, int msgId, PackHandler handler)
{
	if (category<0 || category > PackMax)
		return false;

	_packListeners[category << 12 | msgId] = handler;
	return true;	
}

void Gate::removePackHandler(int category, int msgId)
{
	if (category<0 || category > PackMax)
		return;

	//mem leak here
	_packListeners.erase(category << 12 | msgId);
}
