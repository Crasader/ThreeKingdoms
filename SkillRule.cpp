#include "SkillRule.h"
#include "BaseDataManager.h"

bool SkillRule::init()
{
    return true;
}

ValueMap SkillRule::getSkillDic(int skillId)
{
	if (mainDic.empty())
	{
		mainDic = INSTANCE(BaseDataManager)->getXml(SkillXml);
	}
	return mainDic[Value(skillId).asString()].asValueMap();
}

string SkillRule::getSkillAttribute(int skillId,const string& attributeName)
{
	return Value(getSkillDic(skillId)[attributeName]).asString();
}

//技能消耗
int SkillRule::getSkillCost(int skillId)
{
	return Value(getSkillAttribute(skillId,"anger")).asInt();
}
//技能名
string SkillRule::getSkillName(int skillId)
{
	return Value(getSkillAttribute(skillId,"name")).asString();
}
//技能被击效果锚点
Vec2 SkillRule::getSkillHitAnchorPoint(int skillId)
{
	float _x = Value(getSkillAttribute(skillId,"skillpointX")).asFloat();
	float _y = Value(getSkillAttribute(skillId,"skillpointY")).asFloat();
	return Vec2(_x,_y);
}



