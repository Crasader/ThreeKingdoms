#include "RoleRule.h"
#include "ModelRule.h"
#include "BaseDataManager.h"
#include "UserData.h"

bool RoleRule::init()
{
	return true;
}
//获取角色图片名
string RoleRule::getRoleFrameNameByRoleId(int roleId,RoleStatus status, bool containPng)
{
	return INSTANCE(ModelRule)->getModelFrameNameByModelId(roleId,status,containPng);
}

//获取角色站立第一帧
string RoleRule::getRoleFirstFrameNameByRoleId(int roleId,RoleStatus status)
{
	return INSTANCE(ModelRule)->getModelFirstFrameNameByModelId(roleId,status);
}

//获取角色模型ID
int RoleRule::getRoleModelId(int roleId)
{
	return Value(getRoleAttribute(roleId,"model")).asInt();
}
string RoleRule::getRoleAttribute(int roleId,const string& attributeName)
{
	return getRoleDic(roleId)[attributeName].asString();
}

ValueMap RoleRule::getRoleDic(int roleId)
{
	if (mainDic.empty())
	{
		mainDic = INSTANCE(BaseDataManager)->getXml(RoleXml);
	}
	
	lastSubDic = mainDic[Value(roleId).asString()].asValueMap();
	return lastSubDic;
}

vector<int> RoleRule::getAllRoleId()
{
	vector<int> result;
	for (const auto& key : INSTANCE(BaseDataManager)->getXml(RoleXml))
	{
		result.push_back(Value(key.first).asInt());
	}
	for (auto& i : result)
	{
		log("roleXml:%d",i);
	}
	return result;
}

//获取角色锚点
Vec2 RoleRule::getRoleAnchorPoint(int roleId)
{
	return INSTANCE(ModelRule)->getModelAnchorPoint(roleId);
}

//获取角色名
string RoleRule::getRoleName(int roleId)
{
	return INSTANCE(BaseDataManager)->getLan(getRoleAttribute(roleId,"name"));
}

//获取角色图片资源路径
string RoleRule::getRoleImgPath(int roleId)
{
	return INSTANCE(ModelRule)->getModelPath(getRoleModelId(roleId));
}

//获取角色技能id
int RoleRule::getRoleSkillId(int roleId)
{
	return Value(getRoleAttribute(roleId,"skillId")).asInt();
}

//获取角色技能特效锚点
Vec2 RoleRule::getRoleSkillEffectAnchorPoint(int roleId)
{
	return INSTANCE(ModelRule)->getModelSkillEffectAnchorPoint(getRoleModelId(roleId));
}
//获取角色普攻特效锚点
Vec2 RoleRule::getRoleAttackEffectAnchorPoint(int roleId)
{
	return INSTANCE(ModelRule)->getModelAttackEffectAnchorPoint(getRoleModelId(roleId));
}
//获取角色攻击点帧数
int RoleRule::getRoleAttackFrameNum(int roleId)
{
	return 3;
}
//获取角色技能攻击点帧数
int RoleRule::getRoleSkillFrameNum(int roleId)
{
	return 7;
}
//获取角色最大攻击
int RoleRule::getRoleMaxAttack(int roleId)
{
	return Value(getRoleAttribute(roleId,"maxATK")).asInt();
}
//获取角色最低攻击
int RoleRule::getRoleMinAttack(int roleId)
{
	return Value(getRoleAttribute(roleId,"minATK")).asInt();
}
//获取角色速度
int RoleRule::getRoleSpeed(int roleId)
{
	return Value(getRoleAttribute(roleId,"moveSpeed")).asInt();
}
//获取角色攻击速度
float RoleRule::getRoleAttackSpeed(int roleId)
{
	return Value(getRoleAttribute(roleId,"attackSpeed")).asFloat();
}

//角色描述
string RoleRule::getRoleDesc(int roleId)
{
	return Value(getRoleAttribute(roleId,"feature")).asString();
}

//获取角色攻击范围
Size RoleRule::getRoleAttackSize(int roleId)
{
	return INSTANCE(ModelRule)->getModelAttackSize(getRoleModelId(roleId));
}
//获取角色受击范围
Size RoleRule::getRoleHurtSize(int roleId)
{
	return INSTANCE(ModelRule)->getModelHurtSize(getRoleModelId(roleId));
}


//vip等级限制
int RoleRule::getRoleVip(int roleId)
{
	return Value(getRoleAttribute(roleId,"vip")).asInt();
}
//元宝购买费用
int RoleRule::getRoleCost(int roleId)
{
	return Value(getRoleAttribute(roleId,"goldCost")).asInt();
}
//排序
int RoleRule::getRoleSequence(int roleId)
{
	return Value(getRoleAttribute(roleId,"sequence")).asInt();
}
//是否拥有
bool RoleRule::ownRole(int roleId)
{
	//这个关系到数据库
	//vector<int> roles = INSTANCE(BaseDataManager)->split(INSTANCE(UserData)->getRoles(),"_");
	//for (auto& r : roles)
	//{
	//	if(r == roleId)
	//	{
	//		return true;
	//	}
	//}
	return false;
}
//获取免费角色
vector<int> RoleRule::getFreeRolesVector()
{
	vector<int> result;
	for (const auto& key : INSTANCE(BaseDataManager)->getXml(RoleXml))
	{
		//挑选出vip和cost为0的角色id
		int vip = getRoleVip(Value(key.first).asInt);
		int goldCost = getRoleVip(Value(key.first).asInt);
		if (vip == 0 && goldCost == 0)
		{
			result.push_back(Value(key.first).asInt());
		}
	}
	return result;
}

string RoleRule::getFreeRoles()
{
	string result("");
	vector<int> freeRoles = getFreeRolesVector();
	for (int i = 0;i < freeRoles.size();i++)
	{
		if (i==0)
		{
			result.append(Value(freeRoles[i]).asString());
		}
		else
		{
			result.append("_" + Value(freeRoles[i]).asString());
		}
	}
	return result;
}








