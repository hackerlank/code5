#include "NetService.h"
#include "net/CoderMgr.h"
#include <stdlib.h>
#include <unistd.h>
#include "PlayerMgr.h"
#include "WorldMgr.h"

#include "proto/login.pb.h"
#include "GateMsgCoder.h"
#include "util/concurrent/ScopeLock.h"

#include <stdio.h>

using namespace netmsg;

static bool serverLogin(player_id sessionId, ServerLoginRequest* msg) {
	WorldMgr::instance().loginGate(msg->passwd(), msg->servername(), (session_id)sessionId);
	return false;
}

NetService::NetService()
	:_looping(true), _totalBytes(0), _totalPacks(0)
{}

void NetService::init(const char* ip, short port) 
{
	_stateHandler[CSConnected] = HandlerMap();
	_stateHandler[CSLogined] = HandlerMap();

	_stateHandler[CSConnected][PackData::packId(PackSys, ServerLoginRequest::_msgId)] = new AnyMsgHandler<bool, ServerLoginRequest>(serverLogin);
//	_stateHandler[CSConnected][PackData::packId(PackRequest, 1)] = new AnyMsgHandler<bool, LoginRequest>(playerLogin);

	CoderMgr::instance().reg(g_msg_coders);

	EpollServer::init(ip, port, 6000);
}

PackData* NetService::recvPack(SocketHandle* sock, size_t size, size_t& totalRead )
{
	short header[2];	
	int recved = sock->recv(header, sizeof(header));

	//stat
	if (recved > 0)
		totalRead += recved;

	if (recved != sizeof(header))
		return NULL;

	PackData* pack = PackData::create(header[0]);
	pack->size = header[0];
	pack->packMsgId = header[1];

	pack->fromServer = sock->m_sock == _serverSession;

	const int dataSize = pack->size - sizeof(short) + (pack->fromServer ? sizeof(player_id) : 0);
	if (dataSize <= 0 )
		goto ERROR;

	recved = sock->recv(pack->data, dataSize);

	//stat
	if (recved > 0)
		totalRead += recved;

	if (dataSize != recved)
		goto ERROR;

	if (pack->fromServer)
		pack->player = *pack->playerId();
	else
		pack->player = (player_id)sock->m_sock;

	return pack;
ERROR:
	if (pack) {
		free(pack);
		pack = NULL;
	}
	return pack;
}

void NetService::onRecv(SocketHandle* sock, size_t size)
{
  int64_t oldCnt = _totalBytes;
  _totalBytes += size;
  if (oldCnt >= _totalBytes)
	  assert(0);

  ScopeLock lock(_lock);
  while(size > 0) {
	size_t totalRead = 0;
    PackData* pack = recvPack(sock, size, totalRead);
    if (!pack)
      break;

    ++_totalPacks;

  	const int sockState = reinterpret_cast<long>(sock->userdata);
  	const HandlerMap& handlers = _stateHandler[sockState];
    HandlerMap::const_iterator itr = handlers.find(pack->packMsgId);

    bool pushQueue = true;

    //for debug
    {
    	Message* msg = CoderMgr::instance().decode(pack->packMsgId, pack->data, pack->size - sizeof(short));

   		if (msg) {
   			printf("receive, %ld: %s\n", pack->player, msg->DebugString().c_str());
   			delete msg;
   		}
    }

    if (itr != handlers.end()) {
    	Message* msg = CoderMgr::instance().decode(pack->packMsgId, pack->data, pack->size - sizeof(short));

   		if (msg) {
    		pushQueue = (*itr->second)(pack->player, msg);
    		delete msg;
   		}
    }

    if (pushQueue)
    	_msgQueue.push_back(pack);	

    if (totalRead >= size)
    	break;
    else
    	size -= totalRead;
  }
}

PackData* NetService::pop()
{
	ScopeLock lock(_lock);
	if (_msgQueue.empty())
		return NULL;

	PackData* pack = _msgQueue.front();
	_msgQueue.pop_front();
	return pack;
}

void NetService::onConnected(SocketHandle* sock)
{
	ScopeLock lock(_lock);
	sock->setNonBlock(true);
	_sock2session[sock] = (session_id)sock->m_sock;
	_session2sock[sock->m_sock] = sock;
	EpollServer::onConnected(sock);
}

void NetService::onDisconnected(SocketHandle* sock)
{
	ScopeLock lock(_lock);
	SessionMap::iterator itr = _sock2session.find(sock);
	if (itr != _sock2session.end()) {
		_sock2session.erase(itr);
		_session2sock.erase(itr->second);
	}
	EpollServer::onDisconnected(sock);
}

void NetService::sendSession(session_id session, PackData* pack, bool withPid)
{
	ScopeLock lock(_lock);
	SocketMap::iterator itr = _session2sock.find(session);
	if (itr != _session2sock.end()) {
		*pack->playerId() = pack->player;
		const size_t sendSize = pack->size + sizeof(short) + (withPid ? sizeof(player_id) : 0 );
		itr->second->send(pack->rawData(), sendSize);
	}
}

void NetService::setSessionState(session_id session)
{
	ScopeLock lock(_lock);
	SocketMap::iterator itr = _session2sock.find(session);
	if (itr != _session2sock.end())
		itr->second->userdata = (void*)CSLogined;
}

void NetService::cutSession(session_id session) 
{
	ScopeLock lock(_lock);
	SocketMap::iterator itr = _session2sock.find(session);
	if (itr != _session2sock.end()) {
		itr->second->close();
		delete itr->second;

		_session2sock.erase(itr);
	}
}

void NetService::run() {
	_startTime = Timer::getMilliSecond();
	while (_looping) {
		usleep(1);
		update();
	}
}

void NetService::stop() {
	_looping = false;
}
