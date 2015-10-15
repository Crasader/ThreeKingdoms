#include "CommonTitleBar.h"
#include "tools/GameUtils.h"
#include "UserData.h"
#include "TitleRule.h"
#include "BaseDataManager.h"

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

	//进度条底
	auto frame_1 = Sprite::createWithSpriteFrameName("common_frame_1.png");
	frame_1->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
	addChild(frame_1);

	//设置金钱条
	titleBar = ProgressTimer::create(Sprite::createWithSpriteFrameName("common_frameBar_1.png"));
	frame_1->addChild(titleBar);
	titleBar->setPosition(Vec2(frame_1->getContentSize().width/2,frame_1->getContentSize().height/2));
	titleBar->setType(ProgressTimer::Type::BAR);
	titleBar->setBarChangeRate(Vec2(1,0));
	titleBar->setMidpoint(Vec2::ZERO);
	//titleBar->setPercentage(50.0f);
	//titleBar->setPercentage(static_cast<float>(INSTANCE(UserData)->getCurrentMoney()) / 9999 * 100);

	//图标底
	auto ink1 = Sprite::createWithSpriteFrameName("common_ink.png");
	frame_1->addChild(ink1);
	ink1->setPosition(Vec2(10,frame_1->getContentSize().height/2));

	//当前经验，军衔
	int currentTitleLevel = INSTANCE(UserData)->getTitleLevel();
	//string titleName = INSTANCE(TitleRule)->getTitleNameByTitleLevel(currentTitleLevel);
	string titleName = INSTANCE(BaseDataManager)->getLan(INSTANCE(TitleRule)->getTitleNameByTitleLevel(currentTitleLevel));
	int nextTitleIntegral = INSTANCE(TitleRule)->getTitleIntegralByTitleLevel(currentTitleLevel + 1);
	int currentUpgradeIntegral = INSTANCE(UserData)->getCurrentUpgradeIntegral();
	titleBar->setPercentage(static_cast<float>(currentUpgradeIntegral) / nextTitleIntegral * 100);

//ToDo label 要好好用用!!!??
	titleLabel = Label::createWithBMFont("font/font_title.fnt", titleName);
	frame_1->addChild(titleLabel);
	titleLabel->setPosition(INSTANCE(GameUtils)->getNodeCenterPosition(frame_1)+Vec2(20,-8));

	auto titleIcon = Sprite::createWithSpriteFrameName("common_titleIcon.png");
	frame_1->addChild(titleIcon);
	titleIcon->setPosition(Vec2(10,frame_1->getContentSize().height/2));

	//titleLevel = Label::createWithBMFont("fonts/futura-48.fnt", "Lv 1");
	titleLevel = Label::create();
	titleLevel->setSystemFontSize(20.0f);
	titleLevel->setColor(Color3B::YELLOW);
	string tmpName("Lv.");
	tmpName.append(Value(INSTANCE(UserData)->getTitleLevel()).asString());
	titleLevel->setString(tmpName);
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
	int currentTitleLevel = INSTANCE(UserData)->getTitleLevel();
	string titleName = INSTANCE(BaseDataManager)->getLan(INSTANCE(TitleRule)->getTitleNameByTitleLevel(currentTitleLevel));
	int nextTitleIntegral = INSTANCE(TitleRule)->getTitleIntegralByTitleLevel(currentTitleLevel + 1);
	int currentTitleIntegral = INSTANCE(UserData)->getCurrentIntegral();

	titleBar->setPercentage(static_cast<float>(currentTitleIntegral)/nextTitleIntegral * 100);
	titleLabel->setString(titleName);
	titleLevel->setString(string("Lv.").append(Value(INSTANCE(UserData)->getTitleLevel()).asString()));
}
