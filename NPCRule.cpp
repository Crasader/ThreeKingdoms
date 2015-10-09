#include "NPCRule.h"
#include "BaseDataManager.h"
#include "ModelRule.h"
#include "tools/GameCommon.h"
#include "tools/GameUtils.h"

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

//��ȡnpcվ����һ֡ͼƬ��
string NPCRule::getNpcFirstFrameNameByNpcId(int npcId,RoleStatus status)
{
	return INSTANCE(ModelRule)->getModelFirstFrameNameByModelId(getNpcModelId(npcId),status);
}

//��ȡnpcѪ��
int NPCRule::getNpcHp(int npcId)
{
	return Value(getNpcAttribute(npcId,"hp")).asInt();
}
//��ȡnpcê��
Vec2 NPCRule::getNpcAnchorPoint(int npcId)
{
	return INSTANCE(ModelRule)->getModelAnchorPoint(getNpcModelId(npcId));
}
//��ȡnpc����
string NPCRule::getNpcName(int npcId)
{
	return INSTANCE(BaseDataManager)->getLan(getNpcAttribute(npcId,"name"));
}
//��ȡnpc����
int NPCRule::getNpcType(int npcId)
{
	return Value(getNpcAttribute(npcId,"type")).asInt();
}
//��ȡnpc����
int NPCRule::getNpcIntegral(int npcId)
{
	return Value(getNpcAttribute(npcId,"integral")).asInt();
}
//��ȡnpc�ٶ�
int NPCRule::getNpcSpeed(int npcId)
{
	return Value(getNpcAttribute(npcId,"moveSpeed")).asInt();
}
//��ȡnpcԪ������
int NPCRule::getNpcMoneyMin(int npcId)
{
	return Value(getNpcAttribute(npcId,"moneylow")).asInt();
}
//��ȡnpcԪ������
int NPCRule::getNpcMoneyMax(int npcId)
{
	return Value(getNpcAttribute(npcId,"money")).asInt();
}
//��ȡnpcԪ��
int NPCRule::getNpcMoney(int npcId)
{
	int max = getNpcMoneyMax(npcId);
	int min = getNpcMoneyMin(npcId);
	if (max == min)
	{
		return max;
	}
	//�������һ��min��max֮�����
	return min + INSTANCE(GameUtils)->getRandom(max - min + 1);
}
//��ȡnpcЯ��ŭ��
int NPCRule::getNpcAnger(int npcId)
{
	return Value(getNpcAttribute(npcId,"anger")).asInt();
}
//��ȡnpc����
float NPCRule::getNpcDodge(int npcId)
{
	return Value(getNpcAttribute(npcId,"dodge")).asFloat();
}
//npc����
string NPCRule::getNpcDesc(int npcId)
{
	return Value(getNpcAttribute(npcId,"feature")).asString();
}

//��ȡnpc�ܻ���Χ
Size NPCRule::getNpcHurtSize(int npcId)
{
	return INSTANCE(ModelRule)->getModelHurtSize(getNpcModelId(npcId));
}
//��ȡnpc������Χ
Size NPCRule::getNpcAttackSize(int npcId)
{
	return INSTANCE(ModelRule)->getModelAttackSize(getNpcModelId(npcId));
}

//��������
int NPCRule::getNpcAttackType(int npcId)
{
	return Value(getNpcAttribute(npcId,"attackType")).asInt();
}
//��������
float NPCRule::getNpcAttackProbability(int npcId)
{
	return Value(getNpcAttribute(npcId,"attackProbability")).asFloat();
}
//վ������
float NPCRule::getNpcStandProbability(int npcId)
{
	return Value(getNpcAttribute(npcId,"standbyProbability")).asFloat();
}
//���ٸ���
float NPCRule::getNpcSpeedUpProbability(int npcId)
{
	return Value(getNpcAttribute(npcId,"speedUpProbability")).asFloat();
}
//���ٸ���
float NPCRule::getNpcSpeedDownProbability(int npcId)
{
	return Value(getNpcAttribute(npcId,"speedDownProbability")).asFloat();
}

//�����ͷ�
int NPCRule::getNpcAttackPenalty(int npcId)
{
	return Value(getNpcAttribute(npcId,"attackPenalty")).asInt();
}











 