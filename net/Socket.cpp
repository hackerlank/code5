#include "Socket.h"
#include <string.h>
#include <fcntl.h>
#include <errno.h>

extern int errno;

bool Socket::initialize()
{
#ifdef _WIN32
  WSAData wsadata;
  memset(&wsadata, 0, sizeof(WSAData));
  return WSAStartup(MAKEWORD(2, 2), &wsadata) == 0;
#else
  return true;
#endif
}

void Socket::shutdown()
{
#ifdef _WIN32
  WSACleanup();
#endif
}

int Socket::errorno()
{
  return errno;
}

Socket::Socket(const char* ip, short port)
	:userdata(0)
{
	if (ip) {
		memset(&m_addr, 0, sizeof(sockaddr_in));
		m_addr.sin_family = AF_INET;
		m_addr.sin_addr.s_addr = inet_addr(ip);
		m_addr.sin_port = htons(port);
	}

	m_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
}

Socket::Socket(SockHandle s, int ip, short port)
	:m_sock(s), userdata(0)
{
	memset(&m_addr, 0, sizeof(sockaddr_in));
	m_addr.sin_family = AF_INET;
	m_addr.sin_port = htons(port);
	m_addr.sin_addr.s_addr = ip;
}

void Socket::init(const char* ip, short port) 
{
	memset(&m_addr, 0, sizeof(sockaddr_in));
	m_addr.sin_family = AF_INET;
	m_addr.sin_addr.s_addr = inet_addr(ip);
	m_addr.sin_port = htons(port);
}

bool Socket::bind()
{
	int ret = ::bind(m_sock, (sockaddr*)&m_addr, sizeof(sockaddr_in));
	return 0 == ret;
}

bool Socket::connect()
{
	return 0 == ::connect(m_sock, (sockaddr*)&m_addr, sizeof(sockaddr_in));
}

void Socket::listen(int backlog)
{
	::listen(m_sock, backlog);
}

Socket* Socket::accept()
{
	SockHandle newSock = ::accept(m_sock, 0, 0); 
	sockaddr_in remote_addr;
	int namelen = sizeof(sockaddr_in);
	getsockname(newSock, (sockaddr*)&remote_addr,(socklen_t*)&namelen);
	return new Socket(newSock, remote_addr.sin_addr.s_addr, remote_addr.sin_port);
}

int Socket::send(const void* data, int size)
{
	int sendSize = ::send(m_sock, data, size, 0);
	if (sendSize > 0)
		Log::instance().dumpHex(data, sendSize);
	return sendSize;
}

Socket::~Socket()
{
	close();	
}

int Socket::recv(void* data, int size)
{
	int readSize = ::recv(m_sock, data, size, 0);
	if (readSize > 0)
		Log::instance().dumpHex(data, readSize);
	return readSize;
}

void Socket::close()
{
#ifdef _WIN32
  closesocket(m_sock);
#else
  ::close(m_sock);
#endif
}

void Socket::setNonBlock(bool b)
{
  int flag = fcntl(m_sock, F_GETFL);
  
  if (b)
    flag |= O_NONBLOCK;
  else
    flag &= ~O_NONBLOCK;

  fcntl(m_sock, F_SETFL, flag);
}
