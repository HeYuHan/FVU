#include "tool.h"
#include "cocos2d.h"
USING_NS_CC;
NS_FVU_BEGIN
long getCurrentTime()
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return tv.tv_sec * 1000 + tv.tv_usec / 1000;
}
NS_FVU_END