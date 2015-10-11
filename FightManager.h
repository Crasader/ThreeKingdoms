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

	//角色攻击和释放技能
	void roleAttack(int multiple);
	void roleSkill();
	//攻击得分系数
	CC_SYNTHESIZE(int, attackMultiple, AttackMultiple);

	int getCurrentRate();

	bool enoughMoney();
	bool enoughAnger();
	float getAnger();

	int getEvenStrokes();
private:
	BaseRole* getRole();
	//当前倍率
	int currentRate;
	//当前怒气
	int currentAnger;
	//连招最大次数
	int evenStrokes;

	void skill(int skillId);
	void skill_30001();
	void skill_30002();
	void skill_30003();
	void skill_30004();
	void skill_30005();
	void skill_30006();

	//本轮攻击是否成功
	bool attackNpcSuccess();
	//获取本轮攻击获得分数
	int getGainScore();
	int currentGainScore();
	bool attackSuccess;
};
