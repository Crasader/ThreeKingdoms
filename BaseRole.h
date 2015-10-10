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

	//��������ҡ���Զ�����Ϣ
	virtual void onEnter();
	virtual void onExit();
private:
	int roleId;
	float speedX;
	float speedY;
	float attackSpeed;
	//�ٶ�ϵ��
	float speedCoefficient;

	RoleStatus currentRoleStatus;
	RoleDirection currentRoleDirection;

	Sprite* role;
	EventListenerCustom* listener;
private:
	void initRole();

	void playStand();
	void playRun();
	void playSkill();
	void playAttack();
	void skillComplete();

	Animate* getAnimate(RoleStatus status,float duration = 0.1f);

	void joyStickHandler(string direction);
	void setRolePosition(Vec2 p);
	bool isAttacking();
};