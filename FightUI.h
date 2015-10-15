#pragma once

#include "cocos2d.h"
#include "CommonTitleBar.h"
//#include "CommonMoneyBar.h"
#include "SetBar.h"
#include "OnlineReward.h"

USING_NS_CC;
using namespace std;

class FightUI:public Layer
{
public:
	FightUI();
	~FightUI();
	CREATE_FUNC(FightUI);
	virtual bool init();

	virtual void onEnter();
	virtual void onExit();
private:
	CommonTitleBar* titleBar;
	ProgressTimer* moneyBar;

	Sprite* potSprite;
	ProgressTimer* potBar;
	Label* potLabel;
	Label* moneyLabel;
	SetBar* setBar;
	OnlineReward* onlineReward;


	int currentMoney;
	int currentIntegral;
	int currentUpgradeIntegral;

	//�����
	int maxRate;

	//��Ǯ�仯
	int differenceMoney;

	EventListenerCustom* listenerForMoney;
	EventListenerCustom* listenerForIntegral;
	EventListenerCustom* listenerForPot;
private:
	void initContent();

	void updateMoney();
	void updateIntegral();
	void updatePot();

	void showPotTips();
	void showExpTips();

	void update(float dt);
	void showMoneyAnimation();
};