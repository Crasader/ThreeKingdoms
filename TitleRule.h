#pragma once

#include "cocos2d.h"
#include "tools/GameCommon.h"

USING_NS_CC;
using namespace std;

class TitleRule:public Ref
{
public:
    CLASS_INSTANCE(TitleRule);
    bool init();
    
    //��ȡͷ������by����
    string getTitleNameByIntegral(int integral);
    //��ȡͷ������by�ȼ�
    string getTitleNameByLevel(int level);
    //��ȡ�ȼ�idby����
    int getTitleLevelByIntegral(int integral);
    //��ȡͷ������byͷ�εȼ�
    string getTitleNameByTitleLevel(int titleLevel);
    //��ȡͷ�λ���byͷ�εȼ�
    int getTitleIntegralByTitleLevel(int titleLevel);
    //��ȡͷ����������
    int getTitleUpgradeIntegral(int titleLevel,int integral);
    
    //����ͷ�λ�ý�������
    int getTitleUpgradeReward(int titleLevel);
    
    //��ȡ������д���
    int getEvenStrokes(int titleLevel);
    
    float getTitleAttackAddition(int titleLevel);
    float getTitleSpeedAddition(int titleLevel);
private:
    ValueMap getTitleDic(int titleLevel);
    string getTitleAttribute(int titleLevel,const string& attributeName);
    ValueMap mainDic;
};



