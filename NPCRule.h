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
	//��ȡnpc����id
	int getNpcSkillId(int npcId);
private:
    ValueMap getNpcDic(int npcId);
    string getNpcAttribute(int npcId,const string& attributeName);
    ValueMap mainDic;

};
