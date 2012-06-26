#include "NetService.h"

#include <sys/ioctl.h>
#include "net/CoderMgr.h"
#include "MessageDescriptor.h"

#include <stdio.h>
#include <errno.h>

extern int errno;

NetService::NetService()
	:_connected(false)
{

}

bool NetService::init(const char* ip, short port) { 
	_sock.init(ip, port);

	//init coders
	CoderMgr::instance().reg(g_msg_coders);

	return true;
}

bool NetService::connect() {
	_connected = _sock.connect();
	_sock.setNonBlock(true);
	return _connected;
}

MsgPair NetService::pop()
{
	if (_msgs.empty())
		return MsgPair(0, NULL);

	MsgPair pair = _msgs.front();
	_msgs.pop_front();
	return pair;
}

void NetService::send(player_id playerId, int msgId, Message* msg) {
	if (!_connected)
		return;

	DataBuffer buffer = CoderMgr::instance().encode(msgId, msg);
	if (!buffer.size)
		return;

	PackData* pack = PackData::create(buffer.size + sizeof(short));
	pack->size = buffer.size + sizeof(short);
	*pack->playerId() = playerId;
	pack->packMsgId = msgId;
	memcpy(pack->data, buffer.data, buffer.size);
	if (playerId == -1)
		_sock.send(pack->rawData(), pack->size + sizeof(short));
	else
		_sock.send(pack->rawData(), pack->size + sizeof(player_id) + sizeof(short));
}

void NetService::update()
{
	fd_set readfds;
	FD_ZERO(&readfds);
	FD_SET(_sock.m_sock, &readfds);
	timeval timeout = {0, 0};
	int fdCnt = ::select(_sock.m_sock + 1, &readfds, NULL, NULL, &timeout);

	if (fdCnt != 0 || errno != 0)
		printf("select: %d, %d\n", fdCnt, errno);
	
	if (fdCnt > 0 && FD_ISSET(_sock.m_sock, &readfds)) {
		int size = 0;
		ioctl(_sock.m_sock, FIONREAD, &size);

		if (size == 0)
			_connected = false;
		else
			readMessage(size);
	}
}

void NetService::readMessage(size_t maxSize) {
	PackData* pack = NULL;
	while( maxSize > 0 && (pack = readPack(&_sock, maxSize)) != NULL) {
		Message* msg = CoderMgr::instance().decode(pack->packMsgId, pack->data, pack->size - sizeof(short));
		if (msg) {
			_msgs.push_back(MsgPair(pack->player, msg));
			printf("recv msg: %s\n", msg->DebugString().c_str());
		}
		maxSize -= pack->size + sizeof(player_id) + sizeof(short);
	}
}

PackData* NetService::readPack(Socket* sock, size_t recvSize) {
	short header[2];	
	if (sock->recv((void*)header, sizeof(header)) != sizeof(header))
		return NULL;

	PackData* pack = PackData::create(header[0]);
	pack->size = header[0];
	pack->packMsgId = header[1];

	const int dataSize = pack->size - sizeof(short) + sizeof(player_id);
	if (dataSize <= 0 )
		goto ERROR;

	if (dataSize != sock->recv(pack->data, dataSize))
		goto ERROR;

	
	pack->player = *pack->playerId();

	return pack;
ERROR:
	if (pack) {
		free(pack);
		pack = NULL;
	}
	return pack;

}