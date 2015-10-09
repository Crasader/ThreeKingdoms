#pragma once

#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace std;

class CommonTitleBar : public Node
{
public:
	CommonTitleBar();
	~CommonTitleBar();
	CREATE_FUNC(CommonTitleBar);
	virtual bool init();

	Node* getEventNode();
	void updateBar();
private:
	void initContent();

	Label* titleLabel;
	ProgressTimer* titleBar;
	Label* titleLevel;
};