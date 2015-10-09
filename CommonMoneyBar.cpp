#include "CommonMoneyBar.h"
#include "tools/GameUtils.h"

CommonMoneyBar::CommonMoneyBar()
{

}
CommonMoneyBar::~CommonMoneyBar()
{

}



bool CommonMoneyBar::init()
{
	if (!Node::init())
	{
		return false;
	}
	initContent();
	return true;
}

void CommonMoneyBar::initContent()
{
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("common/common.plist");
	auto frame_2 = Sprite::createWithSpriteFrameName("common_frame_1.png");
	addChild(frame_2);

	moneyBar = ProgressTimer::create(Sprite::createWithSpriteFrameName("common_frameBar_1.png"));
	frame_2->addChild(moneyBar);
	moneyBar->setPosition(Vec2(frame_2->getContentSize().width/2,frame_2->getContentSize().height/2));
	moneyBar->setType(ProgressTimer::Type::BAR);
	moneyBar->setBarChangeRate(Vec2(1,0));
	moneyBar->setMidpoint(Vec2::ZERO);
	moneyBar->setPercentage(30.0f);

	auto ink2 = Sprite::createWithSpriteFrameName("common_ink.png");
	frame_2->addChild(ink2);
	ink2->setPosition(Vec2(10,frame_2->getContentSize().height/2));

//ToDo label 要好好用用!!!??
	moneyLabel = Label::createWithBMFont("fonts/futura-48.fnt", "677");
	frame_2->addChild(moneyLabel);
	moneyLabel->setPosition(INSTANCE(GameUtils)->getNodeCenterPosition(frame_2)+Vec2(0,-8));

	auto moneyIcon = Sprite::createWithSpriteFrameName("common_money_3.png");
	moneyIcon->setScale(0.6f);
	frame_2->addChild(moneyIcon);
	moneyIcon->setPosition(Vec2(10,frame_2->getContentSize().height/2));

}
void CommonMoneyBar::updateBar()
{
	moneyBar->setPercentage(90.0f);
	moneyLabel->setString("999");
}

