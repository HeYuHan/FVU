#ifndef __Character_H__
#define __Character_H__
#include <spine/spine-cocos2dx.h>
#include "Common/Define.h"
#include "CharacterControl.hpp"
using namespace std;
using namespace spine;
NS_FVU_BEGIN
class Character:public cocos2d::Node
{
GET_SET_POINTER(SkeletonAnimation,AnimationPlayer)
GET_SET_POINTER(CharacterControl,MoveControl)
GET_SET(cocos2d::Size,Box2D)
GET_SET(int,UID)

public:
	CREATE_FUNC(Character)
	Character();
	~Character();
	bool virtual init();
	bool loadAnimation(const string &spine_path, const string &atlas_path,float scale=1);
	bool boxContainPoint(cocos2d::Vec2 &pos);


};
NS_FVU_END
#endif