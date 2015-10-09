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
	//获取NPC图片资源路径
	string getNpcImgPath(int npcId);
	//获取npc模型id
	int getNpcModelId(int npcId);
	//获取npc图片名
	string getNpcFrameNameByNpcId(int npcId,RoleStatus status,bool containPng = false);
	//获取npc技能id
	int getNpcSkillId(int npcId);
private:
    ValueMap getNpcDic(int npcId);
    string getNpcAttribute(int npcId,const string& attributeName);
    ValueMap mainDic;

};
