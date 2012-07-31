#include "INetwork.h"

#ifdef __APPLE__
#include <sys/types.h>
#include <sys/event.h>
#include <sys/time.h>

class KQueueService: public INetwork 
{
public:
	KQueueService();
	virtual ~KQueueService();
	
	bool init(const char* ip, short port, const int maxCon);
	void close();
	void update();

	void onDisconnected(SocketHandle* sock);
	void onConnected(SocketHandle* sock);
	void closeSocket(SocketHandle* sock);
private:
	Socket _acceptSocket;
	int _kfd;
	struct kevent* _kevents;
	int _maxConn;
	Socket** _sockets;

};
#endif
