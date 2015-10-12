#pragma once

#include "cocos2d.h"
#include "BaseRole.h"
#include "NPCRule.h"
USING_NS_CC;
using namespace std;

//npc逃离时的状态
enum RunAwayStatus
{
	RunAwayStatus_none,//速度不变
	RunAwayStatus_speedDown,//减速逃离
	RunAwayStatus_speedUp,//加速逃离
};

//部队的状态
enum TroopsType
{
	TroopsType_none,
	TroopsType_attack,
	TroopsType_noAttack,
};

class NPC:public Node
{
public:
	//npcid, 人物朝向，速度，是否Boos，攻击状态
	static NPC* create(int npcId, RoleDirection direction, int speed, bool isBoos, TroopsType troopsType);
	NPC(int npcId, RoleDirection direction, int speed, bool isBoos, TroopsType troopsType);
	~NPC();
	virtual bool init();
	virtual void onEnter();
	virtual void onExit();

	int getNpcId();

	void playWalk();
	void playHurt(bool hit);
	void playDie();
	void playStop();
	void playStand(float dt);
	void playAttack();

	void setNpcStatus(RoleStatus status);
	RoleStatus getNpcStatus();

	RoleDirection getCurrentDirection();

	Rect getHurtRect();
	Rect getAttackRect();

	float getMiss();

	//int getRow();

	void setIsStop(bool stop);

	bool getNpcIsDead();

	int getNpcMoney();
	int getNpcIntegral();
	int getNpcAnger();
	bool getNpcIsBoss();

	//npc加速离开
	void acceleratedMove();
	
	int getNpcAttackType();

	TroopsType getNpcTroopsType();

	//npc的攻击效果
	int getNpcAttackPenalty();

	void stopAll();

	Sprite* getSprite();
	int getSkillId();

private:
	int npcId;
	bool isDead;
	bool isBoos;
	RoleDirection currentDirection;
	RoleStatus currentStatus;
	int npcSpeed;
	TroopsType troopsType;
	Sprite* npcRole;
	bool attackable;
	bool isStop;
	//加速离开
	bool accelerated;

	Size hurtSize;
	int skillId;
	//miss概率
	int missRate;

	int npcMoney;
	int npcIntegral;
	int npcAnger;

	//硬直
	float standProbability;

	RunAwayStatus runAwayStatus;

	int npcAttackType;

	//攻击效果
	int attackPenalty;
private:
	void hurtComplete();
	void dieComplete();
	void standComplete(float dt);
	
	void startMove(bool changeY);
	void stopMove();

	Animate* getAnimate(RoleStatus status);

	void playBlood();

	void startAttack(float dt);
	void attackComplete();
	//被击后反击
	void playAttackBack();
	void attackBackComplete();
	void startAttackBack(float dt);
	//被击后逃跑
	void runAway(bool speedUp);
	void runAwayComplete(float dt);

	void playWalkAnimate(bool changeY = false);

	int getNpcPositionY();

	void setAttackableHandler(float dt);

};





