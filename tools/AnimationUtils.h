#pragma once

#include "cocos2d.h"
#include "GameCommon.h"
#include "RoleRule.h"

USING_NS_CC;
using namespace std;

class AnimationUtils:public Ref
{
public:
	CLASS_INSTANCE(AnimationUtils);
	bool init();

	Animation* getModelAnimation(int modelId,const string& fileName,const string& frameName,float duration = 0.1f);
	Animation* getModelAnimation(int modelId,const string& fileName,const string& frameName,float duration,int startIndex,int endIndex);

	Animate* getModelAnimate(int modelId,RoleStatus status,float duration);

	Animation* getCommonAnimation(const string& fileName,const string& frameName, float duration = 0.1f);

private:
	//根据文件名创建动画
	Animation* getAnimation(const string& frameName,float duration);
	Animation* getAnimation(const string& frameName,float duration,int startIndex,int endIndex);
};
