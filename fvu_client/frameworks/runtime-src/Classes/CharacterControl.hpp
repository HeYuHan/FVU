//
//  CharacterControl.hpp
//  fvu_client
//
//  Created by heyuhan on 17/2/27.
//
//

#ifndef CharacterControl_hpp
#define CharacterControl_hpp

#include "cocos2d.h"
#include "Define.h"
typedef enum
{
    ByDirection,ByDestination
}MoveType;
class CharacterControl:public cocos2d::Ref
{
    GET_SET_POINTER(cocos2d::Node, MoveTarget)
    GET_SET(float,MoveSpeed)
    GET_SET(cocos2d::Vec2,MoveDirection)
    GET_SET(cocos2d::Vec2,MoveDestination)
    GET_SET(MoveType,MoveType)
public:
    CREATE_FUNC(CharacterControl);
    bool init();
};

#endif /* CharacterControl_hpp */
