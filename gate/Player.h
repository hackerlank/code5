#ifndef _PLAYER_H
#define _PLAYER_H

#include "net/PackData.h"
#include "net/Coder.h"
#include "net/CoderMgr.h"

class Player {
public:
	Player(player_id playerId, session_id sessionId);

	player_id	playerId;
	session_id	sessionId;

	template<class T> 
	void send(T* msg) {
		const int msgId = PackData::packId(T::_category, T::_msgId);
		DataBuffer buffer = CoderMgr::instance().encode(msgId, msg);
		if (buffer.size == 0) 
			return;

		PackData* pack = PackData::create(buffer.size + sizeof(short));
		pack->packMsgId = msgId;
		pack->size = buffer.size + sizeof(short);
		pack->fromServer = false;
		memcpy(pack->data, buffer.data, buffer.size);
		pack->player = sessionId;
		send(pack);
	}

	void send(PackData* pack);
};
#endif
