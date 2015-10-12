#include "TitleRule.h"
#include "BaseDataManager.h"

bool TitleRule::init()
{
    return true;
}

ValueMap TitleRule::getTitleDic(int titleLevel)
{
	if (mainDic.empty())
	{
		mainDic = INSTANCE(BaseDataManager)->getXml(TitleXml);
	}
	return Value(mainDic[Value(titleLevel).asString()]).asValueMap();
}

string TitleRule::getTitleAttribute(int titleLevel,const string& attributeName)
{
	return Value(getTitleDic(titleLevel)[attributeName]).asString();
}

//获取头衔名称by积分
string TitleRule::getTitleNameByIntegral(int integral)
{
	return getTitleNameByTitleLevel(getTitleLevelByIntegral(integral));
}
//获取头衔名称by等级
string TitleRule::getTitleNameByLevel(int level)
{
	//等级就是头衔等级
	return getTitleNameByTitleLevel(level);
}
//获取等级idby积分
int TitleRule::getTitleLevelByIntegral(int integral)
{
	if (mainDic.empty())
	{
		mainDic = INSTANCE(BaseDataManager)->getXml(TitleXml);
	}

	int integralTemp = 0;
	int titleLevelTemp = 0;

	vector<int> keyVec;
	for (const auto& key : mainDic)
	{
		integralTemp += Value(Value(key.second).asValueMap()["integral"]).asInt();
		if (integral >= integralTemp)
		{
			titleLevelTemp = Value(key.first).asInt();
		}
		else
		{
			break;
		}
	}

	return titleLevelTemp;
}
//获取头衔名称by头衔等级
string TitleRule::getTitleNameByTitleLevel(int titleLevel)
{
	return getTitleAttribute(titleLevel,"titleName");
}
//获取头衔积分by头衔等级
int TitleRule::getTitleIntegralByTitleLevel(int titleLevel)
{
	return Value(getTitleAttribute(titleLevel,"integral")).asInt();
}
//获取头衔升级积分
//还需要的升级积分=当前积分 - 总共积分
int TitleRule::getTitleUpgradeIntegral(int titleLevel,int integral)
{
	int totleIntegral = 0;
	for (int i = titleLevel; i>0;i--)
	{
		totleIntegral += getTitleIntegralByTitleLevel(i);
	}
	integral -= totleIntegral;
	return integral;
}

//升级头衔获得奖励积分
int TitleRule::getTitleUpgradeReward(int titleLevel)
{
	vector<string> str = INSTANCE(BaseDataManager)->split(getTitleAttribute(titleLevel,"titleReward"),"_");
	return Value(str.at(1)).asInt();
}

//获取最大连招次数
int TitleRule::getEvenStrokes(int titleLevel)
{
	return Value(getTitleAttribute(titleLevel,"evenStrokes")).asInt();
}

float TitleRule::getTitleAttackAddition(int titleLevel)
{
	return Value(getTitleAttribute(titleLevel,"addAttackSpeedPercentage")).asFloat();
}
float TitleRule::getTitleSpeedAddition(int titleLevel)
{
	return Value(getTitleAttribute(titleLevel,"addMoveSpeedPercentage")).asFloat();
}

