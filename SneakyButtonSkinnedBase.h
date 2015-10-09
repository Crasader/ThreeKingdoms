#pragma once

#include "cocos2d.h"
#include "SneakyButton.h"

USING_NS_CC;
using namespace std;

class SneakyButtonSkinnedBase : public Layer
{
public:
	CREATE_FUNC(SneakyButtonSkinnedBase);
	bool init();
	virtual ~SneakyButtonSkinnedBase();

	CC_SYNTHESIZE_READONLY(Sprite*, defaultSprite, DefaultSprite);
	CC_SYNTHESIZE_READONLY(Sprite*, activatedSprite, ActivatedSprite);
	CC_SYNTHESIZE_READONLY(Sprite*, disabledSprite, DisabledSprite);
	CC_SYNTHESIZE_READONLY(Sprite*, pressSprite, PressSprite);
	CC_SYNTHESIZE_READONLY(SneakyButton*, sbutton, Sbutton)

	void watchSelf(float delta);
	void setContentSize(Size s);
	void setDefaultSprite(Sprite *aSprite);
	void setActivatedSprite(Sprite *aSprite);
	void setDisabledSprite(Sprite *aSprite);
	void setPressSprite(Sprite *aSprite);
	void setButton(SneakyButton *aButton);

private:

};









