#include "NPCRule.h"
#include "BaseDataManager.h"
#include "ModelRule.h"
#include "tools/GameCommon.h"
#include "tools/GameUtils.h"

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

//获取npc站立第一帧图片名
string NPCRule::getNpcFirstFrameNameByNpcId(int npcId,RoleStatus status)
{
	return INSTANCE(ModelRule)->getModelFirstFrameNameByModelId(getNpcModelId(npcId),status);
}

//获取npc血量
int NPCRule::getNpcHp(int npcId)
{
	return Value(getNpcAttribute(npcId,"hp")).asInt();
}
//获取npc锚点
Vec2 NPCRule::getNpcAnchorPoint(int npcId)
{
	return INSTANCE(ModelRule)->getModelAnchorPoint(getNpcModelId(npcId));
}
//获取npc名字
string NPCRule::getNpcName(int npcId)
{
	return INSTANCE(BaseDataManager)->getLan(getNpcAttribute(npcId,"name"));
}
//获取npc类型
int NPCRule::getNpcType(int npcId)
{
	return Value(getNpcAttribute(npcId,"type")).asInt();
}
//获取npc积分
int NPCRule::getNpcIntegral(int npcId)
{
	return Value(getNpcAttribute(npcId,"integral")).asInt();
}
//获取npc速度
int NPCRule::getNpcSpeed(int npcId)
{
	return Value(getNpcAttribute(npcId,"moveSpeed")).asInt();
}
//获取npc元宝下限
int NPCRule::getNpcMoneyMin(int npcId)
{
	return Value(getNpcAttribute(npcId,"moneylow")).asInt();
}
//获取npc元宝上限
int NPCRule::getNpcMoneyMax(int npcId)
{
	return Value(getNpcAttribute(npcId,"money")).asInt();
}
//获取npc元宝
int NPCRule::getNpcMoney(int npcId)
{
	int max = getNpcMoneyMax(npcId);
	int min = getNpcMoneyMin(npcId);
	if (max == min)
	{
		return max;
	}
	//随机生成一个min到max之间的数
	return min + INSTANCE(GameUtils)->getRandom(max - min + 1);
}
//获取npc携带怒气
int NPCRule::getNpcAnger(int npcId)
{
	return Value(getNpcAttribute(npcId,"anger")).asInt();
}
//获取npc闪避
float NPCRule::getNpcDodge(int npcId)
{
	return Value(getNpcAttribute(npcId,"dodge")).asFloat();
}
//npc描述
string NPCRule::getNpcDesc(int npcId)
{
	return Value(getNpcAttribute(npcId,"feature")).asString();
}

//获取npc受击范围
Size NPCRule::getNpcHurtSize(int npcId)
{
	return INSTANCE(ModelRule)->getModelHurtSize(getNpcModelId(npcId));
}
//获取npc攻击范围
Size NPCRule::getNpcAttackSize(int npcId)
{
	return INSTANCE(ModelRule)->getModelAttackSize(getNpcModelId(npcId));
}

//攻击类型
int NPCRule::getNpcAttackType(int npcId)
{
	return Value(getNpcAttribute(npcId,"attackType")).asInt();
}
//攻击概率
float NPCRule::getNpcAttackProbability(int npcId)
{
	return Value(getNpcAttribute(npcId,"attackProbability")).asFloat();
}
//站立概率
float NPCRule::getNpcStandProbability(int npcId)
{
	return Value(getNpcAttribute(npcId,"standbyProbability")).asFloat();
}
//加速概率
float NPCRule::getNpcSpeedUpProbability(int npcId)
{
	return Value(getNpcAttribute(npcId,"speedUpProbability")).asFloat();
}
//减速概率
float NPCRule::getNpcSpeedDownProbability(int npcId)
{
	return Value(getNpcAttribute(npcId,"speedDownProbability")).asFloat();
}

//攻击惩罚
int NPCRule::getNpcAttackPenalty(int npcId)
{
	return Value(getNpcAttribute(npcId,"attackPenalty")).asInt();
}











 