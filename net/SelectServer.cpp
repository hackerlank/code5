#include "SelectServer.h"
#include <stdio.h>
#include <string.h>
#include <math.h>

#include <sys/unistd.h>
#include <sys/select.h>
#include <sys/ioctl.h>

SelectServer::SelectServer()
{

}

bool SelectServer::init(const char* ip, short port, const int maxCon)
{
  m_acceptSocket.init(ip, port);
  m_maxCon = std::max(maxCon, FD_SETSIZE);

  FD_ZERO(&m_readset);
  FD_SET(m_acceptSocket.m_sock, &m_readset);
  
  m_sockets.reserve(m_maxCon);
  m_sockets[m_acceptSocket.m_sock] = &m_acceptSocket;

  m_acceptSocket.bind();
  m_acceptSocket.listen(5);
  return true;
}

void SelectServer::run()
{
  select();
}

void SelectServer::select()
{
  memcpy(&m_rdSelectSet, &m_readset, sizeof(fd_set));

  int ret = ::select(m_maxCon + 1, &m_rdSelectSet, NULL, NULL, NULL);
  if (ret <= 0)
    return ;

  for (int i = 0; i < m_maxCon; ++i ) {
    if (FD_ISSET(i, &m_readset)) {
      Socket* sock = m_sockets[i];
      int cnt = 0;
      ioctl(sock->m_sock, FIONREAD, &cnt);
      if (&m_acceptSocket != sock) {
      	if (cnt == 0)
      	  onDisconnected(sock);
      	else
      	  onRecv(sock, cnt);
      } else 
        onConnected(m_acceptSocket.accept());
    }
  }
  
}

void SelectServer::closeSocket(SocketHandle* sock)
{
  onDisconnected(sock);
  m_sockets[sock->m_sock] = 0;
  FD_CLR(sock->m_sock, &m_readset);
}

void SelectServer::onDisconnected(SocketHandle* sock)
{
  m_sockets[sock->m_sock] = 0;
  FD_CLR(sock->m_sock, &m_readset);
  
  sock->close();
}

void SelectServer::onConnected(SocketHandle* sock)
{
  FD_SET(sock->m_sock, &m_readset);
  m_sockets[sock->m_sock] = sock;
}

void SelectServer::close()
{
  for (vector<Socket*>::iterator itr = m_sockets.begin();
       itr != m_sockets.end(); ++itr)
    (*itr)->close();
  FD_ZERO(&m_readset);
}

SelectServer::~SelectServer()
{
  close();
}
