#pragma once

#include "cocos2d.h"
#include "tools/GameCommon.h"
#include "cocos-ext.h"
#include "CommonTitleBar.h"
#include "CommonMoneyBar.h"
#include "SingleSceneFrame.h"

USING_NS_CC;
USING_NS_CC_EXT;

class ChapterScene : public Layer,public ScrollViewDelegate
{
public:
	ChapterScene();
	~ChapterScene();
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(ChapterScene);
private:
	ControlButton* startBtn;
	CommonTitleBar* titleBar;
	CommonMoneyBar* moneyBar;

	vector<int> sceneIdVector;
	int currentSelectedSceneIndex;

	Layer* layer;
	ScrollView* scrollView;
	//scrollview默认是在拖动的时候调用
    virtual void scrollViewDidScroll(ScrollView* view);
	
	int frameWidth;
	int frameSpace;

	Vector<SingleSceneFrame*> frameVector;
private:
	void initContent();
	void initScrollView();

	void adjustScrollView();

	void onBack(Ref* senderz,Control::EventType controlEvent);
	void openSet(Ref* senderz,Control::EventType controlEvent);

	void startGame(Ref* senderz,Control::EventType controlEvent);
};