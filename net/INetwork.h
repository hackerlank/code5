#ifndef _INETWORK_H
#define _INETWORK_H

#include "Socket.h"
#include "Coder.h"

class INetwork
{
public:
	typedef Socket SocketHandle;

	virtual bool init(const char* ip, short port, const int maxCon) = 0;
	virtual void close() = 0;

	virtual void update() = 0;

	virtual void onRecv(SocketHandle* sock, size_t size) = 0;
	virtual void onConnected(SocketHandle* sock) = 0;
	virtual void onDisconnected(SocketHandle* sock) = 0;

	virtual void closeSocket(SocketHandle* sock) = 0;
};

#endif
