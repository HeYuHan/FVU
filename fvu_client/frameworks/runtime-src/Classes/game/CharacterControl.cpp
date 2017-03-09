//
//  CharacterControl.cpp
//  fvu_client
//
//  Created by heyuhan on 17/2/27.
//
//

#include "CharacterControl.hpp"
USING_NS_CC;
NS_FVU_BEGIN
bool CharacterControl::init()
{
    m_MoveTarget=nullptr;
	m_ActionState = ActionState::None;
    m_MoveType=ByDestination;
    m_MoveSpeed=0;
	m_MoveTime = 0;
    m_MoveDirection=Vec2::ZERO;
    m_MoveDestination=Vec2::ZERO;
	
    return true;
}
ActionInterval* CharacterControl::createMoveAction()
{
	if (!m_MoveTarget)return nullptr;
	StopActionState(ActionState::Move);
	ActionInterval* move_action = nullptr;
	if (m_MoveType == ByDestination)
	{
		float dis = m_MoveDestination.distance(m_MoveTarget->getPosition());
		if (dis == 0)return nullptr;
		float move_time = dis / m_MoveSpeed;
		move_action = MoveTo::create(move_time, m_MoveDestination);
	}
	else if (m_MoveType == ByDirection)
	{
		move_action = MoveBy::create(m_MoveTime, m_MoveDirection.getNormalized()*m_MoveSpeed);
	}
	return move_action;
}
void CharacterControl::BeginMove()
{

	ActionInterval* move_action = createMoveAction();
	if (move_action)
	{
		SetActionStateEnabled(ActionState::Move, true);
		std::function<void()> call_back = [&]
		{
			StopActionState(ActionState::Move);
		};
		CallFunc* move_finsh = CallFunc::create(call_back);
		move_action = Sequence::create(move_action, move_finsh, nullptr);
		move_action->setTag(ActionState::Move);
		m_MoveTarget->runAction(move_action);
	}
}
void CharacterControl::BeginMove(std::function<void()> &move_finish_callback)
{
	ActionInterval* move_action = createMoveAction();
	if (move_action)
	{
		SetActionStateEnabled(ActionState::Move, true);
		std::function<void()> call_back = [&]
		{
			StopActionState(ActionState::Move);
			move_finish_callback(); 
		};
		CallFunc* move_finsh = CallFunc::create(call_back);
		move_action = Sequence::create(move_action, move_finsh, nullptr);
		move_action->setTag(ActionState::Move);
		m_MoveTarget->runAction(move_action);
	}
}
void CharacterControl::StopActionState(ActionState state)
{
	if (!m_MoveTarget)return;
	if (m_ActionState&state>0)
	{
		m_MoveTarget->stopActionByTag(state);
		SetActionStateEnabled(state, false);
	}
}
void CharacterControl::SetActionStateEnabled(int state, bool enabled)
{
	if (enabled)
	{
		m_ActionState |= state;
	}
	else
	{
		m_ActionState &= ~state;
	}
}
NS_FVU_END
