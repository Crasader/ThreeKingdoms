#pragma once

#include "cocos2d.h"

USING_NS_CC;
using namespace std;

class SneakJoystick : public Node
{
public:
	bool initWithRect(Rect rect);
protected:

	float joystickRadiusSq;
	float thumbRadiusSq;
	float deadRadiusSq;

	//摇杆坐标
	CC_SYNTHESIZE_READONLY(Vec2, stickPosition, StickPosition);
	//角度
	CC_SYNTHESIZE_READONLY(float, degrees, Degrees);
	//速度
	CC_SYNTHESIZE_READONLY(Vec2, velocity, Velocity);
	//是否自动回到中心点
	CC_SYNTHESIZE(bool, autoCenter, AutoCenter);
	//是否有死亡区域
	CC_SYNTHESIZE(bool, hasDeadzone, HasDeadzone);
	CC_SYNTHESIZE_READONLY(bool, isDPad, IsDPad);
	//方向个数
	CC_SYNTHESIZE(int, numberOfDirections,NumberOfDirections);

	//虚拟摇杆半径
	CC_SYNTHESIZE_READONLY(float, joystickRadius, JoystickRadius);
	//拇指活动半径
	CC_SYNTHESIZE_READONLY(float, thumbRadius,ThumbRadius);
	//摇杆死亡半径
	CC_SYNTHESIZE_READONLY(float, deadRadius,DeadRadius);

	//是否活动中
	CC_SYNTHESIZE_READONLY(bool, active, IsActive);

	virtual ~SneakJoystick();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();

	void setIsDPad(bool b);
	void setJoystickRadius(float r);
	void setThumbRadius(float r);
	void setDeadRadius(float r);

	bool onTouchBegan(Touch* touch,Event* event);
	void onTouchMoved(Touch* touch,Event* event);
	void onTouchEnded(Touch* touch,Event* event);
	void onTouchCancelled(Touch* touch,Event* event);

	EventListenerTouchOneByOne* mEventListenerTouch;
private:
	void updateVelocity(Vec2 point);
	//void setTouchRadius();
};









