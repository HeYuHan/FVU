#ifndef __NETSTREAM_H__
#define __NETSTREAM_H__
#include "tcp.h"
#include "Common/Define.h"
#include "msg/BaseMsg.h"
typedef ::google::protobuf::Message FVU_MSG;
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
	VAR_POINTER(TcpConnection, Connection);
public:
	NetworkStream();
	~NetworkStream();
	bool init();
	void setConnection(TcpConnection* con);
	bool writeMessagePacket(MessagePacket *p);
	bool writeMessage(FVU_MSG *msg, MSG_ID id);
	bool readMessage(FVU_MSG *msg, MSG_ID &id);
	bool readMessagePacket(MessagePacket *p);
private:

};
NS_FVU_END
#endif