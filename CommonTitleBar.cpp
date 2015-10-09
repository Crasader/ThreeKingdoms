#include "CommonTitleBar.h"
#include "tools/GameUtils.h"

CommonTitleBar::CommonTitleBar()
{
}
CommonTitleBar::~CommonTitleBar()
{

}

bool CommonTitleBar::init()
{
	if (!Node::init())
	{
		return false;
	}
	initContent();
	return true;
}

void CommonTitleBar::initContent()
{
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("common/common.plist");

	auto frame_1 = Sprite::createWithSpriteFrameName("common_frame_1.png");
	frame_1->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
	addChild(frame_1);

	titleBar = ProgressTimer::create(Sprite::createWithSpriteFrameName("common_frameBar_1.png"));
	frame_1->addChild(titleBar);
	titleBar->setPosition(Vec2(frame_1->getContentSize().width/2,frame_1->getContentSize().height/2));
	titleBar->setType(ProgressTimer::Type::BAR);
	titleBar->setBarChangeRate(Vec2(1,0));
	titleBar->setMidpoint(Vec2::ZERO);
	//titleBar->setPercentage(500/9999*100);
	titleBar->setPercentage(50.0f);

	auto ink1 = Sprite::createWithSpriteFrameName("common_ink.png");
	frame_1->addChild(ink1);
	ink1->setPosition(Vec2(10,frame_1->getContentSize().height/2));

//ToDo label 要好好用用!!!??
	titleLabel = Label::createWithBMFont("fonts/futura-48.fnt", "Lv");
	frame_1->addChild(titleLabel);
	titleLabel->setPosition(INSTANCE(GameUtils)->getNodeCenterPosition(frame_1)+Vec2(0,-8));

	auto titleIcon = Sprite::createWithSpriteFrameName("common_titleIcon.png");
	frame_1->addChild(titleIcon);
	titleIcon->setPosition(Vec2(10,frame_1->getContentSize().height/2));

	titleLevel = Label::createWithBMFont("fonts/futura-48.fnt", "Lv 1");
	titleLevel->setColor(Color3B::YELLOW);
	titleIcon->addChild(titleLevel);
	titleLevel->setPosition(Vec2(20,titleIcon->getContentSize().height/2-20));
}

Node* CommonTitleBar::getEventNode()
{
	return titleBar;
}
//设置人物等级，进度条
void CommonTitleBar::updateBar()
{
	titleBar->setPercentage(80.0f);
	titleLabel->setString("titleLabel");
	titleLevel->setString("Lv.100");
}
