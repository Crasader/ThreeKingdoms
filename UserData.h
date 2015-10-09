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
	//当前role id
	CC_SYNTHESIZE(int,currentRoleId,CurrentRoleId);
	//当前场景id
	CC_SYNTHESIZE(int,currentSceneId,CurrentSceneId);

};