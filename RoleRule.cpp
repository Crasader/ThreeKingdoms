#include "RoleRule.h"
#include "ModelRule.h"
#include "BaseDataManager.h"
#include "UserData.h"

bool RoleRule::init()
{
	return true;
}
//��ȡ��ɫͼƬ��
string RoleRule::getRoleFrameNameByRoleId(int roleId,RoleStatus status, bool containPng)
{
	return INSTANCE(ModelRule)->getModelFrameNameByModelId(roleId,status,containPng);
}

//��ȡ��ɫվ����һ֡
string RoleRule::getRoleFirstFrameNameByRoleId(int roleId,RoleStatus status)
{
	return INSTANCE(ModelRule)->getModelFirstFrameNameByModelId(roleId,status);
}

//��ȡ��ɫģ��ID
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

//��ȡ��ɫê��
Vec2 RoleRule::getRoleAnchorPoint(int roleId)
{
	return INSTANCE(ModelRule)->getModelAnchorPoint(roleId);
}

//��ȡ��ɫ��
string RoleRule::getRoleName(int roleId)
{
	return INSTANCE(BaseDataManager)->getLan(getRoleAttribute(roleId,"name"));
}

//��ȡ��ɫͼƬ��Դ·��
string RoleRule::getRoleImgPath(int roleId)
{
	return INSTANCE(ModelRule)->getModelPath(getRoleModelId(roleId));
}

//��ȡ��ɫ����id
int RoleRule::getRoleSkillId(int roleId)
{
	return Value(getRoleAttribute(roleId,"skillId")).asInt();
}

//��ȡ��ɫ������Чê��
Vec2 RoleRule::getRoleSkillEffectAnchorPoint(int roleId)
{
	return INSTANCE(ModelRule)->getModelSkillEffectAnchorPoint(getRoleModelId(roleId));
}
//��ȡ��ɫ�չ���Чê��
Vec2 RoleRule::getRoleAttackEffectAnchorPoint(int roleId)
{
	return INSTANCE(ModelRule)->getModelAttackEffectAnchorPoint(getRoleModelId(roleId));
}
//��ȡ��ɫ������֡��
int RoleRule::getRoleAttackFrameNum(int roleId)
{
	return 3;
}
//��ȡ��ɫ���ܹ�����֡��
int RoleRule::getRoleSkillFrameNum(int roleId)
{
	return 7;
}
//��ȡ��ɫ��󹥻�
int RoleRule::getRoleMaxAttack(int roleId)
{
	return Value(getRoleAttribute(roleId,"maxATK")).asInt();
}
//��ȡ��ɫ��͹���
int RoleRule::getRoleMinAttack(int roleId)
{
	return Value(getRoleAttribute(roleId,"minATK")).asInt();
}
//��ȡ��ɫ�ٶ�
int RoleRule::getRoleSpeed(int roleId)
{
	return Value(getRoleAttribute(roleId,"moveSpeed")).asInt();
}
//��ȡ��ɫ�����ٶ�
float RoleRule::getRoleAttackSpeed(int roleId)
{
	return Value(getRoleAttribute(roleId,"attackSpeed")).asFloat();
}

//��ɫ����
string RoleRule::getRoleDesc(int roleId)
{
	return Value(getRoleAttribute(roleId,"feature")).asString();
}

//��ȡ��ɫ������Χ
Size RoleRule::getRoleAttackSize(int roleId)
{
	return INSTANCE(ModelRule)->getModelAttackSize(getRoleModelId(roleId));
}
//��ȡ��ɫ�ܻ���Χ
Size RoleRule::getRoleHurtSize(int roleId)
{
	return INSTANCE(ModelRule)->getModelHurtSize(getRoleModelId(roleId));
}


//vip�ȼ�����
int RoleRule::getRoleVip(int roleId)
{
	return Value(getRoleAttribute(roleId,"vip")).asInt();
}
//Ԫ���������
int RoleRule::getRoleCost(int roleId)
{
	return Value(getRoleAttribute(roleId,"goldCost")).asInt();
}
//����
int RoleRule::getRoleSequence(int roleId)
{
	return Value(getRoleAttribute(roleId,"sequence")).asInt();
}
//�Ƿ�ӵ��
bool RoleRule::ownRole(int roleId)
{
	//�����ϵ�����ݿ�
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
//��ȡ��ѽ�ɫ
vector<int> RoleRule::getFreeRolesVector()
{
	vector<int> result;
	for (const auto& key : INSTANCE(BaseDataManager)->getXml(RoleXml))
	{
		//��ѡ��vip��costΪ0�Ľ�ɫid
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








