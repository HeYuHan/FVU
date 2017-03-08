#include "tcp.h"
NS_FVU_BEGIN
bool TcpConnection::init()
{
#ifdef WIN32_SOCKET
	WSADATA wData;
	WORD version = MAKEWORD(2, 0);
	int ret = WSAStartup(version, &wData);
	if (ret)
	{
		return false;
	}
#endif
	return true;
}
TcpConnection::TcpConnection():
m_Connected(false)
{

}
TcpConnection::~TcpConnection()
{

}
bool TcpConnection::create(bool bKeepAlive)
{
#ifdef WIN32_SOCKET
	WSADATA wsaData;
	WORD version = MAKEWORD(2, 0);
	int ret = WSAStartup(version, &wsaData);
	if (ret != 0)return false;
#endif
	m_Socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (m_Socket == INVALID_SOCKET)
	{
		return false;
	}
	if (bKeepAlive)
	{
		int optval = 1;
		if (setsockopt(m_Socket, SOL_SOCKET, SO_KEEPALIVE, (char*)optval, sizeof(optval)))
		{
			close();
			return false;
		}
	}
#ifdef WIN32_SOCKET
	DWORD nMode = 1;
	int nRes = ioctlsocket(m_Socket, FIONBIO, &nMode);
	if (nRes == SOCKET_ERROR)
	{
		close();
		return false;
	}
#else
	fcntl(m_Socket,F_SETFL,O_NONBLOCK);
#endif
	return true;
}
bool TcpConnection::connect(const char* ip, unsigned short port, int nBlockSec)
{
	struct sockaddr_in addr;
	memset((void*)&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr(ip);
	addr.sin_port = htons(port);
	int ret = ::connect(m_Socket, (struct sockaddr*)&addr, sizeof(addr));
	if (ret == SOCKET_ERROR)
	{
		if (getError())
		{
			close();
			return false;
		}
		else
		{
			timeval timeout;
			timeout.tv_sec = nBlockSec;
			timeout.tv_usec = 0;
			fd_set write_set, except_set;
			FD_ZERO(&write_set);
			FD_ZERO(&except_set);
			FD_SET(m_Socket, &write_set);
			FD_SET(m_Socket, &except_set);
			int ret = select(FD_SETSIZE, NULL, &write_set, &except_set, &timeout);
			if (ret == 0 || ret < 0)
			{
				close();
				return false;
			}
			else
			{
				ret = FD_ISSET(m_Socket, &except_set);
				if (ret)
				{
					close();
					return false;
				}
			}
		}
	}
	struct linger so_linger;
	so_linger.l_onoff = 1;
	so_linger.l_linger = 500;
	setsockopt(m_Socket, SOL_SOCKET, SO_LINGER, (const char*)&so_linger, sizeof(so_linger));
	m_Connected = true;
	return true;
}
int TcpConnection::send(const char* buff, int len, int flags /* = 0 */)
{
	int send_count = 0;
	if (len > 0)
	{
		send_count = ::send(m_Socket, buff, len, flags);
	}
	return send_count;
}
int TcpConnection::recv(char* buff, int len, int flags/* =0 */)
{
	return (::recv(m_Socket, buff, len, flags));
}
int TcpConnection::close()
{
#ifdef WIN32_SOCKET
	m_Connected = false;
	closesocket(m_Socket);
	return (WSACleanup());
#else
	return (::close(m_Socket));
#endif // WIN32_SOCKET

}
bool TcpConnection::getError()
{
#ifdef WIN32_SOCKET
	int err = WSAGetLastError();
	if (err != WSAEWOULDBLOCK)
	{
#else
	int err = eerrno;
	if (err != EINPROGRESS && err != EAGAIN)
	{
#endif
		return true;
	}
	return false;

}
bool TcpConnection::check()
{
	if (m_Socket == INVALID_SOCKET)return false;
	char check_buff[1];
	int ret = recv(check_buff, 1, MSG_PEEK);
	if (ret == 0)
	{
		destory();
		return false;
	}
	else if (ret < 0)
	{
		if (getError())
		{
			destory();
			return false;
		}
		else
		{
			return true;
		}
	}
	return true;
}
void TcpConnection::destory()
{
	struct linger so_linger;
	so_linger.l_onoff = 1;
	so_linger.l_linger = 500;
	int ret = setsockopt(m_Socket, SOL_SOCKET, SO_LINGER, (const char*)&so_linger, sizeof(so_linger));
	close();
	m_Socket = INVALID_SOCKET;
}
NS_FVU_END