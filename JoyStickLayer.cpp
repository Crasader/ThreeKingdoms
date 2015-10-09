#include "JoyStickLayer.h"

bool JoyStickLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("joyStick/joyStickImg.plist");
	initJoyStickLayer();
	return true;
}


void JoyStickLayer::initJoyStickLayer()
{
	joystick = new SneakJoystick();
	joystick->autorelease();
	joystick->initWithRect(Rect::ZERO);
	joystick->setAutoCenter(true);
	joystick->setHasDeadzone(true);
	joystick->setDeadRadius(10.0f);
	joystick->setJoystickRadius(200.0f);

	joystickSkin = SneakJoystickSkinnedBase::create();
	joystickSkin->setBackgroundSprite(Sprite::createWithSpriteFrameName("joyStick.png"));
	joystickSkin->setThumbSprite(Sprite::createWithSpriteFrameName("joyStickCenter.png"));
	joystickSkin->setScale(1.0f);

	joystickSkin->setJoystick(joystick);
	this->addChild(joystickSkin,100);



	attackBtn = INSTANCE(ButtonUtils)->createButton("joyStickButton.png","joyStickButtonHighLight.png","joyStickButton.png",Size(221,177),"");
	this->addChild(attackBtn);
	attackBtn->setZoomOnTouchDown(false);
	skillBtn = INSTANCE(ButtonUtils)->createButton("joyStickskillButton.png","joyStickskillButtonHighLight.png","joyStickskillButtonGray.png",Size(106,111),"");
	this->addChild(skillBtn);
	skillBtn->setZoomOnTouchDown(false);

	joystickSkin->setPosition(Vec2(-350,-200));
	attackBtn->setPosition(Vec2(380,-230));
	skillBtn->setPosition(Vec2(240,-200));

	skillBtn->setEnabled(false);

}

