#pragma once

#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace std;

class CommonMoneyBar : public Node
{
public:
	CommonMoneyBar();
	~CommonMoneyBar();
	CREATE_FUNC(CommonMoneyBar);
	virtual bool init();

	void updateBar();
private:
	void initContent();

	ProgressTimer* moneyBar;
	Label* moneyLabel;

};