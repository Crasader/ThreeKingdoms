#pragma once

#include "cocos2d.h"
#include "cocos-ext.h"
#include "BaseRole.h"
#include "NPC.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace std;

class FightScene : public Layer
{
public:
	FightScene();
	~FightScene();
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(FightScene);

	virtual void onEnter();
	virtual void onExit();

	//��ӵ��˵�������
	void addNpcToScene(NPC* npc);
private:
	Node* mapNode;
	Sprite* bg;

	BaseRole* role;

	EventListenerCustom* listenerShake;
private:
	void initMap();
	void initUI();
	void initRole();

	void update(float dt);
	//��������
	void shake();
};