#pragma once

#include "cocos2d.h"
#include "tools/GameCommon.h"

USING_NS_CC;
using namespace std;

class AnimateManager:public Ref
{
public:
	CLASS_INSTANCE(AnimateManager);
	bool init();

	//Ëõ·ÅºóÉ¾£º³ý
	void showScaleAnimate(Node* sender);
	void showAnimate(Node* sender);
	void hideAnimate(Node* sender);

	void doRemoveFromParentAndCleanup(Node* sender,bool cleanup);
};
