#include "FightUI.h"
#include "UserData.h"
#include "JoyStickLayer.h"

FightUI::FightUI()
{
	currentMoney = INSTANCE(UserData)->getCurrentMoney();
	currentIntegral = INSTANCE(UserData)->getCurrentIntegral();
	//currentUpgradeIntegral = INSTANCE(UserData)->getCurrentUpgradeIntegral();
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

	//æ€±¶≈Ë
	potSprite = Sprite::createWithSpriteFrameName("fightUI_pot_gray.png");
	addChild(potSprite);
	potSprite->setPosition(Vec2(340 - winSize.width/2, winSize.height/2 - 60));


	//–Èƒ‚“°∏À
	JoyStickLayer* joyStickLayer = JoyStickLayer::create();
	addChild(joyStickLayer);
}












