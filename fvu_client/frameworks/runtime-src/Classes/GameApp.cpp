#include "GameApp.h"
using namespace std;

static GameApp* _globalApp = nullptr;
GameApp::GameApp():
	m_MainScene(nullptr),
	m_DesignResolutionSize(Vec2(640,480)),
	m_GlobalLevel(nullptr)
{
}

GameApp::~GameApp()
{
}
GameApp* GameApp::getInstance()
{
	if (!_globalApp)
	{
		_globalApp = new (std::nothrow) GameApp();
		_globalApp->init();
	}
	return _globalApp;
}
void GameApp::init()
{
	m_DesignResolutionSize = Size(640, 480);
	m_MainScene = Scene::create();
	m_GlobalLevel = Level::getInstance();
	m_MainScene->addChild(m_GlobalLevel);
	auto director = Director::getInstance();
	auto glview = director->getOpenGLView();
	glview->setDesignResolutionSize(m_DesignResolutionSize.width, m_DesignResolutionSize.height, ResolutionPolicy::NO_BORDER);
	director->runWithScene(m_MainScene);
}
bool GameApp::startGame()
{
	m_GlobalLevel->setBackGround("stan/battlebackground/battle_background_arena_01.png");
	auto c = Character::create();
	//"spine/actors/dark/skeleton.json","spine/actors/dark/skeleton.plist.atlas"
	//"spine/actors/boss_ghost/skeleton.json", "spine/actors/boss_ghost/skeleton0.plist.atlas"
	c->loadAnimation("spine/actors/boss_firegirl/skeleton.json", "spine/actors/boss_firegirl/skeleton_tex.atlas",0.5f);
	c->getAnimationPlayer()->setAnimation(0, "walk", true);
	c->getAnimationPlayer()->setDebugBonesEnabled(true);
	c->setPosition(Level::getCenterPosition());
	m_GlobalLevel->addCharacter(c);
	m_GlobalLevel->begin();
	return true;
}
