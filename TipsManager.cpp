#include "TipsManager.h"
#include "tools/GameUtils.h"
#include "AnimateManager.h"

/************************************************************************/
/*                       公共提示信息                                  */ 
/************************************************************************/

CommonTips::CommonTips(const string& tipsContent)
{
	this->tipsContent = tipsContent;
}

CommonTips::~CommonTips()
{

}

CommonTips* CommonTips::create(const string& tipsContent)
{
	CommonTips* tips = new CommonTips(tipsContent);
	if (tips && tips->init())
	{
		tips->autorelease();
		return tips;
	}
	else
	{
		delete tips;
		tips = nullptr;
		return nullptr;
	}
}

bool CommonTips::init()
{
	if (!Node::init())
	{
		return false;
	}
	label = Label::create();
	label->setString(tipsContent);
	label->setSystemFontSize(24);
	label->setColor(Color3B::BLACK);
	label->setDimensions(300.0f,0.0f);
	label->setHorizontalAlignment(TextHAlignment::CENTER);
	label->setVerticalAlignment(TextVAlignment::CENTER);

	bg = Scale9Sprite::create("common/common_scale_2.png");
	bg->setPreferredSize(Size(20 + label->getContentSize().width, 20 + label->getContentSize().height));

	setContentSize(bg->getPreferredSize());
	setAnchorPoint(Vec2::ANCHOR_MIDDLE);

	addChild(bg);
	addChild(label);

	label->setPosition(getCenterPosition(this));
	bg->setPosition(getCenterPosition(this));

	return true;
}

void CommonTips::setString(const string& tipsContent)
{
	this->tipsContent = tipsContent;
	label->setString(tipsContent);
	bg->setPreferredSize(Size(20 + label->getContentSize().width, 20 + label->getContentSize().height));
	setContentSize(bg->getPreferredSize());
	setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	label->setPosition(getCenterPosition(this));
	bg->setPosition(getCenterPosition(this));
}

/************************************************************************/
/*                 提示信息管理器                                          */
/************************************************************************/

bool TipsManager::init()
{
	isShowing = false;
	tips = nullptr;
	return true;
}

CommonTips* TipsManager::createTips(const string& tipsContent)
{
	return CommonTips::create(tipsContent);
}

void TipsManager::hideHandler(float dt)
{
	Director::getInstance()->getScheduler()->unscheduleAllForTarget(this);
	isShowing = false;
	INSTANCE(AnimateManager)->hideAnimate(tips);
	tips = nullptr;
}

Vec2 TipsManager::getTipsPosition(Vec2 p)
{
	auto winSize = Director::getInstance()->getWinSize();
	auto size = tips->getContentSize();
	int _x;
	int _y;
	_y = p.y + size.height/2 + 50;
	if (_y + size.height/2 > winSize.height)
	{
		_y = p.y - size.height/2 -50;
	}
	_x = p.x;
	if (_x - size.width/2 < 0)
	{
		_x = size.width/2;
	}
	if (_x + size.width/2 > winSize.width)
	{
		_x = winSize.width - size.width/2;
	}
	return Vec2(_x,_y);
}

void TipsManager::showTips(const string& tipsContent, Vec2 p)
{
	if (!isShowing)
	{
		isShowing = true;
		tips = createTips(tipsContent);
		//添加到场景中
		Director::getInstance()->getRunningScene()->addChild(tips);
		tips->setPosition(getTipsPosition(p));
		INSTANCE(AnimateManager)->showAnimate(tips);
		//Note!!!
		tips->getScheduler()->schedule(CC_SCHEDULE_SELECTOR(TipsManager::hideHandler),this,2.0f,false);
	}
}







