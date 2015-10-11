/************************************************************************/
/* 解析SystemConfig文件  
systemConfig.xml
loginReward.xml
WheelOfFortune.xml
treasureBowl.xml*/
/************************************************************************/
#pragma once

#include "cocos2d.h"
#include "tools/GameCommon.h"

USING_NS_CC;
using namespace std;

class SystemConfigRule : public Ref
{
public:
	CLASS_INSTANCE(SystemConfigRule);
	bool init();
	//============系统配置信息相关================
	//初始化元宝
	int getInitGold();
	//普攻消耗
	int getAttackCost();
	//最大倍率
	int getMaxMagnification();
	//抽水率
	float getDefaultEase();
	//出兵间隔时间
	int getDispatchTroopsInterval();


	//出分周期变换最小时间
	int getScoreConversionCycleMinTime();
	//出分周期变换最大时间
	int getScoreConversionCycleMaxTime();
	//吃分周期变换最小时间
	int getLoseScoreConversionCycleMinTime();
	//吃分周期变换最小时间
	int getLoseScoreConversionCycleMaxTime();

	//出兵间隔最小值
	int getSendTroopsMinTime();
	//出兵间隔最大值
	int getSendTroopsMaxTime();
	//出兵数量最小值
	int getSentTroopsMinNumber();
	//出兵数量最大值
	int getSentTroopsMaxNumber();


	//在线奖励
	int getOnlineReward();
	//在线奖励时间间隔
	int getOnlineRewardTime();
	//在线奖励每次次数
	int getOnlineRewardTimes();

	//每日任务次数
	int getTaskCount();
	//每日任务间隔
	int getTaskTime(bool firstTime);	

	//===================登陆奖励相关==============
	int getLoginReward(int dayNum);
	//boss抽奖消耗
	int getBossLotteryCost();

	//====================转盘相关==========
	//正常转盘概率
	string getFirstProbability();
	//首次打boss转盘概率
	string getSecondProbability();
	//吃分周期怒气少于50%转盘概率
	string getThirdProbability();
	//获取转盘倍数
	int getWheelMultiple();

	//=============聚宝盆相关===============
	//获取彩金
	int getTreasureBowlWinnings(int times);
	//获取元宝消耗
	int getTreasureBowlGoldCost(int times);

	//获取当前元宝消耗
	int getCurrentTreasureBowlGoldCost();
	//获取当前彩金
	int getCurrentTreasureBowlWinnings();
	//彩池是否已满
	bool potIsFull();

	//怒气上限
	int getAngerMax();


	////crp权重
	//float getCRPWeights();
	////抽水率权重
	//float getDPWeights();
	////ccp权重
	//float getCCPWeights();
	////acp权重
	//float getACPWeights();

public:
	
private:
	//配置信息
    ValueMap getSystemDic();
    string getSystemAttribute(const string& attributeName);

	//登陆天数-奖励
	ValueMap getLoginDic(int dayNum);
	string getLoginAttribute(int dayNum, const string& attributeName);

	//转盘
	ValueMap getWheelDic();
	string getWheelAttribute(const string& attributeName);

	//聚宝盆
	ValueMap getTreasureBowlDic(int times);
	string getTreasureBowlAttibute(int times, const string& attributeName);

};
