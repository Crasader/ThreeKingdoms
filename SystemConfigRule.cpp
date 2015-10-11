#include "SystemConfigRule.h"
#include "BaseDataManager.h"
#include "UserData.h"

bool SystemConfigRule::init()
{
	return true;
}

//配置信息
ValueMap SystemConfigRule::getSystemDic()
{
	return Value((INSTANCE(BaseDataManager)->getXml(SystemConfigXml))["1"]).asValueMap();
}
string SystemConfigRule::getSystemAttribute(const string& attributeName)
{
	return Value(getSystemDic()[attributeName]).asString();
}

//登陆天数-奖励
ValueMap SystemConfigRule::getLoginDic(int dayNum)
{
	return Value(INSTANCE(BaseDataManager)->getXml(LoginRewardXml)[Value(dayNum).asString()]).asValueMap();
}
string SystemConfigRule::getLoginAttribute(int dayNum, const string& attributeName)
{
	return Value(getLoginDic(dayNum)[attributeName]).asString();
}

//转盘
ValueMap SystemConfigRule::getWheelDic()
{
	return Value(INSTANCE(BaseDataManager)->getXml(WheelOfFortune)["1"]).asValueMap();
}
string SystemConfigRule::getWheelAttribute(const string& attributeName)
{
	return Value(getWheelDic()[attributeName]).asString();
}

//聚宝盆
ValueMap SystemConfigRule::getTreasureBowlDic(int times)
{
	return Value(INSTANCE(BaseDataManager)->getXml(TreasureBowl)[Value(times).asString()]).asValueMap();
}
string SystemConfigRule::getTreasureBowlAttibute(int times, const string& attributeName)
{
	return Value(getTreasureBowlDic(times)[attributeName]).asString();
}

//=============系统配置相关
//初始化元宝
int SystemConfigRule::getInitGold()
{
	return Value(getSystemAttribute("initGold")).asInt();
}
//普攻消耗
int SystemConfigRule::getAttackCost()
{
	return Value(getSystemAttribute("attackGoldCost")).asInt();
}
//最大倍率
int SystemConfigRule::getMaxMagnification()
{
	return Value(getSystemAttribute("maxMagnification")).asInt();
}
//抽水率
float SystemConfigRule::getDefaultEase()
{
	return Value(getSystemAttribute("defaultEase")).asFloat();
}
//出兵间隔时间
int SystemConfigRule::getDispatchTroopsInterval()
{
	return Value(getSystemAttribute("dispatchTroopsInterval")).asInt();
}

//出分周期变换最小时间
int SystemConfigRule::getScoreConversionCycleMinTime()
{
	return Value(getSystemAttribute("scoreConversionCycleMinTime")).asInt();
}
//出分周期变换最大时间
int SystemConfigRule::getScoreConversionCycleMaxTime()
{
	return Value(getSystemAttribute("scoreConversionCycleMaxTime")).asInt();
}
//吃分周期变换最小时间
int SystemConfigRule::getLoseScoreConversionCycleMinTime()
{
	return Value(getSystemAttribute("loseScoreConversionCycleMinTime")).asInt();
}
//吃分周期变换最小时间
int SystemConfigRule::getLoseScoreConversionCycleMaxTime()
{
	return Value(getSystemAttribute("loseScoreConversionCycleMaxTime")).asInt();
}

//出兵间隔最小值
int SystemConfigRule::getSendTroopsMinTime()
{
	return Value(getSystemAttribute("sendTroopsMinTime")).asInt();
}
//出兵间隔最大值
int SystemConfigRule::getSendTroopsMaxTime()
{
	return Value(getSystemAttribute("sendTroopsMaxTime")).asInt();
}
//出兵数量最小值
int SystemConfigRule::getSentTroopsMinNumber()
{
	return Value(getSystemAttribute("sentTroopsMinNumber")).asInt();
}
//出兵数量最大值
int SystemConfigRule::getSentTroopsMaxNumber()
{
	return Value(getSystemAttribute("sentTroopsMaxNumber")).asInt();
}

//在线奖励
int SystemConfigRule::getOnlineReward()
{
	return Value(getSystemAttribute("dailyOnlineReward")).asInt();
}
//在线奖励时间间隔
int SystemConfigRule::getOnlineRewardTime()
{
	return Value(getSystemAttribute("dailyOnlineRewardTime")).asInt();
}
//在线奖励每次次数
int SystemConfigRule::getOnlineRewardTimes()
{
	return Value(getSystemAttribute("dailyOnlineRewardCount")).asInt();
}

//每日任务次数
int SystemConfigRule::getTaskCount()
{
	return Value(getSystemAttribute("dailyTaskCount")).asInt();
}
//每日任务间隔
int SystemConfigRule::getTaskTime(bool firstTime)
{
	vector<string> str = INSTANCE(BaseDataManager)->split(getSystemAttribute("dailyTaskTimeInterval"),"_");
	if (firstTime)
	{
		return Value(str.at(0)).asInt();
	}
	return Value(str.at(1)).asInt();
}
//==================其他文件
int SystemConfigRule::getLoginReward(int dayNum)
{
	vector<string> str = INSTANCE(BaseDataManager)->split(getLoginAttribute(dayNum,"reward"),"_");
	return Value(str[1]).asInt();
}
//boss抽奖消耗
int SystemConfigRule::getBossLotteryCost()
{
	return 20;
}

//====================转盘相关==========
//正常转盘概率
string SystemConfigRule::getFirstProbability()
{
	return getWheelAttribute("firstProbability");
}
//首次打boss转盘概率
string SystemConfigRule::getSecondProbability()
{
	return getWheelAttribute("secondProbability");
}
//吃分周期怒气少于50%转盘概率
string SystemConfigRule::getThirdProbability()
{
	return getWheelAttribute("thirdProbability");
}
//获取转盘倍数
int SystemConfigRule::getWheelMultiple()
{
	//TODO:
	//概率
	//string probability;
	//if (INSTANCE(UserData)->getWheelTimes() == 0)
	//{
	//	probability = getSecondProbability();
	//}
	//if (!INSTANCE(FightManager)->getSomethingGood() && i)
	//{
	//}
	return 0;
}

//===============聚宝盆相关文件========
//获取彩金
int SystemConfigRule::getTreasureBowlWinnings(int times)
{
	return Value(getTreasureBowlAttibute(times,"goldCost")).asInt();
}
//获取元宝消耗
int SystemConfigRule::getTreasureBowlGoldCost(int times)
{
	return Value(getTreasureBowlAttibute(times,"winnings")).asInt();
}

//获取当前元宝消耗
int SystemConfigRule::getCurrentTreasureBowlGoldCost()
{
	//通关越多元宝消耗越多
	return getTreasureBowlGoldCost(INSTANCE(UserData)->getFinishChapterTimes());
}
//获取当前彩金
int SystemConfigRule::getCurrentTreasureBowlWinnings()
{
	//通关越多彩金消耗越多
	return getTreasureBowlWinnings(INSTANCE(UserData)->getFinishChapterTimes());
}
//彩池是否已满
bool SystemConfigRule::potIsFull()
{
	int currentPot = INSTANCE(UserData)->getPotGold();
	int max = getCurrentTreasureBowlGoldCost();
	if (currentPot >= max)
	{
		return true;
	}
	return false;
}

//怒气上限
int SystemConfigRule::getAngerMax()
{
	return 0;
}















