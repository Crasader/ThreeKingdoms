#include "NPCRule.h"
#include "BaseDataManager.h"
#include "ModelRule.h"
#include "tools/GameCommon.h"

bool NPCRule::init()
{
	return true;
}

//��ȡnpcģ��id
int NPCRule::getNpcModelId(int npcId)
{
	return Value(getNpcAttribute(npcId,"model")).asInt();
}

//��ȡNPCͼƬ��Դ·��
string NPCRule::getNpcImgPath(int npcId)
{
	return INSTANCE(ModelRule)->getModelPath(getNpcModelId(npcId));
}

string NPCRule::getNpcFrameNameByNpcId(int npcId,RoleStatus status,bool containPng)
{
	return INSTANCE(ModelRule)->getModelFrameNameByModelId(getNpcModelId(npcId),status,containPng);
}

//��ȡnpc����id
int NPCRule::getNpcSkillId(int npcId)
{
	return Value(getNpcAttribute(npcId,"skillId")).asInt();
}

ValueMap NPCRule::getNpcDic(int npcId)
{
	if (mainDic.empty())
	{
		mainDic = INSTANCE(BaseDataManager)->getXml(SoldierXml);
	}
	return mainDic[Value(npcId).asString()].asValueMap();
}

string NPCRule::getNpcAttribute(int npcId,const string& attributeName)
{
	return getNpcDic(npcId)[attributeName].asString();
}
