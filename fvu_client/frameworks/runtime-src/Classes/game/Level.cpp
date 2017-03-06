#include "Level.h"
USING_NS_CC;
NS_FVU_BEGIN
Level* gLevel = nullptr;
Level* Level::getInstance()
{
	if (!gLevel)
	{
		gLevel = Level::create();
		gLevel->init();
	}
	return gLevel;
}
Vec2 Level::getCenterPosition()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	Vec2 center = (origin + visibleSize) / 2;
	return center;
}
Vec2 Level::getZeroPosition()
{
	return Director::getInstance()->getVisibleOrigin();
}
Level::Level():
	m_BackGround(nullptr),
	m_DrawNode(nullptr),
	m_TouchListener(nullptr)
{

}
Level::~Level()
{

}
bool Level::init()
{
	if (!Node::init())return false;
	m_BackGround = Sprite::create();
	addChild(m_BackGround);
	m_DrawNode = DrawNode::create();
	addChild(m_DrawNode);
	scheduleUpdate();
	m_TouchListener = EventListenerTouchOneByOne::create();
	m_TouchListener->setSwallowTouches(true);
	m_TouchListener->onTouchBegan = CC_CALLBACK_2(Level::onLevelTouchBegan, this);
	m_TouchListener->onTouchMoved = CC_CALLBACK_2(Level::onLevelTouchMoved, this);
	m_TouchListener->onTouchEnded = CC_CALLBACK_2(Level::onLevelTouchEnded, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(m_TouchListener, this);
	return true;
}
void Level::addCharacter(Character *c)
{
	addChild(c);
	m_CharacterList.pushBack(c);
}

void Level::setBackGround(const string &sprite_name, ResourceType res_type /* = TEXTURE */)
{
	if (res_type == TEXTURE)
	{
		Texture2D* tex = Director::getInstance()->getTextureCache()->addImage(sprite_name);
		if (tex)
		{
			m_BackGround->setTexture(tex);
			Rect texRect;
			texRect.origin = Vec2::ZERO;
			texRect.size = tex->getContentSize();
			m_BackGround->setTextureRect(texRect);
		}
	}
	else
	{
		SpriteFrame* frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(sprite_name);
		if (frame)
		{
			m_BackGround->setSpriteFrame(frame);
		}
	}
	m_BackGround->setPosition(getCenterPosition());
}
bool Level::onLevelTouchBegan(cocos2d::Touch* t, cocos2d::Event* e)
{
	log("OnLevelTouchBegan");
	//ture 表示接受本次触摸，不再向下传递该事件
	return true;
}
void Level::onLevelTouchMoved(cocos2d::Touch* t, cocos2d::Event* e)
{
	Vec2 touchPos = t->getLocation();
	for (int i = 0; i < m_CharacterList.size(); i++)
	{
		auto c = m_CharacterList.at(i);
		if (c->boxContainPoint(touchPos))
		{
			log("touch character:%d", i);
		}
	}

}
void Level::onLevelTouchEnded(cocos2d::Touch* t, cocos2d::Event* e)
{
	log("OnLevelTouchEnded");
}
void Level::cleanCharacterList()
{
	for (auto &c : m_CharacterList)
	{
		removeChild(c);
	}
	m_CharacterList.clear();
}
void Level::begin()
{
	this->getEventDispatcher()->resumeEventListenersForTarget(this);
	
}
void Level::end()
{
	this->getEventDispatcher()->pauseEventListenersForTarget(this);
	cleanCharacterList();
}
void Level::update(float delta)
{
#ifdef TEST_CHRACTER_BOX
	m_DrawNode->clear();
	for (auto &c : m_CharacterList)
	{
		Vec2 left_bottom = c->getPosition();
		left_bottom.x -= c->getBox2D().width / 2;
		Vec2 right_top = left_bottom + c->getBox2D();
		m_DrawNode->drawRect(left_bottom, right_top, Color4F::GREEN);
	}
#endif
}
NS_FVU_END