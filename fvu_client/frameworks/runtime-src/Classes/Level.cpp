#include "Level.h"
USING_NS_CC;
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
	m_BackGround(nullptr)
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
	auto c = Character::create();
	c->loadAnimation("spine/actors/boss_ghost/skeleton.json", "spine/actors/boss_ghost/skeleton0.plist.atlas");
	c->getAnimationPlayer()->setAnimation(0, "skill_a", true);
	c->setPosition(getZeroPosition());
	addCharacter(c);
	return true;
}
void Level::addCharacter(Character *c)
{
	addChild(c);
}