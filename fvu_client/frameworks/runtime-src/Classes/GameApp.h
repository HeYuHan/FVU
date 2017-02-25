#pragma once
#ifndef __GAMEAPP_H__
#define __GAMEAPP_H__
#include "cocos2d.h"
#include "Character.h"
#include "Define.h"
USING_NS_CC;
class GameApp:public cocos2d::Ref
{
	GET_SET_POINTER(Scene, MainScene)
	GET_SET_POINTER(Layer,BackGroundLayer)
	GET_SET_POINTER(Layer, CharacterLayer)
	GET_SET_POINTER(Layer, UILayer)
	GET_SET(Size, DesignResolutionSize)
public:
	virtual ~GameApp();
private:
	GameApp();
public:
	static GameApp* getInstance();
	void init();
	bool startGame();
	Vec2 getCenterPosition();
	Vec2 getZeroPosition();
	void addCharacter(Character* c);
};
#endif

