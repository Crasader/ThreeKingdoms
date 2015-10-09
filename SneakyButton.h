#pragma once

#include "cocos2d.h"

USING_NS_CC;
using namespace std;

class SneakyButton : public Node
{
public:
	//Public methods
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
	bool initWithRect(Rect rect);
	void limiter(float delta);
	void setRadius(float r);

private:
    EventListenerTouchOneByOne * mEventListenerTouch;
    
protected:
	Vec2 center;
	float radiusSq;

	Rect bounds;

	CC_SYNTHESIZE(bool, status, Status);
	CC_SYNTHESIZE_READONLY(bool, active, IsActive);
	CC_SYNTHESIZE_READONLY(bool, value, Value);
	CC_SYNTHESIZE(bool, isHoldable, IsHoldable);
	CC_SYNTHESIZE(bool, isToggleable, IsToggleable);
	CC_SYNTHESIZE(float, rateLimit, RateLimit);

	CC_SYNTHESIZE_READONLY(float, radius, Radius);

    
    bool onTouchBegan(Touch* touch, Event* event);
    void onTouchMoved(Touch* touch, Event* event);
    void onTouchEnded(Touch* touch, Event* event);
    void onTouchCancelled(Touch* touch, Event* event);
};









