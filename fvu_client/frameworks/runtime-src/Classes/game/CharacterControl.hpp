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
#include "Common/Define.h"
NS_FVU_BEGIN
typedef enum
{
    ByDirection,ByDestination
}MoveType;
typedef enum
{
	None=1<<0,Move=1<<1, Jump=1<<2
}ActionState;
class CharacterControl:public cocos2d::Ref
{
	GET_SET_POINTER(cocos2d::Node, MoveTarget)
	GET_SET(float, MoveSpeed)
	GET_SET(float, MoveTime)
	GET_SET(cocos2d::Vec2, MoveDirection)
	GET_SET(cocos2d::Vec2, MoveDestination)
	GET_SET(MoveType, MoveType)
private:
	VAR(int, ActionState);
private:
	cocos2d::ActionInterval* createMoveAction();
	void SetActionStateEnabled(int state, bool enabled);
public:
    CREATE_FUNC(CharacterControl);
    bool init();
	void BeginMove();
	void BeginMove(std::function<void()> &move_finish_callback);
	void StopActionState(ActionState state);
};
NS_FVU_END
#endif /* CharacterControl_hpp */
