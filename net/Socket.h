
#pragma once

#ifdef _WIN32
#include <Windows.h>
#include <winsock.h>
typedef SOCKET SockHandle;
#else
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
typedef int SockHandle;
#endif

#include "util/Log.h"

class Socket
{
public:
	static bool initialize();
	static void shutdown();
	static int errorno();
public:

	Socket(const char* ip=0, short port = 0);
	Socket(SockHandle m, int ip, short port);
	~Socket();

	bool connect();
	bool bind();
	void listen(int backlog);
	void setNonBlock(bool b);
	void close();

	Socket* accept();

	int send(const void* data, int size);
	int recv(void* data, int size);
	void init(const char* ip, short port);
public:
	SockHandle m_sock;
	sockaddr_in m_addr;

	void* userdata;
};
