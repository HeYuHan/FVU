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
<<<<<<< HEAD
	
	return true;
}

=======
	auto c = Character::create();
	c->loadAnimation("spine/actors/dark/skeleton.json","spine/actors/dark/skeleton.plist.atlas");
	c->getAnimationPlayer()->setAnimation(0, "skill_a", true);
	c->setPosition(getZeroPosition());
	addCharacter(c);
	return true;
}
Vec2 GameApp::getCenterPosition()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	Vec2 center = (origin + visibleSize) / 2;
	return center;
}
Vec2 GameApp::getZeroPosition()
{
	return Director::getInstance()->getVisibleOrigin();
}
void GameApp::addCharacter(Character *c)
{
	m_CharacterLayer->addChild(c);
}
>>>>>>> 8b3e8f9017430b96019acb8e2dc792f4d2eebd52
