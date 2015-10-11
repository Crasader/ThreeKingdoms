#include "SystemConfigRule.h"
#include "BaseDataManager.h"
#include "UserData.h"

bool SystemConfigRule::init()
{
	return true;
}

//������Ϣ
ValueMap SystemConfigRule::getSystemDic()
{
	return Value((INSTANCE(BaseDataManager)->getXml(SystemConfigXml))["1"]).asValueMap();
}
string SystemConfigRule::getSystemAttribute(const string& attributeName)
{
	return Value(getSystemDic()[attributeName]).asString();
}

//��½����-����
ValueMap SystemConfigRule::getLoginDic(int dayNum)
{
	return Value(INSTANCE(BaseDataManager)->getXml(LoginRewardXml)[Value(dayNum).asString()]).asValueMap();
}
string SystemConfigRule::getLoginAttribute(int dayNum, const string& attributeName)
{
	return Value(getLoginDic(dayNum)[attributeName]).asString();
}

//ת��
ValueMap SystemConfigRule::getWheelDic()
{
	return Value(INSTANCE(BaseDataManager)->getXml(WheelOfFortune)["1"]).asValueMap();
}
string SystemConfigRule::getWheelAttribute(const string& attributeName)
{
	return Value(getWheelDic()[attributeName]).asString();
}

//�۱���
ValueMap SystemConfigRule::getTreasureBowlDic(int times)
{
	return Value(INSTANCE(BaseDataManager)->getXml(TreasureBowl)[Value(times).asString()]).asValueMap();
}
string SystemConfigRule::getTreasureBowlAttibute(int times, const string& attributeName)
{
	return Value(getTreasureBowlDic(times)[attributeName]).asString();
}

//=============ϵͳ�������
//��ʼ��Ԫ��
int SystemConfigRule::getInitGold()
{
	return Value(getSystemAttribute("initGold")).asInt();
}
//�չ�����
int SystemConfigRule::getAttackCost()
{
	return Value(getSystemAttribute("attackGoldCost")).asInt();
}
//�����
int SystemConfigRule::getMaxMagnification()
{
	return Value(getSystemAttribute("maxMagnification")).asInt();
}
//��ˮ��
float SystemConfigRule::getDefaultEase()
{
	return Value(getSystemAttribute("defaultEase")).asFloat();
}
//�������ʱ��
int SystemConfigRule::getDispatchTroopsInterval()
{
	return Value(getSystemAttribute("dispatchTroopsInterval")).asInt();
}

//�������ڱ任��Сʱ��
int SystemConfigRule::getScoreConversionCycleMinTime()
{
	return Value(getSystemAttribute("scoreConversionCycleMinTime")).asInt();
}
//�������ڱ任���ʱ��
int SystemConfigRule::getScoreConversionCycleMaxTime()
{
	return Value(getSystemAttribute("scoreConversionCycleMaxTime")).asInt();
}
//�Է����ڱ任��Сʱ��
int SystemConfigRule::getLoseScoreConversionCycleMinTime()
{
	return Value(getSystemAttribute("loseScoreConversionCycleMinTime")).asInt();
}
//�Է����ڱ任��Сʱ��
int SystemConfigRule::getLoseScoreConversionCycleMaxTime()
{
	return Value(getSystemAttribute("loseScoreConversionCycleMaxTime")).asInt();
}

//���������Сֵ
int SystemConfigRule::getSendTroopsMinTime()
{
	return Value(getSystemAttribute("sendTroopsMinTime")).asInt();
}
//����������ֵ
int SystemConfigRule::getSendTroopsMaxTime()
{
	return Value(getSystemAttribute("sendTroopsMaxTime")).asInt();
}
//����������Сֵ
int SystemConfigRule::getSentTroopsMinNumber()
{
	return Value(getSystemAttribute("sentTroopsMinNumber")).asInt();
}
//�����������ֵ
int SystemConfigRule::getSentTroopsMaxNumber()
{
	return Value(getSystemAttribute("sentTroopsMaxNumber")).asInt();
}

//���߽���
int SystemConfigRule::getOnlineReward()
{
	return Value(getSystemAttribute("dailyOnlineReward")).asInt();
}
//���߽���ʱ����
int SystemConfigRule::getOnlineRewardTime()
{
	return Value(getSystemAttribute("dailyOnlineRewardTime")).asInt();
}
//���߽���ÿ�δ���
int SystemConfigRule::getOnlineRewardTimes()
{
	return Value(getSystemAttribute("dailyOnlineRewardCount")).asInt();
}

//ÿ���������
int SystemConfigRule::getTaskCount()
{
	return Value(getSystemAttribute("dailyTaskCount")).asInt();
}
//ÿ��������
int SystemConfigRule::getTaskTime(bool firstTime)
{
	vector<string> str = INSTANCE(BaseDataManager)->split(getSystemAttribute("dailyTaskTimeInterval"),"_");
	if (firstTime)
	{
		return Value(str.at(0)).asInt();
	}
	return Value(str.at(1)).asInt();
}
//==================�����ļ�
int SystemConfigRule::getLoginReward(int dayNum)
{
	vector<string> str = INSTANCE(BaseDataManager)->split(getLoginAttribute(dayNum,"reward"),"_");
	return Value(str[1]).asInt();
}
//boss�齱����
int SystemConfigRule::getBossLotteryCost()
{
	return 20;
}

//====================ת�����==========
//����ת�̸���
string SystemConfigRule::getFirstProbability()
{
	return getWheelAttribute("firstProbability");
}
//�״δ�bossת�̸���
string SystemConfigRule::getSecondProbability()
{
	return getWheelAttribute("secondProbability");
}
//�Է�����ŭ������50%ת�̸���
string SystemConfigRule::getThirdProbability()
{
	return getWheelAttribute("thirdProbability");
}
//��ȡת�̱���
int SystemConfigRule::getWheelMultiple()
{
	//TODO:
	//����
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

//===============�۱�������ļ�========
//��ȡ�ʽ�
int SystemConfigRule::getTreasureBowlWinnings(int times)
{
	return Value(getTreasureBowlAttibute(times,"goldCost")).asInt();
}
//��ȡԪ������
int SystemConfigRule::getTreasureBowlGoldCost(int times)
{
	return Value(getTreasureBowlAttibute(times,"winnings")).asInt();
}

//��ȡ��ǰԪ������
int SystemConfigRule::getCurrentTreasureBowlGoldCost()
{
	//ͨ��Խ��Ԫ������Խ��
	return getTreasureBowlGoldCost(INSTANCE(UserData)->getFinishChapterTimes());
}
//��ȡ��ǰ�ʽ�
int SystemConfigRule::getCurrentTreasureBowlWinnings()
{
	//ͨ��Խ��ʽ�����Խ��
	return getTreasureBowlWinnings(INSTANCE(UserData)->getFinishChapterTimes());
}
//�ʳ��Ƿ�����
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

//ŭ������
int SystemConfigRule::getAngerMax()
{
	return 0;
}















