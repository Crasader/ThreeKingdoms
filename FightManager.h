#pragma once

#include "cocos2d.h"
#include "tools/GameCommon.h"
#include "BaseRole.h"
#include "NPC.h"

USING_NS_CC;
using namespace std;

//boss出现时间间隔
#define BossAppearTime 300
//npc逃离速度系数
#define NpcRunAwaySpeedCoefficient 3
//清屏时npc逃离系数
#define ClearNpcSpeedCoefficient 4

//消息名称
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

	//角色攻击和释放技能
	void roleAttack(int multiple);
	void roleSkill();

	//npc攻击角色和释放技能
	void npcAttack(NPC* npc);
	void npcSkill(int skillId);
	bool npcCanAttackRole(NPC* npc);


	//攻击得分系数
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

	//从boss数组中选取id到currentBOSSVector中
	void selectBossId();
	//生产npc
	void createNpc(float dt);

	//是否攻击范围内
	bool attackabel(Rect attackRect,Rect hurtRect);
private:
	//当前倍率
	int currentRate;
	//当前怒气
	int currentAnger;
	//连招最大次数
	int evenStrokes;

	//本轮攻击是否成功
	bool attackNpcSuccess();
	//获取本轮攻击获得分数
	int getGainScore();
	int currentGainScore();
	bool attackSuccess;

	//boss数组
	vector<int> bossVector;
	//当前boss数组
	vector<int> currentBossVector;
	//当前技能兵数组
	vector<int> skillNpcVector;
};
