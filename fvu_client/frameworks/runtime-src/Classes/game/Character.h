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
	GET_SET_POINTER(SkeletonAnimation, AnimationPlayer);
	GET_SET(cocos2d::Size, BodyBox);
	GET_SET(int, UID);
	GET_SET(cocos2d::Vec2, WantMovePosition);
private:
	VAR_POINTER(CharacterControl, MoveControl);

public:
	CREATE_FUNC(Character)
	Character();
	~Character();
	bool virtual init();
	bool loadAnimation(const string &spine_path, const string &atlas_path,float scale=1);
	bool bodyContainPoint(cocos2d::Vec2 &pos);
	void drawWantMovePoistion(cocos2d::DrawNode* drawNode);
	void Move();
};
NS_FVU_END
#endif