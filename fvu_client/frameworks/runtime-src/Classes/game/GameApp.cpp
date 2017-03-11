#include "GameApp.h"
using namespace std;
#include "msg/testmsg.pb.h"
NS_FVU_BEGIN
static GameApp* _globalApp = nullptr;
GameApp::GameApp():
	m_MainScene(nullptr),
	m_DesignResolutionSize(Vec2(640,480)),
	m_GlobalLevel(nullptr),
	m_NetStream(nullptr),
	m_Connection(nullptr)
{
}

GameApp::~GameApp()
{
	if (m_NetStream)
	{
		delete m_NetStream;
	}
	if (m_Connection)
	{
		delete m_Connection;
	}
	m_NetStream = nullptr;
	m_Connection = nullptr;
}
GameApp* GameApp::getInstance()
{
	if (!_globalApp)
	{
		_globalApp = new (std::nothrow) GameApp();
		if(!_globalApp->init())
		{
			delete _globalApp;
			_globalApp = nullptr;
			return nullptr;
		}
		_globalApp->retain();
		_globalApp->autorelease();
		
		
	}
	return _globalApp;
}
bool GameApp::createNetwork()
{
	//tcp init
	m_Connection = new TcpConnection();
	if (!m_Connection->init())
	{
		delete m_Connection;
		m_Connection = nullptr;
		return false;
	}
	if (!m_Connection->create())
	{
		delete m_Connection;
		m_Connection = nullptr;
		return false;
	}
	if (!m_Connection->connect("127.0.0.1", 9898, 100))
	{
		delete m_Connection;
		m_Connection = nullptr;
		return false;
	}
	m_NetStream = new NetworkStream();
	m_NetStream->init();
	m_NetStream->setConnection(m_Connection);
	return true;
}
bool GameApp::init()
{
	
	m_DesignResolutionSize = Size(640, 480);
	m_MainScene = Scene::create();
	m_GlobalLevel = Level::getInstance();
	m_MainScene->addChild(m_GlobalLevel);
	auto director = Director::getInstance();
	auto glview = director->getOpenGLView();
	glview->setDesignResolutionSize(m_DesignResolutionSize.width, m_DesignResolutionSize.height, ResolutionPolicy::NO_BORDER);
	director->runWithScene(m_MainScene);
	director->getScheduler()->schedule(CC_SCHEDULE_SELECTOR(GameApp::tcpUpdate), this, 0.02f, false);
	return true;
}
bool GameApp::startGame()
{
	//m_GlobalLevel->setBackGround("stan/battlebackground/battle_background_arena_01.png");
	
	m_GlobalLevel->begin();
	auto c = Character::create();
	//c->loadAnimation("spine/actors/boss_firegirl/skeleton.json", "spine/actors/boss_firegirl/skeleton_tex.atlas",0.5f);
	//c->getAnimationPlayer()->setAnimation(0, "walk", true);
	//c->getAnimationPlayer()->setDebugBonesEnabled(true);
	c->setPosition(m_GlobalLevel->getFightAreaOrigin());
	m_GlobalLevel->addCharacter(c);
#if 1
	if (!createNetwork())return false;
	TestMessage* tm = new TestMessage();
	tm->set_boolvalue(true);
	tm->set_doublevalue(0.01);
	tm->set_floatvalue(2.0f);
	tm->set_int64value(5);
	tm->set_stringvalue("124asdfasf");
	tm->set_bytesvalue("你好123asfaf");
	tm->set_uintvalue(12);
	ChildMessage* child = tm->add_childmessage();
	child->set_fixedvalue(2);
	bool ret = m_NetStream->writeMessage(tm,1);
	delete tm;
#endif
	return true;
}
void GameApp::tcpUpdate(float frame_time)
{
	if (m_NetStream)
	{
		m_NetStream->update();
		MSG_ID msg_id;
		if (m_NetStream->readMessage(msg_id))
		{
			TestMessage* tm = new TestMessage();
			if (m_NetStream->getMessage(tm))
			{
				auto str = tm->stringvalue();
				auto str2 = tm->bytesvalue();
			}

			delete tm;
			return;
		}
	}
}
NS_FVU_END
