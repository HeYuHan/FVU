#ifndef __LEVEL_H__
#define __LEVEL_H__
#include "Define.h"
#include "cocos2d.h"
#include "Character.h"
class Level:public cocos2d::Node
{
private:
	cocos2d::Sprite* m_BackGround;
public:
	Level();
	~Level();
	CREATE_FUNC(Level)
	bool virtual init();
	void addCharacter(Character* c);
public:
	static Level* getInstance();
	static Vec2 getCenterPosition();
	static Vec2 getZeroPosition();
private:

};

#endif