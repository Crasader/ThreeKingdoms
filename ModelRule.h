#pragma once

#include "cocos2d.h"
#include "tools/GameCommon.h"
#include "RoleRule.h"

USING_NS_CC;
using namespace std;

class ModelRule:public Ref
{
public:
    CLASS_INSTANCE(ModelRule);
    bool init();
    
    //��ȡģ��ͼƬ��
    string getModelFrameNameByModelId(int modelId,RoleStatus status,bool containPng = false);
    //��ȡģ��վ����һ֡ͼƬ��
    string getModelFirstFrameNameByModelId(int modelId,RoleStatus status);
    
    //��ȡģ��·��
    string getModelPath(int modelId);
    //��ȡģ��ê��
    Vec2 getModelAnchorPoint(int modelId);
    //��ȡģ�ͼ�����Чê��
    Vec2 getModelSkillEffectAnchorPoint(int modelId);
    //��ȡģ���չ���Чê��
    Vec2 getModelAttackEffectAnchorPoint(int modelId);
    //��ȡģ���ܻ���Χ
    Size getModelHurtSize(int modelId);
    //��ȡģ�͹�����Χ
    Size getModelAttackSize(int modelId);

    //��ȡ���ܱ�����ЧͼƬ��
    string getSkillHitFrameName(int skillId,bool containPng = false);
    //��ȡ���ܱ�����Чê��
    Vec2 getSkillHitAnchorPoint(int skillId);
    
private:
    ValueMap getModelDic(int modelId);
    string getModelAttribute(int modelId,const string& attributeName);
    ValueMap mainDic;
    
    //int lastId;
    //CCDictionary *lastSubDic;
};



