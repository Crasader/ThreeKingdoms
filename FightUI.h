#pragma once

#include "cocos2d.h"
#include "CommonTitleBar.h"

USING_NS_CC;
using namespace std;

class FightUI:public Layer
{
public:
	FightUI();
	~FightUI();
	CREATE_FUNC(FightUI);
	virtual bool init();
private:
	CommonTitleBar* titleBar;
private:
	void initContent();
};