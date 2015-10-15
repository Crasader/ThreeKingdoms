#include "OnlineReward.h"
#include "SystemConfigRule.h"
#include "UserData.h"
#include "FightManager.h"

bool OnlineReward::init()
{
	if (!Node::init())
	{
		return false;
	}
	initContent();
	return true;
}
OnlineReward::OnlineReward()
{

}

OnlineReward::~OnlineReward()
{

}

void OnlineReward::initContent()
{
	time = INSTANCE(SystemConfigRule)->getOnlineRewardTime();
	times = INSTANCE(SystemConfigRule)->getOnlineRewardTimes();
	money = INSTANCE(SystemConfigRule)->getOnlineReward();

	auto frame = Sprite::createWithSpriteFrameName("fightUI_onlineReward_frame.png");
	addChild(frame);
	auto listener1 = EventListenerTouchOneByOne::create();
	listener1->onTouchBegan = [=](Touch* touch,Event* event) {
		log("ontouchBegan");
		auto target = static_cast<Sprite*>(event->getCurrentTarget());

		Vec2 locationInNode = target->convertToNodeSpace(touch->getLocation());
		Size s = target->getContentSize();
		Rect rect = Rect(0, 0, s.width, s.height);
		if (rect.containsPoint(locationInNode))
		{
			receiveHandler();
			return true;
		}
		return false;
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1,frame);

	bar = ProgressTimer::create(Sprite::createWithSpriteFrameName("fightUI_onlineReward_bar.png"));
	frame->addChild(bar);
	bar->setPosition(frame->getContentSize().width/2,10);
	bar->setType(ProgressTimer::Type::BAR);
	bar->setBarChangeRate(Vec2(1,0));
	bar->setMidpoint(Vec2::ZERO);
	bar->setPercentage(static_cast<float>(INSTANCE(UserData)->getReceiveOnlineRewardTimes())/times * 100);

	for (int i=1;i<times;i++)
	{
		auto line = Sprite::createWithSpriteFrameName("fightUI_onlineReward_line.png");
		frame->addChild(line);
		line->setPosition(Vec2(8+i*(90/times),10));
	}

	label = Label::create();
	label->setPosition(Vec2(frame->getContentSize().width/2,32));
	label->setSystemFontSize(20);
	label->setColor(Color3B::RED);
	frame->addChild(label);
	updateTime(0.1f);
	Director::getInstance()->getScheduler()->schedule(CC_SCHEDULE_SELECTOR(OnlineReward::updateTime),this,1.0f,false);
}

void OnlineReward::updateTime(float dt)
{
	//更新奖励
	if (INSTANCE(UserData)->getReceiveOnlineRewardTimes() == times)
	{
		label->setColor(Color3B::RED);
		label->setString("FALSE");
		receivable = false;
	}
	else
	{
		label->setColor(Color3B::GREEN);
		label->setString("True");
		receivable = true;
	}
}

void OnlineReward::receiveHandler()
{
	log("onlineReward::;receiveHandler");
	if (receivable)
	{
		CCLOG("%s",string("领取").c_str());
	}
	else
	{
		CCLOG("%s",string("不能领取").c_str());
	}
	//测试屏震效果
	_eventDispatcher->dispatchCustomEvent(NoticeSkillShake);
}
