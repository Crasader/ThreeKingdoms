#pragma once
#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace std;

class OnlineReward : public Node
{
public:
	CREATE_FUNC(OnlineReward);
	virtual bool init();
	OnlineReward();
	~OnlineReward();

	void updateTime(float dt);
private:
	void initContent();

	ProgressTimer* bar;
	Label* label;

	void receiveHandler();
	bool receivable;


	int times;
	int money;
	int time;
};