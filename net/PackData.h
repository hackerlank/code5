#ifndef _PACKDATA_H
#define _PACKDATA_H

#include <inttypes.h>
#include <stddef.h>
#include <stdlib.h>
#include <google/protobuf/message.h>

typedef google::protobuf::Message Message;

typedef int64_t player_id;
typedef int64_t session_id;

typedef unsigned char byte;

enum PackCategory {
  PackRequest = 0,
  PackEvent = 1,
  PackResponse = 2,
  PackInfo = 3,

  PackSys = 4, 

  PackMax = 0x1f
};

struct PackData {
	player_id player; // first sessionId then playerId
	bool	  fromServer;
		
	short	size;	//size without player_id size, and without it self, just the (data size + header size)

	union{
		short packMsgId;
		struct{
			short	msgId : 12;
			short	category : 4;
		};
	};

	byte	data[1];

	byte* rawData() {return (byte*)&size; };
	byte* contentData(){ return (byte*)&packMsgId; }

	static PackData* create(int size, int playerCnt = 1) {
		if (playerCnt > 1)
			++ playerCnt;

		return (PackData*)malloc(offsetof(PackData, packMsgId) + sizeof(player_id) * playerCnt + size);
	}

	static short packId(short category, short msgId) {
		return (category << 12) | msgId;
	}

	player_id* playerId() {
		return (player_id*)((byte*)&packMsgId + size);
	}
};

#endif
