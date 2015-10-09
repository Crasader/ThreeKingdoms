#pragma once

#include "cocos2d.h"
#include "tools/GameCommon.h"
#include "cocos-ext.h"
#include "CommonTitleBar.h"
#include "CommonMoneyBar.h"
#include "SingleSceneFrame.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace std;

class LoadingScene : public Layer
{
public:
	LoadingScene();
	~LoadingScene();
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(LoadingScene);

	virtual void onEnter();
	virtual void onExit();
private:
	Sprite* frame;
	ProgressTimer* loadingBar;
	Sprite* fire;
	Label* currentLoad;

	size_t currentLoadNum;
	vector<string> resourceVector;
private:
	void initContent();
	void startLoad();
	void loadHandler();

};