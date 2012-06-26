#include "EpollServer.h"

#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>

EpollServer::EpollServer()
{
}

bool EpollServer::init(const char* ip, short port, const int maxCon)
{
	m_acceptSocket.init(ip,port);
	
	m_acceptSocket.bind();
	m_acceptSocket.listen(5);

	m_events = (epoll_event*)malloc(sizeof(epoll_event) * maxCon);
	m_sockets = (Socket**)malloc(sizeof(Socket*) * maxCon);
	m_sockets[0] = &m_acceptSocket;

	m_epollfd = epoll_create(maxCon);
	m_maxConn = maxCon;

	epoll_event& e = m_events[m_acceptSocket.m_sock];
	e.data.u64 = 0;
	e.data.fd = m_acceptSocket.m_sock;
	e.events = EPOLLIN | EPOLLET;
	epoll_ctl(m_epollfd, EPOLL_CTL_ADD, m_acceptSocket.m_sock, &e);

	return true;
}

void EpollServer::close()
{
  //  close(m_epollfd);
}

void EpollServer::update()
{
	int eventCount = epoll_wait(m_epollfd, m_events, m_maxConn, 0);
	for (int i = 0; i < eventCount; ++i) {
		epoll_event& e = m_events[i];
		if (e.events & EPOLLIN) {
			if (e.data.fd != m_acceptSocket.m_sock) {
				int size = 0;
				ioctl(e.data.fd, FIONREAD, &size);
				
				if (size != 0)
					onRecv(m_sockets[e.data.fd], size);
				else
					onDisconnected(m_sockets[e.data.fd]);
			} else {		
				onConnected(m_acceptSocket.accept());
			}

		}
	}

}

void EpollServer::onDisconnected(SocketHandle* sock)
{
  closeSocket(sock);
}

void EpollServer::onConnected(SocketHandle* sock)
{
	epoll_event& e = m_events[sock->m_sock];

	e.data.u64 = 0;
	e.data.fd = sock->m_sock;
	e.events = EPOLLIN | EPOLLET;
	epoll_ctl(m_epollfd, EPOLL_CTL_ADD, sock->m_sock, &e);

	m_sockets[sock->m_sock] = sock;
}

void EpollServer::closeSocket(SocketHandle* sock)
{
	epoll_event& e = m_events[sock->m_sock];
	epoll_ctl(m_epollfd, EPOLL_CTL_DEL, sock->m_sock, &e);
}
