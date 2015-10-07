#include "RoleRule.h"
#include "ModelRule.h"
#include "BaseDataManager.h"

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
