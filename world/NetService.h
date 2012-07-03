#ifndef _NETSERVICE_H
#define _NETSERVICE_H

#include "net/PackData.h"
#include "net/Socket.h"
#include "pattern/Singleton.h"
#include <list>
#include <vector>
#include <boost/tuple/tuple.hpp>
#include "util/concurrent/Thread.h"
#include "util/concurrent/Mutex.h"
#include "util/concurrent/ScopeLock.h"
#include <string.h>

using std::list;
using std::vector;
using boost::tuple;

typedef tuple<player_id, Message*> MsgPair;

class NetService : public Thread, public Singleton<NetService>
{
public:
	static PackData* packMsg(int msgId, Message* msg, int playerCnt);
public:
	NetService();

	bool init(const char* ip, short port);
	bool connect();
	
	void update();
	void run();

	MsgPair pop();
	
	void send(player_id playerId, int msgId, Message* msg);
	
	template<class T>
	void send(player_id playerId, T* msg) {
		if (!_connected)
			return;

		ScopeLock lock(_lock);
		PackData* pack = packMsg(PackData::packId(T::_category, T::_msgId), msg, 1);
		
		if (!pack)
			return;
		
		*pack->playerId() = playerId;
		if (playerId == -1)
			_sock.send(pack->rawData(), pack->size + sizeof(short));
		else
			_sock.send(pack->rawData(), pack->size + sizeof(short) + sizeof(player_id));
		free(pack);
	}

	template<class T>
	void send(T* msg, vector<player_id> players) {
		if (!_connected )
			return;

		if (players.empty())
			return;

		if (players.size() == 1) {
			send(players.front(), msg);
			return;
		}

		ScopeLock lock(_lock);
		PackData* pack = packMsg(PackData::packId(T::_category, T::_msgId), msg, 1);
		
		if (!pack)
			return;

		*pack->playerId() = players.size();
		memcpy(pack->playerId() + 1, &players.front(), sizeof(player_id) * players.size());
		const int size = pack->size + sizeof(short) + sizeof(player_id) * (players.size() + 1);
		_sock.send(pack->rawData(), size);
		free(pack);
	}

private:
	void readMessage(size_t maxSize);
	PackData* readPack(Socket* sock, size_t recvSize);
private:
	Socket _sock;
	list<MsgPair> _msgs;
	Mutex	_lock;
	bool	_connected;
	bool	_looping;
};

#endif
