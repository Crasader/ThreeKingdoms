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

	//处理虚拟摇杆自定义消息
	virtual void onEnter();
	virtual void onExit();

	//获取角色方向
	RoleDirection getRoleDirection();
	
	//获取角色攻击区域和受伤区域
	Rect getAttackRect();
	Rect getHurtRect();

	//技能消耗怒气值
	int getSkillCost();
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
	EventListenerCustom* listener;

	bool attackCompleted;

	//角色最大连招次数
	int evenStrokes;
private:
	void initRole();

	void playStand();
	void playRun();
	void playSkill();
	void playAttack();
	void skillComplete();
	void startSkill(float dt);
	void attackComplete();
	void startAttack(float dt);
	void allowNextAttack(float dt);
	//角色攻击次数
	int getAttackMultiple();

	Animate* getAnimate(RoleStatus status,float duration = 0.1f);

	void joyStickHandler(string direction);
	void setRolePosition(Vec2 p);
	bool isAttacking();




};