#include "ButtonUtils.h"

bool ButtonUtils::init()
{
	return true;
}


void ButtonUtils::setButtonTitle(ControlButton* button,const std::string& titleName)
{
	//根据按钮状态设置文本
	button->setTitleForState(titleName,Control::State::NORMAL);
	button->setTitleForState(titleName,Control::State::HIGH_LIGHTED);
	button->setTitleForState(titleName,Control::State::DISABLED);
	button->setTitleForState(titleName,Control::State::SELECTED);
}

ControlButton* ButtonUtils::createButton(const std::string& frameName,
							Size size,
							const std::string& label,
							float labelSize,
							Color3B labelColor)
{
	//auto normal = Scale9Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName));
	//auto highLight = Scale9Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName));
	//auto disable = Scale9Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName));

	//auto btn = ControlButton::create(label,"Arial",labelSize);
	////根据状态设置背景
	//btn->setBackgroundSpriteForState(normal,Control::State::NORMAL);
	//btn->setBackgroundSpriteForState(highLight,Control::State::HIGH_LIGHTED);
	//btn->setBackgroundSpriteForState(disable,Control::State::DISABLED);

	////根据状态设置按钮文字颜色
	//btn->setTitleColorForState(labelColor,Control::State::NORMAL);
	//btn->setTitleColorForState(labelColor,Control::State::HIGH_LIGHTED);
	//btn->setTitleColorForState(labelColor,Control::State::DISABLED);

	////--TODO设置触摸级别
	//return btn;

	return createButton(frameName,frameName,frameName,size,label,labelSize,labelColor);
}

ControlButton* ButtonUtils::createButton(const std::string& normalFrame,
							const std::string& highLightFrame,
							const std::string& disableFrame,
							Size size,
							const std::string& label,
							float labelSize ,
							Color3B labelColor)
{
	auto normal = Scale9Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(normalFrame));
	auto highLight = Scale9Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(highLightFrame));
	auto disable = Scale9Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(disableFrame));

	auto btn = ControlButton::create(label,"Arial",labelSize);

	//设置显示尺寸
	btn->setPreferredSize(size);
	//根据状态设置背景
	btn->setBackgroundSpriteForState(normal,Control::State::NORMAL);
	btn->setBackgroundSpriteForState(highLight,Control::State::HIGH_LIGHTED);
	btn->setBackgroundSpriteForState(disable,Control::State::DISABLED);

	//根据状态设置按钮文字颜色
	btn->setTitleColorForState(labelColor,Control::State::NORMAL);
	btn->setTitleColorForState(labelColor,Control::State::HIGH_LIGHTED);
	btn->setTitleColorForState(labelColor,Control::State::DISABLED);

	//--TODO设置触摸级别

	return btn;
}
