#pragma once
#ifndef __GAMEAPP_H__
#define __GAMEAPP_H__
#include "cocos2d.h"
#include "Level.h"
#include "Define.h"
USING_NS_CC;
class GameApp:public cocos2d::Ref
{
	GET_SET_POINTER(Scene, MainScene)
	GET_SET_POINTER(Level,GlobalLevel)
	GET_SET(Size, DesignResolutionSize)
	GET_SET(unsigned int,ID)

public:
	virtual ~GameApp();
private:
	GameApp();
public:
	static GameApp* getInstance();
	void init();
	bool startGame();

	
};
#endif

