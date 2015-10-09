#include "NPCRule.h"
#include "BaseDataManager.h"
#include "ModelRule.h"
#include "tools/GameCommon.h"

bool NPCRule::init()
{
	return true;
}

//获取npc模型id
int NPCRule::getNpcModelId(int npcId)
{
	return Value(getNpcAttribute(npcId,"model")).asInt();
}

//获取NPC图片资源路径
string NPCRule::getNpcImgPath(int npcId)
{
	return INSTANCE(ModelRule)->getModelPath(getNpcModelId(npcId));
}

string NPCRule::getNpcFrameNameByNpcId(int npcId,RoleStatus status,bool containPng)
{
	return INSTANCE(ModelRule)->getModelFrameNameByModelId(getNpcModelId(npcId),status,containPng);
}

//获取npc技能id
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
