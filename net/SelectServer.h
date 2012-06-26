#pragma once

#include "INetwork.h"
#include <vector>

using std::vector;

class SelectServer: public INetwork
{
public:
	SelectServer();
	~SelectServer();

	bool init(const char* ip, short port, const int maxCon);
	void close();
	
	void run();

	void select();

	void onConnected(SocketHandle* sock);
	void onDisconnected(SocketHandle* sock);
	void closeSocket(SocketHandle* sock);
private:
	int m_maxCon;
	Socket m_acceptSocket;

	fd_set m_readset;
	fd_set m_rdSelectSet;
	
	vector<Socket*> m_sockets;
};
