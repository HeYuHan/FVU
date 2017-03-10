#ifndef __NETSTREAM_H__
#define __NETSTREAM_H__
#include "tcp.h"
#include "Common/Define.h"
#include "msg/allmsg.h"
NS_FVU_BEGIN
#define RECV_BUFF_LEN 1024*10
#define SEND_BUFF_LEN 1024*10
class NetworkStream
{
private:
	VAR_POINTER(char, SendBuff);
	VAR_POINTER(char, RecvBuff);
	VAR_POINTER(char, WriteOffset);
	VAR_POINTER(char, WritePosition);
	VAR_POINTER(char, ReadOffset);
	VAR_POINTER(char, ReadPosition);
	VAR_POINTER(char, CacheMessage);
	VAR(int, CacheMessageLength);
	VAR_POINTER(TcpConnection, Connection);
public:
	NetworkStream();
	~NetworkStream();
	bool init();
	void setConnection(TcpConnection* con);
	bool writeMessage(FVU_MSG *msg, MSG_ID id);
	bool getMessage(FVU_MSG *msg);
	bool readMessage(MSG_ID &id);
	void update();
private:

};
NS_FVU_END
#endif