#include "SetBar.h"
#include "tools/ButtonUtils.h"
#include "ChapterScene.h"

bool SetBar::init()
{
	if (!Node::init())
	{
		return false;
	}
	initContent();
	return true;
}
SetBar::SetBar()
{
	isShow = false;
	barBg = nullptr;
	showBtn = nullptr;
	setBtn = nullptr;
}

SetBar::~SetBar()
{
	barBg->release();
}

void SetBar::initContent()
{
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("common/common.plist");

	barBg = Sprite::createWithSpriteFrameName("fightUI_set_barBg.png");
	barBg->setAnchorPoint(Vec2::ANCHOR_MIDDLE_TOP);
	barBg->setPosition(Vec2(0,-10));
	barBg->retain();

	setBtn = INSTANCE(ButtonUtils)->createButton("common_setBtn.png",Size(75,81),"");
	barBg->addChild(setBtn);
	setBtn->setPosition(Vec2(30,295));
	setBtn->addTargetWithActionForControlEvents(this,cccontrol_selector(SetBar::openSet),Control::EventType::TOUCH_DOWN);

	auto btn = INSTANCE(ButtonUtils)->createButton("common_rechargeBtn.png",Size(75,81),"");
	barBg->addChild(btn);
	btn->setPosition(Vec2(30,215));
	btn->addTargetWithActionForControlEvents(this,cccontrol_selector(SetBar::openRecharge),Control::EventType::TOUCH_DOWN);

	btn = INSTANCE(ButtonUtils)->createButton("common_chapterBtn.png",Size(75,81),"");
	barBg->addChild(btn);
	btn->setPosition(Vec2(30,135));
	btn->addTargetWithActionForControlEvents(this,cccontrol_selector(SetBar::back),Control::EventType::TOUCH_DOWN);

	showBtn = INSTANCE(ButtonUtils)->createButton("fightUI_set_showBtn.png","fightUI_set_hideBtn.png","fightUI_set_hideBtn.png",Size(75,81),"");
	addChild(showBtn);
	showBtn->setZoomOnTouchDown(false);
	showBtn->addTargetWithActionForControlEvents(this,cccontrol_selector(SetBar::showBtnHandler),Control::EventType::TOUCH_UP_INSIDE);
}

void SetBar::showBtnHandler(Ref* senderz,Control::EventType controlEvent)
{
	if (isShow)
	{
		hideBar();
		showBtn->setHighlighted(false);
	}
	else
	{
		showBar();
		showBtn->setHighlighted(true);
	}
	isShow = !isShow;
}

void SetBar::showBar()
{
	if (!barBg->getParent())
	{
		addChild(barBg,-1);
	}
}
void SetBar::hideBar()
{
	barBg->removeFromParent();
}

void SetBar::openSet(Ref* senderz,Control::EventType controlEvent)
{
	showBtnHandler(senderz,controlEvent);
	//打开设置
}

void SetBar::openRecharge(Ref* senderz,Control::EventType controlEvent)
{
	showBtnHandler(senderz,controlEvent);
	//打开充值
}

void SetBar::back(Ref* senderz,Control::EventType controlEvent)
{
	showBtnHandler(senderz,controlEvent);
	//Director::getInstance()->replaceScene(ChapterScene::createScene());
}
