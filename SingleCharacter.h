//角色
#pragma once

#include "cocos2d.h"

USING_NS_CC;
using namespace std;

//消息名称
#define UnselectAllSingleCharacter "UnselectAllSingleCharacter"

enum FrameType
{
	FrameType_role,
	FrameType_name,
	FrameType_lightEffect,
};

class SingleCharacter:public Sprite
{
public:
	static SingleCharacter* create(int roleId);
	SingleCharacter(int roleId);
	~SingleCharacter();
	virtual bool init();

	void setSelect(bool select);
private:
	int roleId;//角色id

	Sprite* lightEffect;
	Sprite* selectedFlag;
	Sprite* roleName;

private:
	void initContent();

	string getFrameName(int roleId,FrameType type);
	string getLightEffect(int roleId);

	void skillComplete();
};