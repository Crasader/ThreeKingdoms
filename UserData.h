#pragma once

#include "cocos2d.h"
#include "tools/GameCommon.h"

USING_NS_CC;

class UserData : public Ref
{
public:
	CLASS_INSTANCE(UserData);
	bool init();
public:
	//��ǰrole id
	CC_SYNTHESIZE(int,currentRoleId,CurrentRoleId);

};