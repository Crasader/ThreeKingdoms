#pragma once

#include "cocos2d.h"
#include "GameCommon.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

class ButtonUtils:public cocos2d::Ref
{
public:
	CLASS_INSTANCE(ButtonUtils);
	bool init();

	void setButtonTitle(cocos2d::extension::ControlButton* button,const std::string& titleName);

	ControlButton* createButton(const std::string& frameName,
		Size size,
		const std::string& label,
		float labelSize = 22.0f,
		Color3B labelColor = Color3B::WHITE);

	cocos2d::extension::ControlButton* createButton(const std::string& normalFrame,
		const std::string& highLightFrame,
		const std::string& disableFrame,
		cocos2d::Size size,
		const std::string& label,
		float labelSize = 22.0f,
		cocos2d::Color3B labelColor = cocos2d::Color3B::WHITE);
};