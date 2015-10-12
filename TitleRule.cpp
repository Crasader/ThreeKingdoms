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

//��ȡͷ������by����
string TitleRule::getTitleNameByIntegral(int integral)
{
	return getTitleNameByTitleLevel(getTitleLevelByIntegral(integral));
}
//��ȡͷ������by�ȼ�
string TitleRule::getTitleNameByLevel(int level)
{
	//�ȼ�����ͷ�εȼ�
	return getTitleNameByTitleLevel(level);
}
//��ȡ�ȼ�idby����
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
//��ȡͷ������byͷ�εȼ�
string TitleRule::getTitleNameByTitleLevel(int titleLevel)
{
	return getTitleAttribute(titleLevel,"titleName");
}
//��ȡͷ�λ���byͷ�εȼ�
int TitleRule::getTitleIntegralByTitleLevel(int titleLevel)
{
	return Value(getTitleAttribute(titleLevel,"integral")).asInt();
}
//��ȡͷ����������
//����Ҫ����������=��ǰ���� - �ܹ�����
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

//����ͷ�λ�ý�������
int TitleRule::getTitleUpgradeReward(int titleLevel)
{
	vector<string> str = INSTANCE(BaseDataManager)->split(getTitleAttribute(titleLevel,"titleReward"),"_");
	return Value(str.at(1)).asInt();
}

//��ȡ������д���
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

