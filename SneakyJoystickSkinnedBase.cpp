#include "SneakyJoystickSkinnedBase.h"


bool SneakJoystickSkinnedBase::init()
{
	if (!Layer::init())
	{
		return false;
	}
	this->backgroundSprite = nullptr;
	this->thumbSprite = nullptr;
	this->joystick = nullptr;

	schedule(schedule_selector(SneakJoystickSkinnedBase::updatePositions));
	return true;
}
SneakJoystickSkinnedBase::~SneakJoystickSkinnedBase()
{
	if (backgroundSprite)
	{
		backgroundSprite->release();
		backgroundSprite = nullptr;
	}
	if (thumbSprite)
	{
		thumbSprite->release();
		thumbSprite = nullptr;
	}
	if (joystick)
	{
		joystick->release();
		joystick = nullptr;
	}
}



void SneakJoystickSkinnedBase::updatePositions(float delta)
{
	if (joystick && thumbSprite)
	{
		thumbSprite->setPosition(joystick->getStickPosition());
	}
}
void SneakJoystickSkinnedBase::setContentSize(Size s)
{
	Layer::setContentSize(s);
	backgroundSprite->setContentSize(s);
}
void SneakJoystickSkinnedBase::setBackgroundSprite(Sprite* bg)
{
	if (backgroundSprite)
	{
		if (backgroundSprite->getParent())
		{
			backgroundSprite->getParent()->removeChild(backgroundSprite,true);
		}
		backgroundSprite->release();
	}
	bg->retain();
	backgroundSprite = bg;
	if (bg)
	{
		this->addChild(backgroundSprite,0);
		this->setContentSize(backgroundSprite->getContentSize());
	}
}
void SneakJoystickSkinnedBase::setThumbSprite(Sprite* thumb)
{
	if (thumbSprite)
	{
		if (thumbSprite->getParent())
		{
			thumbSprite->getParent()->removeChild(thumbSprite,true);
		}
		thumbSprite->release();
	}
	thumb->retain();
	thumbSprite = thumb;
	if (thumb)
	{
		this->addChild(thumbSprite,1);
	}
}
void SneakJoystickSkinnedBase::setJoystick(SneakJoystick* joys)
{
	if (joystick)
	{
		if (joystick->getParent())
		{
			joystick->getParent()->removeChild(joystick,true);
		}
		joystick->release();
	}
	
	joys->retain();
	joystick = joys;
	if (joys)
	{
		this->addChild(joys,2);
		if (thumbSprite)
		{
			joystick->setThumbRadius(thumbSprite->getBoundingBox().size.width/2);
		}
		else
		{
			joystick->setThumbRadius(0);
		}

		if (backgroundSprite)
		{
			joystick->setJoystickRadius(backgroundSprite->getBoundingBox().size.width/2);
		}
	}
}







