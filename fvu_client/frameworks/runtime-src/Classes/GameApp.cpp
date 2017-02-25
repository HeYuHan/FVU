#include "GameApp.h"
using namespace std;

static GameApp* _globalApp = nullptr;
GameApp::GameApp():
	m_MainScene(nullptr),
	m_BackGroundLayer(nullptr),
	m_CharacterLayer(nullptr),
	m_UILayer(nullptr),
	m_DesignResolutionSize(Vec2(640,480))
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
	m_BackGroundLayer = Layer::create();
	m_CharacterLayer = Layer::create();
	m_UILayer = Layer::create();
	m_MainScene->addChild(m_BackGroundLayer);
	m_MainScene->addChild(m_CharacterLayer);
	m_MainScene->addChild(m_UILayer);
	auto director = Director::getInstance();
	auto glview = director->getOpenGLView();
	glview->setDesignResolutionSize(m_DesignResolutionSize.width, m_DesignResolutionSize.height, ResolutionPolicy::NO_BORDER);
	director->runWithScene(m_MainScene);
	


}
bool GameApp::startGame()
{
	auto c = Character::create();
	c->loadAnimation("spine/actors/boss_ghost/skeleton.json","spine/actors/boss_ghost/skeleton0.plist.atlas");
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