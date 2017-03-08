#include "networkstream.h"
NS_FVU_BEGIN
NetworkStream::NetworkStream() :
m_SendBuff(nullptr),
m_RecvBuff(nullptr),
m_WriteOffset(nullptr),
m_WritePosition(nullptr),
m_ReadOffset(nullptr),
m_ReadPosition(nullptr),
m_Connection(nullptr),
m_CacheMessage(nullptr),
m_CacheMessageLength(0)
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
	memset(m_SendBuff, 0, SEND_BUFF_LEN);
	memset(m_RecvBuff, 0, RECV_BUFF_LEN);
	m_ReadPosition = m_ReadOffset = m_SendBuff;
	m_WritePosition = m_WriteOffset = m_SendBuff;
	return true;
}
void NetworkStream::setConnection(TcpConnection* con)
{
	this->m_Connection = con;
}
bool NetworkStream::writeMessage(FVU_MSG* msg, MSG_ID id)
{
	if (!msg)return false;
	int msg_len = msg->ByteSize();
	if (msg_len <= 0)return false;
	int head_len = sizeof(MSG_HEAD);
	int id_len = sizeof(MSG_ID);
	int packet_len = msg_len + id_len + head_len;
	int data_len = msg_len + id_len;
	char* data_start = m_WriteOffset + (id_len + head_len);
	if (m_WriteOffset + packet_len > m_SendBuff + SEND_BUFF_LEN)
	{
		return false;
	}
	if (msg->SerializeToArray(data_start, msg_len))
	{
		memcpy(m_WriteOffset, (void*)&data_len, head_len);
		m_WriteOffset += head_len;
		memcpy(m_WriteOffset, (void*)&id, id_len);
		m_WriteOffset += id_len;
		m_WriteOffset += msg_len;
		return true;
	}
	return false;
}
bool NetworkStream::getMessage(FVU_MSG *msg)
{
	if (!msg)return false;
	if (!m_CacheMessage || m_CacheMessageLength==0)return false;
	bool ret = msg->ParseFromArray(m_CacheMessage, m_CacheMessageLength);
	m_CacheMessageLength = 0;
	m_CacheMessage = nullptr;
	return ret;
}
bool NetworkStream::readMessage(MSG_ID &id)
{
	int head_len = sizeof(MSG_HEAD);
	if ((m_ReadOffset - m_ReadPosition) < head_len)
	{
		return false;
	}
	MSG_HEAD data_len = 0;
	//read head
	memcpy((void*)&data_len, m_ReadPosition, head_len);
	if ((m_ReadOffset - m_ReadPosition) < (head_len + data_len))
	{
		return false;
	}
	//read id
	m_ReadPosition += head_len;
	int id_len = sizeof(MSG_ID);
	memcpy((void*)&id, m_ReadPosition, id_len);
	m_CacheMessageLength = data_len - id_len;
	m_CacheMessage = m_ReadPosition + id_len;
	m_ReadPosition += data_len;
	//move unread data
	int unread_msg_size = (m_ReadOffset - m_ReadPosition);
	if (unread_msg_size > 0)
	{
		memmove(m_RecvBuff, m_ReadPosition, unread_msg_size);
	}
	m_ReadOffset = m_RecvBuff + unread_msg_size;
	m_ReadPosition = m_RecvBuff;
	return true;
}
void NetworkStream::update()
{
	if (!m_Connection||!m_Connection->getConnected())return;
	//check error
	if (!m_Connection->check())
	{
		//µôÏß
		return;
	}
	//read
	int recv_count = 0;
	do
	{
		int max_len = (m_ReadPosition + RECV_BUFF_LEN - m_ReadOffset);
		recv_count = m_Connection->recv(m_ReadOffset, max_len);
		if (recv_count > 0)
		{
			m_ReadOffset += recv_count;
		}

	} while (recv_count > 0);
	//write
	int data_count = m_WriteOffset - m_WritePosition;
	m_WritePosition += m_Connection->send(m_WritePosition, data_count);
	//move unwrite data
	data_count = m_WriteOffset - m_WritePosition;
	if (data_count > 0)
	{
		memmove(m_SendBuff, m_WritePosition, data_count);
	}
	m_WritePosition = m_SendBuff;
	m_WriteOffset = m_SendBuff + data_count;
}
NS_FVU_END
