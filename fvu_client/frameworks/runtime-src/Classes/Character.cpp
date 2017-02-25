#include "Character.h"
Character::Character():
m_AnimationPlayer(nullptr)
{

}
Character::~Character()
{

}
bool Character::init()
{
	return true;
}
bool Character::loadAnimation(const string &spine_path, const string &atlas_path)
{
	if (m_AnimationPlayer)
	{
		removeChild(m_AnimationPlayer);
		m_AnimationPlayer = nullptr;
	}
	m_AnimationPlayer = SkeletonAnimation::createWithJsonFile(spine_path, atlas_path,0.5f);
	addChild(m_AnimationPlayer);
	return true;
}