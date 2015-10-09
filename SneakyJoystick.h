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

	//ҡ������
	CC_SYNTHESIZE_READONLY(Vec2, stickPosition, StickPosition);
	//�Ƕ�
	CC_SYNTHESIZE_READONLY(float, degrees, Degrees);
	//�ٶ�
	CC_SYNTHESIZE_READONLY(Vec2, velocity, Velocity);
	//�Ƿ��Զ��ص����ĵ�
	CC_SYNTHESIZE(bool, autoCenter, AutoCenter);
	//�Ƿ�����������
	CC_SYNTHESIZE(bool, hasDeadzone, HasDeadzone);
	CC_SYNTHESIZE_READONLY(bool, isDPad, IsDPad);
	//�������
	CC_SYNTHESIZE(int, numberOfDirections,NumberOfDirections);

	//����ҡ�˰뾶
	CC_SYNTHESIZE_READONLY(float, joystickRadius, JoystickRadius);
	//Ĵָ��뾶
	CC_SYNTHESIZE_READONLY(float, thumbRadius,ThumbRadius);
	//ҡ�������뾶
	CC_SYNTHESIZE_READONLY(float, deadRadius,DeadRadius);

	//�Ƿ���
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









