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
    m_MoveType=ByDestination;
    m_MoveSpeed=0;
    m_MoveDirection=Vec2::ZERO;
    m_MoveDestination=Vec2::ZERO;
    return true;
}
NS_FVU_END
