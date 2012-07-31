#include "KQueueService.h"

#ifdef __APPLE__

#include <sys/ioctl.h>

KQueueService::KQueueService()
{
}

KQueueService::~KQueueService()
{

}

bool KQueueService::init(const char* ip, short port, const int maxCon)
{
	_acceptSocket.init(ip, port);
	_acceptSocket.bind();
	_acceptSocket.listen(5);

	_kfd = kqueue();
	_maxConn = maxCon;

	//_sockets = new Socket*[maxCon];
	_sockets[_acceptSocket.m_sock] = &_acceptSocket;
	_kevents = (struct kevent*)malloc(sizeof(struct kevent) * (maxCon + 1));
	memset(&_kevents, 0, sizeof(struct kevent) * (maxCon + 1));

	struct kevent ke;
	EV_SET(&ke, _acceptSocket.m_sock, EVFILT_READ, EV_ADD, 0, 0, NULL);
	int ret = kevent(_kfd, &ke, 1, NULL, 0, NULL);
	if (ret == -1) {
		free(_kevents);

	}
	return ret != -1;
}

void KQueueService::update() 
{
	timespec timeout;
	timeout.tv_sec = 0;
	timeout.tv_nsec = 30;
	
	int evtCnt = kevent(_kfd, NULL, 0, _kevents, _maxConn, &timeout);
	for (int i = 0; i < evtCnt; ++i) {
		const struct kevent& e = _kevents[i];
		if (e.filter & EVFILT_READ) {
			if (e.ident != _acceptSocket.m_sock) {
				int size = 0;
				ioctl(e.ident, FIONREAD, &size);
				if (size != 0)
					onRecv(_sockets[e.ident], size);
				else
					onDisconnected(_sockets[e.ident]);
			} else {
				onConnected(_acceptSocket.accept());
			}
		}
	}
}

void KQueueService::onConnected(SocketHandle* sock)
{
	struct kevent ke;
	EV_SET(&ke, sock->m_sock, EVFILT_READ, EV_ADD, 0, 0, NULL);
	if (-1 != kevent(_kfd, &ke, 1, NULL, 0, NULL)) {
		_sockets[sock->m_sock] = sock;
	}
}

void KQueueService::onDisconnected(SocketHandle* sock) 
{
	struct kevent ke;
	EV_SET(&ke, sock->m_sock, EVFILT_READ, EV_DELETE, 0, 0, NULL);
	kevent(_kfd, &ke, 1, NULL, 0, NULL);
	_sockets[sock->m_sock] = sock;
	closeSocket(sock);
}

void KQueueService::close()
{
}

void KQueueService::closeSocket(SocketHandle* sock)
{
}
#endif
