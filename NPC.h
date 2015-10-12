#pragma once

#include "cocos2d.h"
#include "BaseRole.h"
#include "NPCRule.h"
USING_NS_CC;
using namespace std;

//npc����ʱ��״̬
enum RunAwayStatus
{
	RunAwayStatus_none,//�ٶȲ���
	RunAwayStatus_speedDown,//��������
	RunAwayStatus_speedUp,//��������
};

//���ӵ�״̬
enum TroopsType
{
	TroopsType_none,
	TroopsType_attack,
	TroopsType_noAttack,
};

class NPC:public Node
{
public:
	//npcid, ���ﳯ���ٶȣ��Ƿ�Boos������״̬
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

	//npc�����뿪
	void acceleratedMove();
	
	int getNpcAttackType();

	TroopsType getNpcTroopsType();

	//npc�Ĺ���Ч��
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
	//�����뿪
	bool accelerated;

	Size hurtSize;
	int skillId;
	//miss����
	int missRate;

	int npcMoney;
	int npcIntegral;
	int npcAnger;

	//Ӳֱ
	float standProbability;

	RunAwayStatus runAwayStatus;

	int npcAttackType;

	//����Ч��
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
	//�����󷴻�
	void playAttackBack();
	void attackBackComplete();
	void startAttackBack(float dt);
	//����������
	void runAway(bool speedUp);
	void runAwayComplete(float dt);

	void playWalkAnimate(bool changeY = false);

	int getNpcPositionY();

	void setAttackableHandler(float dt);

};





