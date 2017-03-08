#include "Character.h"
USING_NS_CC;
NS_FVU_BEGIN
Character::Character():
m_AnimationPlayer(nullptr),
m_MoveControl(nullptr),
m_Box2D(Size(100,150))
{

}
Character::~Character()
{

}
bool Character::init()
{
	m_MoveControl = CharacterControl::create();
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
bool Character::boxContainPoint(Vec2 &pos)
{
	Vec2 left_bottom = getPosition();
	left_bottom.x -= m_Box2D.width / 2;
	Rect boxRect;
	boxRect.origin = left_bottom;
	boxRect.size = m_Box2D;
	return boxRect.containsPoint(pos);
}
NS_FVU_END