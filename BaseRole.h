#pragma once

#include "cocos2d.h"
#include "RoleRule.h"

USING_NS_CC;
using namespace std;

class BaseRole:public Node
{
public:
	static BaseRole* create(int roleId);
	BaseRole(int roleId);
	~BaseRole();
	virtual bool init();
private:
	int roleId;
	float speedX;
	float speedY;
	float attackSpeed;
	//速度系数
	float speedCoefficient;

	RoleStatus currentRoleStatus;
	RoleDirection currentRoleDirection;

	Sprite* role;
private:
	void initRole();

	void playStand();

	Animate* getAnimate(RoleStatus status,float duration = 0.1f);
};