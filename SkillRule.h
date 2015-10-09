#pragma once

#include "cocos2d.h"
#include "tools/GameCommon.h"

USING_NS_CC;
using namespace std;

class SkillRule:public Ref
{
public:
    CLASS_INSTANCE(SkillRule);
    bool init();
    
	//技能消耗
	int getSkillCost(int skillId);
	//技能名
	string getSkillName(int skillId);
	//技能被击效果锚点
	Vec2 getSkillHitAnchorPoint(int skillId);
private:
    ValueMap getSkillDic(int skillId);
    string getSkillAttribute(int skillId,const string& attributeName);
    ValueMap mainDic;
};



