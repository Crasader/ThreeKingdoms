#pragma once

#include "cocos2d.h"

USING_NS_CC;
using namespace std;

class SingleSceneFrame:public Node
{
public:
	static SingleSceneFrame* create(int sceneId);
	SingleSceneFrame(int sceneId);
	~SingleSceneFrame();
	virtual bool init();
private:
	int sceneId;//³¡¾°Id
private:
	void initContent();
};