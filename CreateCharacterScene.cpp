#include "CreateCharacterScene.h"
#include "tools/GameUtils.h"
#include "tools/ButtonUtils.h"
#include "RoleRule.h"
#include "UserData.h"
#include "HelloWorldScene.h"
#include "ChapterScene.h"


Scene* CreateCharacterScene::createScene()
{
    auto scene = Scene::create();
    auto layer = CreateCharacterScene::create();
    scene->addChild(layer);
    return scene;
}

bool CreateCharacterScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
	initContent();
    return true;
}


void CreateCharacterScene::onChangeAccount(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void CreateCharacterScene::onEnter()
{
	Layer::onEnter();
	listener = EventListenerCustom::create(UnselectAllSingleCharacter,[=](EventCustom* event){
		unSelectAll();
	});
	_eventDispatcher->addEventListenerWithFixedPriority(listener,1);
}
void CreateCharacterScene::onEnterTransitionDidFinish()
{
	Layer::onEnterTransitionDidFinish();
}
void CreateCharacterScene::onExit()
{
	Layer::onExit();
	removeAllChildren();
	_eventDispatcher->removeEventListener(listener);


}

void CreateCharacterScene::initContent()
{
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("ui/createCharacter/createCharacter.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("model/20001/20001_stand.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("model/20002/20002_stand.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("model/20003/20003_stand.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("model/20005/20005_stand.plist");

	auto winSize = Director::getInstance()->getWinSize();

	initBg();

	auto fg = Sprite::createWithSpriteFrameName("createCharacter_fontground.png");
	addChild(fg);
	fg->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
	fg->setPosition(Vec2(INSTANCE(GameUtils)->getWindowsCenterPosition().x,70));

	//auto color = LayerColor::create(getColor());
	//addChild(color);

	auto startBtn = INSTANCE(ButtonUtils)->createButton("createCharacter_enterGameBtn1.png",
		"createCharacter_enterGameBtn2.png",
		"createCharacter_enterGameBtn2.png",
		Size(232,139),"");
	addChild(startBtn);
	startBtn->setPosition(Vec2(INSTANCE(GameUtils)->getWindowsCenterPosition().x,70));

	startBtn->addTargetWithActionForControlEvents(this, cccontrol_selector(CreateCharacterScene::startGame),Control::EventType::TOUCH_UP_INSIDE);

	vector<int> roleIds = INSTANCE(RoleRule)->getAllRoleId();
	//for (const auto& ids : roleIds)
	for(int i=0;i<roleIds.size();i++)
	{
		//CCLOG("%d",ids);
		auto sc = SingleCharacter::create(roleIds[i]);
		addChild(sc);
		sc->setPosition(Vec2(winSize.width/5 * (i+1),150));
		characterArray.pushBack(sc);
	}

}
void CreateCharacterScene::startGame(Ref* senderz,Control::EventType controlEvent)
{
	log("startGame");

	int roleId = INSTANCE(UserData)->getCurrentRoleId();
	Director::getInstance()->replaceScene(ChapterScene::createScene());
}
void CreateCharacterScene::unSelectAll()
{
	for (auto& ref : characterArray)
	{
		ref->setSelect(false);
	}
}

Color4B CreateCharacterScene::getColor()
{
	return Color4B::BLUE;
}

//´´½¨¹ö¶¯±³¾°
void CreateCharacterScene::initBg()
{
	auto winSize = Director::getInstance()->getWinSize();
	bg1 = Sprite::create("ui/createCharacter/createCharacter_bg.png");
	bg2 = Sprite::create("ui/createCharacter/createCharacter_bg.png");
	addChild(bg1);
	bg1->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
	bg1->setPosition(Vec2(0,winSize.height));
	addChild(bg2);
	bg2->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
	bg2->setFlippedX(true);
	bg2->setPosition(Vec2(-bg1->getContentSize().width,winSize.height));

	scheduleUpdate();
	//schedule(CC_SCHEDULE_SELECTOR(CreateCharacterScene::update),1.0f);
}

void CreateCharacterScene::update(float dt)
{
	bg1->setPosition(bg1->getPosition() + Vec2(1,0));
	bg2->setPosition(bg2->getPosition() + Vec2(1,0));
	//log("bg1==%f,%f",bg1->getPositionX(),bg1->getPositionY());
	//log("bg2==%f,%f",bg2->getPositionX(),bg2->getPositionY());
	if (bg1->getPositionX() > 0 && bg2->getPositionX() > 0)
	{
		if (bg1->getPositionX() > bg2->getPositionX())
		{
			bg1->setPositionX(bg2->getPositionX() - bg2->getContentSize().width);
		}
		else
		{
			bg2->setPositionX(bg1->getPositionX() - bg1->getContentSize().width);
		}
	}
}
