//
//  BaseDataManager.h
//  threeKingdoms
//
//  xml文件解析类
//
//
#pragma once

#include <iostream>
#include "tools/GameCommon.h"
#include "cocos2d.h"

using namespace std;
USING_NS_CC;

#define SystemConfigXml "SystemConfig.xml"
#define SoldierXml "Soldier.xml"
#define SkillXml "Skill.xml"
#define ScenesXml "Scenes.xml"
#define RoleXml "Role.xml"
#define BaseFormationXml "BaseFormation.xml"
#define ModelConfigXml "ModelConfig.xml"
#define SystemConfigXml "SystemConfig.xml"
#define TitleXml "Title.xml"
#define LoginRewardXml "LoginReward.xml"
#define WheelOfFortune "WheelOfFortune.xml"
#define TreasureBowl "TreasureBowl.xml"
#define TaskXml "DailyTasks.xml"
#define RechargeXml "Recharge.xml"

class BaseDataManager:public Ref
{
public:
    CLASS_INSTANCE(BaseDataManager);
    bool init();
    
    ValueMap getXml(const string& xmlPath);
    
    string getLan(string param);
    
    void removeAllXml();

	vector<string> split(string str,string pattern);
private:
    ValueMap xmlDic;
    ValueMap lanDic;
    
    void loadLan();

};

