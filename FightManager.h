#pragma once

#include "cocos2d.h"
#include "tools/GameCommon.h"
#include "BaseRole.h"

USING_NS_CC;
using namespace std;

class FightManager:public Ref
{
public:
	CLASS_INSTANCE(FightManager);
	bool init();

	void enterFight();
	void exitFight();

	//��ɫ�������ͷż���
	void roleAttack(int multiple);
	void roleSkill();
	//�����÷�ϵ��
	CC_SYNTHESIZE(int, attackMultiple, AttackMultiple);

	int getCurrentRate();

	bool enoughMoney();
	bool enoughAnger();
	float getAnger();

	int getEvenStrokes();
private:
	BaseRole* getRole();
	//��ǰ����
	int currentRate;
	//��ǰŭ��
	int currentAnger;
	//����������
	int evenStrokes;

	void skill(int skillId);
	void skill_30001();
	void skill_30002();
	void skill_30003();
	void skill_30004();
	void skill_30005();
	void skill_30006();

	//���ֹ����Ƿ�ɹ�
	bool attackNpcSuccess();
	//��ȡ���ֹ�����÷���
	int getGainScore();
	int currentGainScore();
	bool attackSuccess;
};
