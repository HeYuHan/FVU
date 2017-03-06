#include "networkstream.h"
NS_FVU_BEGIN
NetworkStream::NetworkStream() :
m_SendBuff(nullptr),
m_RecvBuff(nullptr),
m_WriteOffset(nullptr),
m_WritePosition(nullptr),
m_ReadOffset(nullptr),
m_ReadPosition(nullptr),
m_Connection(nullptr)
{

}
NetworkStream::~NetworkStream()
{
	if (m_SendBuff)
	{
		delete[] m_SendBuff;
	}
	if (m_RecvBuff)
	{
		delete[] m_RecvBuff;
	}
	m_SendBuff = nullptr;
	m_RecvBuff = nullptr;

	m_ReadPosition = nullptr;
	m_ReadOffset = nullptr;

	m_WriteOffset = nullptr;
	m_WritePosition = nullptr;
}
bool NetworkStream::init()
{
	m_SendBuff = new char[SEND_BUFF_LEN];
	m_RecvBuff = new char[RECV_BUFF_LEN];
	return true;
}
void NetworkStream::setConnection(TcpConnection* con)
{
	this->m_Connection = con;
}
bool NetworkStream::writeMessagePacket(MessagePacket *p)
{
	if (!p)return false;
	return writeMessage(p->getMessage(), p->getID());
}
bool NetworkStream::writeMessage(FVU_MSG* msg, MSG_ID id)
{
	if (!msg)return false;
	int msg_len = msg->ByteSize();
	if (msg_len <= 0)return false;
	int head_len = sizeof(MSG_HEAD);
	int id_len = sizeof(MSG_ID);
	int packet_len = msg_len + id_len + head_len;
	char* data_start = m_WriteOffset + (id_len + head_len);
	if (m_WriteOffset + packet_len < m_SendBuff + SEND_BUFF_LEN)
	{
		return false;
	}
	if (msg->SerializeToArray(data_start, msg_len))
	{
		memcpy(m_WriteOffset, (void*)&packet_len, head_len);
		m_WriteOffset += head_len;
		memcpy(m_WriteOffset, (void*)&id, id_len);
		m_WriteOffset += head_len;
		m_WriteOffset += msg_len;
		return true;
	}
	return false;
}
bool NetworkStream::readMessage(FVU_MSG *msg, MSG_ID &id)
{
	if (!msg)return false;
	int head_len = sizeof(MSG_HEAD);
	if ((m_ReadOffset - m_ReadPosition)<head_len)
	{
		return false;
	}
	MSG_HEAD data_len = 0;
	//read head
	memcpy((void*)&data_len,m_ReadPosition,head_len);
	if ((m_ReadOffset - m_ReadPosition) < (head_len + data_len))
	{
		return false;
	}
	//read id
	m_ReadPosition += head_len;
	int id_len = sizeof(MSG_ID);
	memcpy((void*)&id, m_ReadPosition, id_len);
	//read data
	m_ReadPosition += id_len;
	bool ret = msg->ParseFromArray(m_ReadPosition, data_len);
	m_ReadPosition += data_len;
	return ret;
}
NS_FVU_END
