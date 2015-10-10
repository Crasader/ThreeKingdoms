#include "JoyStickLayer.h"
#include "TipsManager.h"

bool JoyStickLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("joyStick/joyStickImg.plist");
	lastPoi = Vec2::ZERO;
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

	skillPro = ProgressTimer::create(Sprite::createWithSpriteFrameName("joyStickskillButton.png"));
	skillBtn->addChild(skillPro);
	skillPro->setPosition(Vec2(skillBtn->getContentSize().width/2,skillBtn->getContentSize().height/2));
	skillPro->setType(ProgressTimer::Type::BAR);
	skillPro->setBarChangeRate(Vec2::ANCHOR_TOP_LEFT);
	skillPro->setMidpoint(Vec2::ZERO);
	skillPro->setPercentage(50.0f);

	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [=](Touch* touch,Event* event) {
		auto target = static_cast<ProgressTimer*>(event->getCurrentTarget());

		Vec2 locationInNode = target->convertToNodeSpace(touch->getLocation());
		Size s = target->getContentSize();
		Rect rect = Rect(0, 0, s.width, s.height);
		if (rect.containsPoint(locationInNode))
		{
			skillTips();
			return true;
		}
		return false;
	};
	listener->onTouchMoved = [](Touch* touch,Event* event) {

	};
	listener->onTouchEnded = [](Touch* touch,Event* event) {

	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener,skillPro);

	scheduleUpdate();
}

void JoyStickLayer::skillTips()
{
	//技能按钮，怒气没满时，点击显示提示信息
	log("showSkillTips");
	if (!skillBtn->isEnabled())
	{
		INSTANCE(TipsManager)->showTips("showSki冯铸llTips击击杀技能能兵击杀技能兵击杀技能兵击兵击杀技能兵击杀技能兵击杀技能兵击杀技能兵杀技能兵n",
			skillBtn->getParent()->convertToWorldSpace(skillBtn->getPosition()));
	}
}

void JoyStickLayer::update(float dt)
{
	//虚拟摇杆根据位置发送消息
	Vec2 poi = joystick->getVelocity() * 50;
	if (poi.x == 0 && poi.y == 0)
	{
		if (lastPoi.x != 0 || lastPoi.y != 0)
		{
			lastPoi = poi;
			_eventDispatcher->dispatchCustomEvent(JoyStick_status,JoyStick_none);
		}
		return;
	}
	lastPoi = poi;

	float degree = atan2(poi.y, poi.x)*180/atan2(0.0f,-1.0f);

	if (degree < 0)
	{
		degree += 360;
	}

	if (degree >= 22.5f && degree < 67.5f)
	{
		_eventDispatcher->dispatchCustomEvent(JoyStick_status,JoyStick_right_up);
	}
	else if (degree >= 67.5f && degree < 112.5f)
	{
		_eventDispatcher->dispatchCustomEvent(JoyStick_status,JoyStick_up);
	}
	else if (degree >= 112.5f && degree < 157.5f)
	{
		_eventDispatcher->dispatchCustomEvent(JoyStick_status,JoyStick_left_up);
	}
	else if (degree >= 157.5f && degree < 202.5f)
	{
		_eventDispatcher->dispatchCustomEvent(JoyStick_status,JoyStick_left);
	}
	else if (degree >= 202.5f && degree < 247.5f)
	{
		_eventDispatcher->dispatchCustomEvent(JoyStick_status,JoyStick_left_down);
	}
	else if (degree >= 247.5f && degree < 292.5f)
	{
		_eventDispatcher->dispatchCustomEvent(JoyStick_status,JoyStick_down);
	}
	else if (degree >= 292.5f && degree < 337.5f)
	{
		_eventDispatcher->dispatchCustomEvent(JoyStick_status,JoyStick_right_down);
	}
	else
	{
		_eventDispatcher->dispatchCustomEvent(JoyStick_status,JoyStick_right);
	}
	
}



