#pragma once

#include "cocos2d.h"
#include "tools/GameCommon.h"
#include "BaseRole.h"
#include "NPC.h"

USING_NS_CC;
using namespace std;

//boss����ʱ����
#define BossAppearTime 300
//npc�����ٶ�ϵ��
#define NpcRunAwaySpeedCoefficient 3
//����ʱnpc����ϵ��
#define ClearNpcSpeedCoefficient 4

//��Ϣ����
#define NoticeUpdateMoney "noticeUpdateMoney"
#define NoticeUpdateIntegral "noticeUpdateIntegral"
#define NoticeUpdatePot "noticeUpdatePot"

#define NoticeSkillShake "noticeSkillShake"

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

	//npc������ɫ���ͷż���
	void npcAttack(NPC* npc);
	void npcSkill(int skillId);
	bool npcCanAttackRole(NPC* npc);


	//�����÷�ϵ��
	CC_SYNTHESIZE(int, attackMultiple, AttackMultiple);

	int getCurrentRate();

	bool enoughMoney();
	bool enoughAnger();
	float getAnger();

	int getEvenStrokes();


	BaseRole* getRole();
private:
	void skill(int skillId);
	void skill_30001();
	void skill_30002();
	void skill_30003();
	void skill_30004();
	void skill_30005();
	void skill_30006();

	//��boss������ѡȡid��currentBOSSVector��
	void selectBossId();
	//����npc
	void createNpc(float dt);

	//�Ƿ񹥻���Χ��
	bool attackabel(Rect attackRect,Rect hurtRect);
private:
	//��ǰ����
	int currentRate;
	//��ǰŭ��
	int currentAnger;
	//����������
	int evenStrokes;

	//���ֹ����Ƿ�ɹ�
	bool attackNpcSuccess();
	//��ȡ���ֹ�����÷���
	int getGainScore();
	int currentGainScore();
	bool attackSuccess;

	//boss����
	vector<int> bossVector;
	//��ǰboss����
	vector<int> currentBossVector;
	//��ǰ���ܱ�����
	vector<int> skillNpcVector;
};
