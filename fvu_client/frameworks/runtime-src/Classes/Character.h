#ifndef __Character_H__
#define __Character_H__
#include <spine/spine-cocos2dx.h>
#include "Define.h"
using namespace std;
using namespace spine;
class Character:public cocos2d::Node
{
GET_SET_POINTER(SkeletonAnimation,AnimationPlayer)

public:
	Character();
	~Character();
	bool virtual init();
	bool loadAnimation(const string &spine_path, const string &atlas_path);
	CREATE_FUNC(Character)

};

#endif