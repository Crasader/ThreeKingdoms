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
    
    //获取模型图片名
    string getModelFrameNameByModelId(int modelId,RoleStatus status,bool containPng = false);
    //获取模型站立第一帧图片名
    string getModelFirstFrameNameByModelId(int modelId,RoleStatus status);
    
    //获取模型路径
    string getModelPath(int modelId);
    //获取模型锚点
    Vec2 getModelAnchorPoint(int modelId);
    ////获取模型技能特效锚点
    //CCPoint getModelSkillEffectAnchorPoint(int modelId);
    ////获取模型普攻特效锚点
    //CCPoint getModelAttackEffectAnchorPoint(int modelId);
    ////获取模型受击范围
    //CCSize getModelHurtSize(int modelId);
    ////获取模型攻击范围
    //CCSize getModelAttackSize(int modelId);

    ////获取技能被击特效图片名
    //string getSkillHitFrameName(int skillId,bool containPng = false);
    ////获取技能被击特效锚点
    //CCPoint getSkillHitAnchorPoint(int skillId);
    
private:
    ValueMap getModelDic(int modelId);
    string getModelAttribute(int modelId,const string& attributeName);
    ValueMap mainDic;
    
    //int lastId;
    //CCDictionary *lastSubDic;
};



