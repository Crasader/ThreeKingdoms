#include "ModelRule.h"
#include "BaseDataManager.h"
#include "SkillRule.h"

bool ModelRule::init()
{
    //lastId = -1;
    //mainDic = NULL;
    return true;
}

string ModelRule::getModelFrameNameByModelId(int modelId,RoleStatus status,bool containPng)
{
    string result = Value(modelId).asString();
    switch (status) {
        case RoleStatusStand:
			result += "_stand";
            break;
        case RoleStatusWalk:
			result += "_walk";
            break;
        case RoleStatusRun:
			result += "_run";
            break;
        case RoleStatusAttack:
			result += "_attack";
            break;
        case RoleStatusAttack_1:
			result += "_attack_1";
            break;
        case RoleStatusAttack_2:
			result += "_attack_2";
            break;
        case RoleStatusAttack_3:
			result += "_attack_3";
            break;
        case RoleStatusAttack_4:
			result += "_attack_4";
            break;
        case RoleStatusAttack_5:
			result += "_attack_5";
            break;
        case RoleStatusHurt:
			result += "_hurt";
            break;
        case RoleStatusDie:
			result += "_die";
            break;
        case RoleStatusSkill:
			result += "_skill";
            break;
        case RoleStatusAttackEffect:
			result += "_attack_effect";
            break;
        case RoleStatusSkillEffect:
			result += "_skill_effect";
            break;
        default:
            break;
    }
    if(containPng){
		return result + ".png";
    }else{
        return result;
    }
}

//获取技能被击特效图片名
string ModelRule::getSkillHitFrameName(int skillId,bool containPng)
{
	string result = Value(skillId).asString();
	result += "_skill_hit";
	if (containPng)
	{
		result += ".png";
	}
	return result;
}

string ModelRule::getModelFirstFrameNameByModelId(int modelId,RoleStatus status)
{
    string result = getModelFrameNameByModelId(modelId,status);
	result += "_0000.png";
    return result;
}

//获取模型锚点
Vec2 ModelRule::getModelAnchorPoint(int modelId)
{
	float _x = Value(getModelAttribute(modelId,"pointX")).asFloat();
	float _y = Value(getModelAttribute(modelId,"pointY")).asFloat();
	return Vec2(_x,_y);
}

string ModelRule::getModelAttribute(int modelId,const string& attributeName)
{
	return getModelDic(modelId)[attributeName].asString();
}

ValueMap ModelRule::getModelDic(int modelId)
{
	if (mainDic.empty())
	{
		mainDic = INSTANCE(BaseDataManager)->getXml(ModelConfigXml);
	}
	return mainDic[Value(modelId).asString()].asValueMap();
}

//获取模型路径
string ModelRule::getModelPath(int modelId)
{
	string result("model/");
	result += Value(modelId).asString();
	return result+"/";
}

//获取模型技能特效锚点
Vec2 ModelRule::getModelSkillEffectAnchorPoint(int modelId)
{
	float _x = Value(getModelAttribute(modelId,"skillpointX")).asFloat();
	float _y = Value(getModelAttribute(modelId,"skillpointY")).asFloat();
	return Vec2(_x,_y);
}

//获取模型普攻特效锚点
Vec2 ModelRule::getModelAttackEffectAnchorPoint(int modelId)
{
	float _x = Value(getModelAttribute(modelId,"attackpointX")).asFloat();
	float _y = Value(getModelAttribute(modelId,"attackpointY")).asFloat();
	return Vec2(_x,_y);
}

//获取模型受击范围
Size ModelRule::getModelHurtSize(int modelId)
{
	string temp = getModelAttribute(modelId,"size");
	if (temp == "0")
	{
		return Size::ZERO;
	}
	vector<string> size = INSTANCE(BaseDataManager)->split(temp,"_");
	return Size(Value(size[0]).asFloat(),Value(size[1]).asFloat());
}
//获取模型攻击范围
Size ModelRule::getModelAttackSize(int modelId)
{
	string temp = getModelAttribute(modelId,"AttackSize");
	if (temp == "0")
	{
		return Size::ZERO;
	}
	vector<string> size = INSTANCE(BaseDataManager)->split(temp,"_");
	return Size(Value(size[0]).asFloat(),Value(size[1]).asFloat());
}

//获取技能被击特效锚点
Vec2 ModelRule::getSkillHitAnchorPoint(int skillId)
{
	return INSTANCE(SkillRule)->getSkillHitAnchorPoint(skillId);
}
