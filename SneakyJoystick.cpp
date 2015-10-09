#include "SneakyJoystick.h"

#define SJ_PI 3.1415926f
#define SJ_PI_x_2 6.2831853f
#define SJ_RAD2DEG 180.0f/SJ_PI
#define SJ_DEG2RAD SJ_PI/180.0f

bool SneakJoystick::initWithRect(Rect rect)
{
	stickPosition = Vec2::ZERO;
	degrees = 0.0f;
	velocity = Vec2::ZERO;
	autoCenter = true;
	isDPad = false;
	hasDeadzone = false;
	numberOfDirections = 4;
	active = false;

	this->setJoystickRadius(rect.size.width/2);
	this->setThumbRadius(32.0f);
	this->setDeadRadius(0.0f);

	setPosition(rect.origin);
	return true;
}

SneakJoystick::~SneakJoystick()
{

}
void SneakJoystick::onEnterTransitionDidFinish()
{
	mEventListenerTouch = EventListenerTouchOneByOne::create();
	mEventListenerTouch->onTouchBegan = CC_CALLBACK_2(SneakJoystick::onTouchBegan,this);
	mEventListenerTouch->onTouchMoved = CC_CALLBACK_2(SneakJoystick::onTouchMoved,this);
	mEventListenerTouch->onTouchCancelled = CC_CALLBACK_2(SneakJoystick::onTouchCancelled,this);
	mEventListenerTouch->onTouchEnded = CC_CALLBACK_2(SneakJoystick::onTouchEnded,this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(mEventListenerTouch,this);
}
void SneakJoystick::onExit()
{
	Director::getInstance()->getEventDispatcher()->removeEventListener(mEventListenerTouch);
}

float round(float r)
{
	//floor向下取整,ceil向上取整
	return (r > 0.0f) ? floor(r + 0.5f) : ceil(r - 0.5f);
}


void SneakJoystick::setIsDPad(bool b)
{
	isDPad = b;
	if (isDPad)
	{
		hasDeadzone = true;
		this->setDeadRadius(10.0f);
	}
}
void SneakJoystick::setJoystickRadius(float r)
{
	joystickRadius = r;
	joystickRadiusSq = r * r;
}
void SneakJoystick::setThumbRadius(float r)
{
	thumbRadius = r;
	thumbRadiusSq = r * r;
}
void SneakJoystick::setDeadRadius(float r)
{
	deadRadius = r;
	deadRadiusSq = r * r;
}


bool SneakJoystick::onTouchBegan(Touch* touch,Event* event)
{
	auto location = Director::getInstance()->convertToGL(touch->getLocationInView());
	location = this->convertToNodeSpace(location);

	//触摸点不在区域内
	if (location.x < -joystickRadius || location.x > joystickRadius || location.y < -joystickRadius || location.y > joystickRadius)
	{
		return false;
	}
	else
	{
		float dSq = location.x * location.x + location.y * location.y;
		if (joystickRadiusSq > dSq)
		{
			//在触摸点内
			updateVelocity(location);
			return true;
		}
	}

	return false;
}
void SneakJoystick::onTouchMoved(Touch* touch,Event* event)
{
	auto location = Director::getInstance()->convertToGL(touch->getLocationInView());
	location = this->convertToNodeSpace(location);
	updateVelocity(location);
}
void SneakJoystick::onTouchEnded(Touch* touch,Event* event)
{
	auto location = Vec2::ZERO;
	if (!autoCenter)
	{
		location = Director::getInstance()->convertToGL(touch->getLocationInView());
		location = this->convertToNodeSpace(location);
	}
	updateVelocity(location);
}
void SneakJoystick::onTouchCancelled(Touch* touch,Event* event)
{
	this->onTouchEnded(touch,event);
}


void SneakJoystick::updateVelocity(Vec2 point)
{
	//计算point到圆点的距离和角度
	float dx = point.x;
	float dy = point.y;
	float dsq = dx * dx + dy * dy;

	if (dsq <= deadRadiusSq)
	{
		velocity = Vec2::ZERO;
		degrees = 0.0f;
		stickPosition = point;
		return;
	}

	float angle = atan2f(dy, dx);
	if (angle < 0)
	{
		angle += SJ_PI_x_2;
	}
	float cosAngle;
	float sinAngle;

	if (isDPad)
	{
		float anglePerSector = 360.0f /numberOfDirections * SJ_DEG2RAD;
		angle = round(angle/anglePerSector) * anglePerSector;
	}

	cosAngle = cosf(angle);
	sinAngle = sinf(angle);

	if(dsq > joystickRadiusSq || isDPad)
	{
		dx = cosAngle * joystickRadius;
		dy = sinAngle * joystickRadius;
	}

	velocity = Vec2(dx/joystickRadius, dy/joystickRadius);
	degrees = angle * SJ_RAD2DEG;

	stickPosition = Vec2(dx, dy);
}
