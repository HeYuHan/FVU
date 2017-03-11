#include "Character.h"
#include "cocos2d.h"
#include "Level.h"
#include "Common/tool.h"
USING_NS_CC;
NS_FVU_BEGIN
Character::Character():
m_AnimationPlayer(nullptr),
m_MoveControl(nullptr),
m_BodyBox(Size(50,75))
{

}
Character::~Character()
{
	if (m_MoveControl)
	{
		m_MoveControl->release();
	}
}
bool Character::init()
{
	m_MoveControl = CharacterControl::create();
	m_MoveControl->retain();
	m_MoveControl->setMoveTarget(this);
	m_MoveControl->setMoveSpeed(100);
	return true;
}
bool Character::loadAnimation(const string &spine_path, const string &atlas_path,float scale)
{
	if (m_AnimationPlayer)
	{
		removeChild(m_AnimationPlayer);
		m_AnimationPlayer = nullptr;
	}
	m_AnimationPlayer = SkeletonAnimation::createWithJsonFile(spine_path, atlas_path,scale);
	addChild(m_AnimationPlayer);
	return true;
}
bool Character::bodyContainPoint(Vec2 &pos)
{
	Vec2 left_bottom = getPosition();
	left_bottom.x -= m_BodyBox.width / 2;
	Rect boxRect;
	boxRect.origin = left_bottom;
	boxRect.size = m_BodyBox;
	return boxRect.containsPoint(pos);
}
void Character::drawWantMovePoistion(cocos2d::DrawNode* drawNode)
{
	
	drawNode->drawLine(getPosition(), m_WantMovePosition, Color4F::GREEN);
	drawNode->drawCircle(m_WantMovePosition, m_BodyBox.width/2, 0, 20, true, 1, tan(CC_DEGREES_TO_RADIANS(Level::getInstance()->getFightAreaAngle())), Color4F::RED);
	Vec2 arrow = m_WantMovePosition + Vec2(0, cos(getCurrentTime()*6.28*3) * 10 + 10);
	drawNode->drawTriangle(arrow, arrow + Vec2(-10, 10), arrow + Vec2(10, 10), Color4F::RED);
}
void Character::Move()
{
	m_MoveControl->setMoveDestination(m_WantMovePosition);
	m_MoveControl->BeginMove();
}
NS_FVU_END
