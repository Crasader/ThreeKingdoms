#pragma once

#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace std;

class CommonBg : public Node
{
public:
	CommonBg(string title);
	~CommonBg();
	static CommonBg* create(string title);
	virtual bool init();
private:
	void initContent();

	string title;
};