#pragma once

#include "cocos2d.h"
#include "tools/GameCommon.h"

USING_NS_CC;
using namespace std;

class SkillRule:public Ref
{
public:
    CLASS_INSTANCE(SkillRule);
    bool init();
    
	//��������
	int getSkillCost(int skillId);
	//������
	string getSkillName(int skillId);
	//���ܱ���Ч��ê��
	Vec2 getSkillHitAnchorPoint(int skillId);
private:
    ValueMap getSkillDic(int skillId);
    string getSkillAttribute(int skillId,const string& attributeName);
    ValueMap mainDic;
};



