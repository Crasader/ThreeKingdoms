#pragma once

#include "cocos2d.h"
#include "tools/GameCommon.h"
#include "RoleRule.h"

USING_NS_CC;
using namespace std;

class NPCRule : public Ref
{
public:
	CLASS_INSTANCE(NPCRule);
	bool init();

public:
	//��ȡNPCͼƬ��Դ·��
	string getNpcImgPath(int npcId);
	//��ȡnpcģ��id
	int getNpcModelId(int npcId);
	//��ȡnpcͼƬ��
	string getNpcFrameNameByNpcId(int npcId,RoleStatus status,bool containPng = false);
	//��ȡnpcվ����һ֡ͼƬ��
	string getNpcFirstFrameNameByNpcId(int npcId,RoleStatus status);
	//��ȡnpc����id
	int getNpcSkillId(int npcId);

    //��ȡnpcѪ��
    int getNpcHp(int npcId);
    //��ȡnpcê��
    Vec2 getNpcAnchorPoint(int npcId);
    //��ȡnpc����
    string getNpcName(int npcId);
    //��ȡnpc����
    int getNpcType(int npcId);
    //��ȡnpc����
    int getNpcIntegral(int npcId);
    //��ȡnpc�ٶ�
    int getNpcSpeed(int npcId);
    //��ȡnpcԪ������
    int getNpcMoneyMin(int npcId);
    //��ȡnpcԪ������
    int getNpcMoneyMax(int npcId);
    //��ȡnpcԪ��
    int getNpcMoney(int npcId);
    //��ȡnpcЯ��ŭ��
    int getNpcAnger(int npcId);
    //��ȡnpc����
    float getNpcDodge(int npcId);
    //npc����
    string getNpcDesc(int npcId);
    
    //��ȡnpc�ܻ���Χ
    Size getNpcHurtSize(int npcId);
    //��ȡnpc������Χ
    Size getNpcAttackSize(int npcId);
    
    //��������
    int getNpcAttackType(int npcId);
    //��������
    float getNpcAttackProbability(int npcId);
    //վ������
    float getNpcStandProbability(int npcId);
    //���ٸ���
    float getNpcSpeedUpProbability(int npcId);
    //���ٸ���
    float getNpcSpeedDownProbability(int npcId);
    
    //�����ͷ�
    int getNpcAttackPenalty(int npcId);
private:
    ValueMap getNpcDic(int npcId);
    string getNpcAttribute(int npcId,const string& attributeName);
    ValueMap mainDic;

};
