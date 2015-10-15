#include "FightUI.h"
#include "UserData.h"
#include "JoyStickLayer.h"
#include "SystemConfigRule.h"
#include "FightManager.h"
#include "TipsManager.h"
#include "tools/GameUtils.h"
#include "TitleRule.h"

FightUI::FightUI()
{
	currentMoney = INSTANCE(UserData)->getCurrentMoney();
	currentIntegral = INSTANCE(UserData)->getCurrentIntegral();
	//currentUpgradeIntegral = INSTANCE(UserData)->getCurrentUpgradeIntegral();
	maxRate = INSTANCE(SystemConfigRule)->getMaxMagnification();

	differenceMoney = 0;
}

FightUI::~FightUI()
{

}

bool FightUI::init()
{
	if (!Layer::init())
	{
		return false;
	}
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("ui/fightUI/fightUI.plist");

	initContent();
	return true;
}

void FightUI::initContent()
{
	auto winSize = Director::getInstance()->getWinSize();

	auto bottomBar = Sprite::createWithSpriteFrameName("fightUI_bottomBar.png");
	addChild(bottomBar);
	bottomBar->setPosition(Vec2(0,(bottomBar->getContentSize().height-winSize.height)/2));

	titleBar = CommonTitleBar::create();
	titleBar->setPosition(Vec2(60-winSize.width/2,winSize.height/2 - 60));
	addChild(titleBar);
	//设置titleBar的点击事件
	auto listener1 = EventListenerTouchOneByOne::create();
	listener1->onTouchBegan = [=](Touch* touch,Event* event) {
		log("ontouchBegan");
		auto target = static_cast<CommonTitleBar*>(event->getCurrentTarget());

		Vec2 locationInNode = target->convertToNodeSpace(touch->getLocation());
		Size s = target->getContentSize();
		Rect rect = Rect(0, 0, s.width, s.height);
		if (rect.containsPoint(locationInNode))
		{
			showExpTips();
			return true;
		}
		return false;
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1,titleBar->getEventNode());

	//聚宝盆
	potSprite = Sprite::createWithSpriteFrameName("fightUI_pot_gray.png");
	addChild(potSprite);
	potSprite->setPosition(Vec2(340 - winSize.width/2, winSize.height/2 - 60));
	//设置聚宝盆的点击事件
	auto listener2 = EventListenerTouchOneByOne::create();
	listener2->onTouchBegan = [=](Touch* touch,Event* event) {
		log("ontouchBegan");
		auto target = static_cast<Sprite*>(event->getCurrentTarget());

		Vec2 locationInNode = target->convertToNodeSpace(touch->getLocation());
		Size s = target->getContentSize();
		Rect rect = Rect(0, 0, s.width, s.height);
		if (rect.containsPoint(locationInNode))
		{
			showPotTips();
			return true;
		}
		return false;
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener2,potSprite);

	//彩池进度条
	int currentPot = INSTANCE(UserData)->getPotWinning();
	int max = INSTANCE(SystemConfigRule)->getCurrentTreasureBowlWinnings();
	potBar = ProgressTimer::create(Sprite::createWithSpriteFrameName("fightUI_pot.png"));
	potSprite->addChild(potBar);
	potBar->setPosition(getCenterPosition(potSprite));
	potBar->setType(ProgressTimer::Type::BAR);
	potBar->setBarChangeRate(Vec2(0,1));
	potBar->setMidpoint(Vec2::ZERO);
	potBar->setPercentage(static_cast<float>(currentPot)/max * 100);

	potLabel = Label::create();
	potLabel->setSystemFontSize(24);
	potLabel->setColor(Color3B::GREEN);
	potSprite->addChild(potLabel);
	//potLabel->setPosition(Vec2(potSprite->getContentSize().width/2,potSprite->getContentSize().height/2));
	potLabel->setPosition(getCenterPosition(potSprite));
	potLabel->setString(Value(currentPot).asString()+ "/" + Value(max).asString());

	updatePot();

	//金钱条
	auto barFrame2 = Sprite::createWithSpriteFrameName("fightUI_barFrame_2.png");
	addChild(barFrame2);
	barFrame2->setPosition(Vec2(20, 80 - winSize.height/2));

	moneyBar = ProgressTimer::create(Sprite::createWithSpriteFrameName("fightUI_redBar.png"));
	barFrame2->addChild(moneyBar);
	moneyBar->setPosition(getCenterPosition(barFrame2));
	moneyBar->setType(ProgressTimer::Type::BAR);
	moneyBar->setBarChangeRate(Vec2(1,0));
	moneyBar->setMidpoint(Vec2::ZERO);
	moneyBar->setPercentage(static_cast<float>(currentMoney)/9999*100);

	moneyLabel = Label::createWithBMFont("font/font_yellowNum.fnt",Value(currentMoney).asString());
	barFrame2->addChild(moneyLabel);
	moneyLabel->setPosition(getCenterPosition(barFrame2));

	auto icon2 = Sprite::createWithSpriteFrameName("fightUI_moneyIcon.png");
	barFrame2->addChild(icon2);
	icon2->setPosition(Vec2(20,barFrame2->getContentSize().height/2));
	//设置金币的点击事件
	auto listener3 = EventListenerTouchOneByOne::create();
	listener3->onTouchBegan = [=](Touch* touch,Event* event) {
		log("ontouchBegan");
		auto target = static_cast<Sprite*>(event->getCurrentTarget());

		Vec2 locationInNode = target->convertToNodeSpace(touch->getLocation());
		Size s = target->getContentSize();
		Rect rect = Rect(0, 0, s.width, s.height);
		if (rect.containsPoint(locationInNode))
		{
			//打开充值界面
			log("open recharge win");
			return true;
		}
		return false;
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener3,icon2);

	//虚拟摇杆
	JoyStickLayer* joyStickLayer = JoyStickLayer::create();
	addChild(joyStickLayer);

	setBar = SetBar::create();
	setBar->setPosition(Vec2(winSize.width/2 - 40,280));
	addChild(setBar);

	onlineReward = OnlineReward::create();
	addChild(onlineReward);
	onlineReward->setPosition(Vec2(140 - winSize.width/2,winSize.height/2 - 110));
}

//初始化完成后执行
void FightUI::onEnter()
{
	Layer::onEnter();
	//接受到更新消息后处理
	listenerForMoney = EventListenerCustom::create(NoticeUpdateMoney,[=](EventCustom* event)
	{
		updateMoney();
	});
	listenerForIntegral = EventListenerCustom::create(NoticeUpdateIntegral,[=](EventCustom* event)
	{
		updateIntegral();
	});
	listenerForPot = EventListenerCustom::create(NoticeUpdatePot,[=](EventCustom* event)
	{
		updatePot();
	});
	Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(listenerForMoney,1);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(listenerForIntegral,2);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(listenerForPot,3);

	updateIntegral();

	scheduleUpdate();
}

void FightUI::onExit()
{
	Layer::onExit();
	Director::getInstance()->getEventDispatcher()->removeEventListener(listenerForMoney);
	Director::getInstance()->getEventDispatcher()->removeEventListener(listenerForIntegral);
	Director::getInstance()->getEventDispatcher()->removeEventListener(listenerForPot);
}

void FightUI::updateMoney()
{
	differenceMoney += INSTANCE(UserData)->getCurrentMoney() - currentMoney;
	currentMoney = INSTANCE(UserData)->getCurrentMoney();
	moneyBar->setPercentage(static_cast<float>(currentMoney)/9999*100);
}
void FightUI::updateIntegral()
{
	int lastTitleLevel = INSTANCE(TitleRule)->getTitleLevelByIntegral(currentIntegral);
	currentIntegral = INSTANCE(UserData)->getCurrentIntegral();
	int currentTitleLevel = INSTANCE(UserData)->getTitleLevel();
	titleBar->updateBar();
	if (currentTitleLevel > lastTitleLevel)
	{
		//TODO
		log("show Level UP");
	}
}
void FightUI::updatePot()
{
	int currentPot = INSTANCE(UserData)->getPotWinning();
	int max = INSTANCE(SystemConfigRule)->getCurrentTreasureBowlWinnings();
	if (max - currentPot <= 100)
	{
		potLabel->setColor(Color3B::GREEN);
	}
	else
	{
		potLabel->setColor(Color3B::RED);
	}
	potBar->setPercentage(static_cast<float>(currentPot)/max*100);
	potLabel->setString(Value(currentPot).asString()+ "/" + Value(max).asString());
}

void FightUI::showPotTips()
{
	INSTANCE(TipsManager)->showTips(string("xxx"),
		potSprite->getParent()->convertToWorldSpace(potSprite->getPosition()));
}
void FightUI::showExpTips()
{
	INSTANCE(TipsManager)->showTips("升级能开启高倍场景和连招(连招越多,消耗越大,得到的奖励也越高)",
		titleBar->getParent()->convertToWorldSpace(titleBar->getPosition()));
}

void FightUI::update(float dt)
{
	showMoneyAnimation();
}

void FightUI::showMoneyAnimation()
{
	if (differenceMoney == 0)
	{
		return;
	}

	if (differenceMoney < 0)
	{
		differenceMoney++;
	}
	else
	{
		differenceMoney--;
	}
	moneyLabel->setString(Value(currentMoney - differenceMoney).asString());
}







