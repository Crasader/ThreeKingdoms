#include "ButtonUtils.h"

bool ButtonUtils::init()
{
	return true;
}


void ButtonUtils::setButtonTitle(ControlButton* button,const std::string& titleName)
{
	//���ݰ�ť״̬�����ı�
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
	////����״̬���ñ���
	//btn->setBackgroundSpriteForState(normal,Control::State::NORMAL);
	//btn->setBackgroundSpriteForState(highLight,Control::State::HIGH_LIGHTED);
	//btn->setBackgroundSpriteForState(disable,Control::State::DISABLED);

	////����״̬���ð�ť������ɫ
	//btn->setTitleColorForState(labelColor,Control::State::NORMAL);
	//btn->setTitleColorForState(labelColor,Control::State::HIGH_LIGHTED);
	//btn->setTitleColorForState(labelColor,Control::State::DISABLED);

	////--TODO���ô�������
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

	//������ʾ�ߴ�
	btn->setPreferredSize(size);
	//����״̬���ñ���
	btn->setBackgroundSpriteForState(normal,Control::State::NORMAL);
	btn->setBackgroundSpriteForState(highLight,Control::State::HIGH_LIGHTED);
	btn->setBackgroundSpriteForState(disable,Control::State::DISABLED);

	//����״̬���ð�ť������ɫ
	btn->setTitleColorForState(labelColor,Control::State::NORMAL);
	btn->setTitleColorForState(labelColor,Control::State::HIGH_LIGHTED);
	btn->setTitleColorForState(labelColor,Control::State::DISABLED);

	//--TODO���ô�������

	return btn;
}
