#ifndef _NETSERVICE_H
#define _NETSERVICE_H

#include "net/PackData.h"
#include "net/EpollServer.h"
#include "pattern/Singleton.h"
#include "util/concurrent/Thread.h"
#include "util/concurrent/Mutex.h"
#include "util/Timer.h"

#include <list>
#include <map>
#include <inttypes.h>
#include <cmath>

using std::map;
using std::list;
using std::max;

enum ConState {
	CSConnected,
	CSLogined,
	CSMax
};

class NetService : public EpollServer, public Singleton<NetService>, public Thread{
public:
	typedef map<SocketHandle*, session_id> SessionMap;
	typedef map<session_id, SocketHandle*> SocketMap;
public:
	NetService();

	void init(const char* svr_ip, short port);

	virtual void onConnected(SocketHandle* sock);
	virtual void onDisconnected(SocketHandle* sock);
	
	virtual void onRecv(SocketHandle* sock, size_t size);
	PackData* pop();

	void sendSession(session_id session, PackData* data, bool withPid);
	// /void sendSession(session_id session, byte* data, size_t size);

	void setSessionState(session_id session);
	void cutSession(session_id session);

	void run();
	void stop();

	void speed(double& byteSpeed, double& packSpeed) {
		double elapsed = (Timer::getMilliSecond() - _startTime) / 1000.0;
		if (elapsed < 1)
			elapsed = 1;
		byteSpeed = _totalBytes / elapsed;
		packSpeed = _totalPacks / elapsed;
	}
protected:
	PackData* recvPack(SocketHandle* sock, size_t size, size_t& totalRead);

	list<PackData*> _msgQueue;
	SessionMap _sock2session;
	SocketMap _session2sock;
	session_id _serverSession;

	typedef MessageHandler<bool>* PackHandler;
	typedef map<short, PackHandler> HandlerMap;
	HandlerMap _stateHandler[CSMax];

	Mutex	_lock;
	bool	_looping;

	int64_t _totalBytes;
	int64_t _totalPacks;

	long	_startTime;
};

#endif
