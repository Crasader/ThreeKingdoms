#pragma once

#include "cocos2d.h"
#include "tools/GameCommon.h"

USING_NS_CC;

class ChapterScene : public Layer
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(ChapterScene);
private:
	void initContent();
};