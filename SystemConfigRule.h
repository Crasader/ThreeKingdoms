/************************************************************************/
/* ����SystemConfig�ļ�  
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
	//============ϵͳ������Ϣ���================
	//��ʼ��Ԫ��
	int getInitGold();
	//�չ�����
	int getAttackCost();
	//�����
	int getMaxMagnification();
	//��ˮ��
	float getDefaultEase();
	//�������ʱ��
	int getDispatchTroopsInterval();


	//�������ڱ任��Сʱ��
	int getScoreConversionCycleMinTime();
	//�������ڱ任���ʱ��
	int getScoreConversionCycleMaxTime();
	//�Է����ڱ任��Сʱ��
	int getLoseScoreConversionCycleMinTime();
	//�Է����ڱ任��Сʱ��
	int getLoseScoreConversionCycleMaxTime();

	//���������Сֵ
	int getSendTroopsMinTime();
	//����������ֵ
	int getSendTroopsMaxTime();
	//����������Сֵ
	int getSentTroopsMinNumber();
	//�����������ֵ
	int getSentTroopsMaxNumber();


	//���߽���
	int getOnlineReward();
	//���߽���ʱ����
	int getOnlineRewardTime();
	//���߽���ÿ�δ���
	int getOnlineRewardTimes();

	//ÿ���������
	int getTaskCount();
	//ÿ��������
	int getTaskTime(bool firstTime);	

	//===================��½�������==============
	int getLoginReward(int dayNum);
	//boss�齱����
	int getBossLotteryCost();

	//====================ת�����==========
	//����ת�̸���
	string getFirstProbability();
	//�״δ�bossת�̸���
	string getSecondProbability();
	//�Է�����ŭ������50%ת�̸���
	string getThirdProbability();
	//��ȡת�̱���
	int getWheelMultiple();

	//=============�۱������===============
	//��ȡ�ʽ�
	int getTreasureBowlWinnings(int times);
	//��ȡԪ������
	int getTreasureBowlGoldCost(int times);

	//��ȡ��ǰԪ������
	int getCurrentTreasureBowlGoldCost();
	//��ȡ��ǰ�ʽ�
	int getCurrentTreasureBowlWinnings();
	//�ʳ��Ƿ�����
	bool potIsFull();

	//ŭ������
	int getAngerMax();


	////crpȨ��
	//float getCRPWeights();
	////��ˮ��Ȩ��
	//float getDPWeights();
	////ccpȨ��
	//float getCCPWeights();
	////acpȨ��
	//float getACPWeights();

public:
	
private:
	//������Ϣ
    ValueMap getSystemDic();
    string getSystemAttribute(const string& attributeName);

	//��½����-����
	ValueMap getLoginDic(int dayNum);
	string getLoginAttribute(int dayNum, const string& attributeName);

	//ת��
	ValueMap getWheelDic();
	string getWheelAttribute(const string& attributeName);

	//�۱���
	ValueMap getTreasureBowlDic(int times);
	string getTreasureBowlAttibute(int times, const string& attributeName);

};
