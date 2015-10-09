#pragma once

#include "cocos2d.h"
#include "SneakyJoystick.h"

USING_NS_CC;
using namespace std;

class SneakJoystickSkinnedBase : public Layer
{
public:
	CREATE_FUNC(SneakJoystickSkinnedBase);
	bool init();
	virtual ~SneakJoystickSkinnedBase();

	CC_SYNTHESIZE_READONLY(Sprite*, backgroundSprite, BackgroundSprite);
	CC_SYNTHESIZE_READONLY(Sprite*, thumbSprite, ThumbSprite);
	CC_SYNTHESIZE_READONLY(SneakJoystick*, joystick, Joystick);

	void updatePositions(float delta);
	void setContentSize(Size s);
	void setBackgroundSprite(Sprite* bg);
	void setThumbSprite(Sprite* thumb);
	void setJoystick(SneakJoystick* joys);

private:

};









