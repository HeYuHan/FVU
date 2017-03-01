#ifndef __Character_H__
#define __Character_H__
#include <spine/spine-cocos2dx.h>
#include "Define.h"
#include "CharacterControl.hpp"
using namespace std;
using namespace spine;
class Character:public cocos2d::Node
{
GET_SET_POINTER(SkeletonAnimation,AnimationPlayer)
GET_SET_POINTER(CharacterControl,MoveControl)
GET_SET(cocos2d::Size,Box2D)

public:
	CREATE_FUNC(Character)
	Character();
	~Character();
	bool virtual init();
	bool loadAnimation(const string &spine_path, const string &atlas_path,float scale=1);
	bool boxContainPoint(cocos2d::Vec2 &pos);


};

#endif