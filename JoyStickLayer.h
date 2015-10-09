#pragma once

#include "cocos2d.h"
#include "SneakyJoystick.h"
#include "SneakyJoystickSkinnedBase.h"
#include "tools/ButtonUtils.h"

USING_NS_CC;
using namespace std;

class JoyStickLayer:public Layer
{
public:
	CREATE_FUNC(JoyStickLayer);
	virtual bool init();
private:
	void initJoyStickLayer();
private:
	SneakJoystick* joystick;
	SneakJoystickSkinnedBase* joystickSkin;
	ControlButton* attackBtn;
	ControlButton* skillBtn;
	
};