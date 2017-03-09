#ifndef __LEVEL_H__
#define __LEVEL_H__
#include "Common/Define.h"
#include "cocos2d.h"
#include "Character.h"
NS_FVU_BEGIN
typedef enum
{
	NotDraw=1<<0,Draw=1<<1
}DarwState;
class Level:public cocos2d::Layer
{
	GET_SET_POINTER(cocos2d::DrawNode, DrawNode);
	GET_SET(cocos2d::Vector<Character*>, CharacterList);
	GET_SET_POINTER(cocos2d::EventListenerTouchOneByOne, TouchListener);
	GET_SET(float, FightAreaAngle);
	GET_SET(int, FightAreaDrawState);
	GET_SET(cocos2d::Rect, FightArea);
	GET_SET_POINTER(Character, SelectedCharacter);


private:
	VAR_POINTER(cocos2d::Vec2, FightAreaPoints);
	VAR_POINTER(cocos2d::Sprite, BackGround);

	
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
	void caculateFightArea();
	cocos2d::Vec2 getFightAreaOrigin();
	cocos2d::Size getFightAreaSize();
private:
	void glDraw(float frame_time);
	void cleanCharacterList();
	bool onLevelTouchBegan(cocos2d::Touch* t, cocos2d::Event* e);
	void onLevelTouchMoved(cocos2d::Touch* t, cocos2d::Event* e);
	void onLevelTouchEnded(cocos2d::Touch* t, cocos2d::Event* e);
public:
	static Level* getInstance();
	static cocos2d::Vec2 getCenterPosition();
	static cocos2d::Vec2 getZeroPosition();
	static cocos2d::Vec2 rotatePoint(cocos2d::Vec2 &origin, cocos2d::Vec2 &point,float d_angle);
private:

};
NS_FVU_END
#endif