#ifndef __LEVEL_H__
#define __LEVEL_H__
#include "Define.h"
#include "cocos2d.h"
#include "Character.h"
NS_FVU_BEGIN
class Level:public cocos2d::Layer
{
	GET_SET_POINTER(cocos2d::DrawNode, DrawNode)
	GET_SET(cocos2d::Vector<Character*>, CharacterList)
	GET_SET_POINTER(cocos2d::EventListenerTouchOneByOne, TouchListener);
private:
	cocos2d::Sprite* m_BackGround;
public:
	Level();
	~Level();
	CREATE_FUNC(Level)
	bool virtual init();
	virtual void update(float delta);
	void begin();
	void end();
	void addCharacter(Character* c);
	void setBackGround(const string &sprite_name, ResourceType res_type = TEXTURE);
private:
	void cleanCharacterList();
	bool onLevelTouchBegan(cocos2d::Touch* t, cocos2d::Event* e);
	void onLevelTouchMoved(cocos2d::Touch* t, cocos2d::Event* e);
	void onLevelTouchEnded(cocos2d::Touch* t, cocos2d::Event* e);
public:
	static Level* getInstance();
	static cocos2d::Vec2 getCenterPosition();
	static cocos2d::Vec2 getZeroPosition();
private:

};
NS_FVU_END
#endif