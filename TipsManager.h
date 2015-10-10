#pragma once

#include "cocos2d.h"
#include "cocos-ext.h"
#include "tools/GameCommon.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace std;

//公共提示信息
class CommonTips : public Node
{
public:
	CommonTips(const string& tipsContent);
	~CommonTips();
	static CommonTips* create(const string& tipsContent);
	virtual bool init();

	void setString(const string& tipsContent);
private:
	string tipsContent;
	Label* label;
	Scale9Sprite* bg;
};


//提示信息管理器
class TipsManager:public Ref
{
public:
	CLASS_INSTANCE(TipsManager);
	bool init();

	void showTips(const string& tipsContent, Vec2 p);
private:
	bool isShowing;
	CommonTips* createTips(const string& tipsContent);
	CommonTips* tips;

	void hideHandler(float dt);

	Vec2 getTipsPosition(Vec2 p);

};
