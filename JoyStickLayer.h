#pragma once

#include "cocos2d.h"
#include "SneakyJoystick.h"
#include "SneakyJoystickSkinnedBase.h"
#include "tools/ButtonUtils.h"

USING_NS_CC;
using namespace std;

//消息名
#define JoyStick_status "JoyStick_status"
//消息附加数据
#define JoyStick_none "JoyStick_none"
#define JoyStick_right "JoyStick_right"
#define JoyStick_left "JoyStick_left"
#define JoyStick_up "JoyStick_up"
#define JoyStick_down "JoyStick_down"
#define JoyStick_right_down "JoyStick_right_down"
#define JoyStick_right_up "JoyStick_right_up"
#define JoyStick_left_down "JoyStick_left_down"
#define JoyStick_left_up "JoyStick_left_up"

#define JoyStick_attack "JoyStick_attack"
#define JoyStick_skill "JoyStick_skill"

class JoyStickLayer:public Layer
{
public:
	CREATE_FUNC(JoyStickLayer);
	virtual bool init();
private:
	void initJoyStickLayer();

	void skillTips();

	void update(float dt);
private:
	SneakJoystick* joystick;
	SneakJoystickSkinnedBase* joystickSkin;
	ControlButton* attackBtn;
	ControlButton* skillBtn;
	ProgressTimer* skillPro;

	Vec2 lastPoi;
	
};