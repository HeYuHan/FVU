#include <google/protobuf/message.h>
#include "Common/Define.h"
NS_FVU_BEGIN
typedef unsigned int MSG_HEAD;
typedef unsigned short MSG_ID;
typedef ::google::protobuf::Message FVU_MSG;
class MessagePacket
{
	GET_SET_POINTER(google::protobuf::Message, Message);
	GET_SET(MSG_ID, ID);

};

NS_FVU_END