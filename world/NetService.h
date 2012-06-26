#ifndef _NETSERVICE_H
#define _NETSERVICE_H

#include "net/PackData.h"
#include "net/Socket.h"
#include "pattern/Singleton.h"
#include <list>
#include <boost/tuple/tuple.hpp>

using std::list;
using boost::tuple;

typedef tuple<player_id, Message*> MsgPair;

class NetService : public Singleton<NetService>
{
public:
	NetService();

	bool init(const char* ip, short port);
	bool connect();
	
	void update();

	MsgPair pop();
	
	void send(player_id playerId, int msgId, Message* msg);
	
	template<class T>
	void send(player_id playerId, T* msg) {
		send(playerId, PackData::packId(T::_category, T::_msgId), msg);
	}

private:
	void readMessage(size_t maxSize);
	PackData* readPack(Socket* sock, size_t recvSize);
private:
	Socket _sock;
	list<MsgPair> _msgs;
	bool	_connected;
};

#endif