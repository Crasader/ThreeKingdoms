#pragma once
#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace std;

class SetBar : public Node
{
public:
	CREATE_FUNC(SetBar);
	virtual bool init();
	SetBar();
	~SetBar();
private:
	void initContent();
	Sprite* barBg;

	ControlButton* showBtn;
	ControlButton* setBtn;

	bool isShow;
	void showBtnHandler(Ref* senderz,Control::EventType controlEvent);
	void showBar();
	void hideBar();
	void openSet(Ref* senderz,Control::EventType controlEvent);
	void openRecharge(Ref* senderz,Control::EventType controlEvent);
	void back(Ref* senderz,Control::EventType controlEvent);


};