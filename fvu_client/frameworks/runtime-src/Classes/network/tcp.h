#ifndef __TCP_H__
#define __TCP_H__
#if defined(_WIN32) && defined(_WINDOWS)
#define WIN32_SOCKET
#include <WinSock.h>
#pragma comment(lib,"wsock32")
#else
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <errno.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>

#include <string.h>
#endif
#include "Common/tool.h"

#ifndef SOCKET
#define SOCKET int
#endif // !SOCKET
#ifndef SOCKET_ERROR
#define SOCKET_ERROR -1
#endif
#ifndef INVALID_SOCKET
#define INVALID_SOCKET -1
#endif // !INVALID_SOCKET

NS_FVU_BEGIN
class TcpConnection
{
	GET_SET(bool, Connected);
	GET_SET(SOCKET, Socket);
public:
	bool init();
	TcpConnection();
	~TcpConnection();
	bool create(bool bKeepAlive=false);
	bool connect(const char* ip, unsigned short port,int nBlockSec);
	int send(const char* buff, int len, int flags = 0);
	int recv(char* buff, int len, int flags=0);
	int close();
	void destory();
	bool check();
	bool getError();
private:

};
NS_FVU_END
#endif
