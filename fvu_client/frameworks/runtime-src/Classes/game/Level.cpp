#include "Level.h"
USING_NS_CC;
NS_FVU_BEGIN
Level* gLevel = nullptr;
Level* Level::getInstance()
{
	if (!gLevel)
	{
		gLevel = Level::create();
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
Vec2 Level::rotatePoint(cocos2d::Vec2 &origin, cocos2d::Vec2 &point,float d_angle)
{
	Vec2 result;
	float r_angle = CC_DEGREES_TO_RADIANS(d_angle);
	float dx = point.x - origin.x;
	float dy = point.y - origin.y;
	float cos_a = cos(r_angle);
	float sin_a = sin(r_angle);
	result.x = dx*cos_a - dx*sin_a + origin.x;
	result.y = dy*sin_a + dy*cos_a + origin.y;
	return result;
}
Level::Level():
	m_BackGround(nullptr),
	m_DrawNode(nullptr),
	m_TouchListener(nullptr),
	m_FightAreaAngle(10),
	m_FightAreaPoints(nullptr),
	m_FightAreaDrawState(DarwState::NotDraw),
	m_SelectedCharacter(nullptr)
{

}
Level::~Level()
{
	if (m_FightAreaPoints)
	{
		delete[] m_FightAreaPoints;
		m_FightAreaPoints = nullptr;
	}
}
bool Level::init()
{
	if (!Node::init())return false;
	m_FightAreaPoints = new Vec2[4];
	
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
void Level::caculateFightArea()
{
	Vec2 origin = m_FightArea.origin + getZeroPosition();
	Vec2 size = m_FightArea.size;
	m_FightAreaPoints[0] = origin;
	float offset_x = tan(CC_DEGREES_TO_RADIANS(m_FightAreaAngle))*m_FightArea.size.height;
	m_FightAreaPoints[1] = origin+Vec2(offset_x,size.y);
	m_FightAreaPoints[2] = origin+size;
	m_FightAreaPoints[3] = origin + Vec2(size.x - offset_x, 0);
}
Vec2 Level::getFightAreaOrigin()
{
	return m_FightArea.origin + getZeroPosition();
}
Size Level::getFightAreaSize()
{
	return m_FightArea.size;
}
bool Level::onLevelTouchBegan(cocos2d::Touch* t, cocos2d::Event* e)
{
	log("OnLevelTouchBegan");
	Vec2 touchPos = t->getLocation();
	for (int i = 0; i < m_CharacterList.size(); i++)
	{
		auto c = m_CharacterList.at(i);
		if (c->bodyContainPoint(touchPos))
		{
			m_SelectedCharacter = c;
			return true;
		}
	}
	//ture 表示接受本次触摸，不再向下传递该事件
	return false;
}
void Level::onLevelTouchMoved(cocos2d::Touch* t, cocos2d::Event* e)
{
	
	if (m_SelectedCharacter)
	{
		m_SelectedCharacter->setWantMovePosition(t->getLocation());
	}
}
void Level::onLevelTouchEnded(cocos2d::Touch* t, cocos2d::Event* e)
{
	if (m_SelectedCharacter)
	{
		m_SelectedCharacter->Move();
	}
	m_SelectedCharacter = nullptr;
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
	m_FightArea.origin = Vec2(10,5);
	Size screen_size = Director::getInstance()->getVisibleSize();
	m_FightArea.size = Size(screen_size.width-20,screen_size.height-10);
	caculateFightArea();
	setFightAreaDrawState(DarwState::Draw);
}
void Level::end()
{
	this->getEventDispatcher()->pauseEventListenersForTarget(this);
	cleanCharacterList();
}
void Level::update(float delta)
{
	glDraw(delta);
}
void Level::glDraw(float frame_time)
{
	m_DrawNode->clear();

	if ((m_FightAreaDrawState&DarwState::Draw) > 0)
	{
		m_DrawNode->drawPolygon(m_FightAreaPoints, 4, Color4F::GRAY, 1, Color4F::YELLOW);
	}
#ifdef TEST_CHRACTER_BOX

	for (auto &c : m_CharacterList)
	{
		Vec2 left_bottom = c->getPosition();
		left_bottom.x -= c->getBodyBox().width / 2;
		Vec2 right_top = left_bottom + c->getBodyBox();
		m_DrawNode->drawRect(left_bottom, right_top, Color4F::ORANGE);
	}
#endif
	if (m_SelectedCharacter)
	{
		m_SelectedCharacter->drawWantMovePoistion(m_DrawNode);
	}

}
NS_FVU_END