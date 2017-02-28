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
	
	return true;
}

