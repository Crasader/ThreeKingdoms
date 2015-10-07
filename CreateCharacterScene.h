#pragma once

#include "cocos2d.h"
#include "cocos-ext.h"
#include "extensions/ExtensionExport.h"
#include "SingleCharacter.h"

USING_NS_CC;
USING_NS_CC_EXT;

class CreateCharacterScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(CreateCharacterScene);

	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
    void onChangeAccount(cocos2d::Ref* pSender);

	virtual void update(float dt) override;
private:
	Vector<SingleCharacter*> characterArray;//½ÇÉ«Êý×é

	void initContent();
	void startGame(Ref* senderz,Control::EventType controlEvent);
	void unSelectAll();
	void initBg();

	Color4B getColor();

	ControlButton* changeAccount;
	Label* text;

	Sprite* bg1;
	Sprite* bg2;
	
	EventListenerCustom* listener;
};
