#include "INetwork.h"

#include <sys/epoll.h>

class EpollServer: public INetwork
{
public:
	EpollServer();
	virtual ~EpollServer() {}
	
	bool init(const char* ip, short port, const int maxCon);
	void close();
	void update();

	void onDisconnected(SocketHandle* sock);
	void onConnected(SocketHandle* sock);
	void closeSocket(SocketHandle* sock);
private:
	Socket m_acceptSocket;
	int	m_epollfd;
	epoll_event* m_events;
	Socket** m_sockets;
	int m_maxConn;
};
