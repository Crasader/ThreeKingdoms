#include "FightManager.h"
#include "UserData.h"

bool FightManager::init()
{
	currentRate = 1;
	currentAnger = INSTANCE(UserData)->getAnger();
	return true;
}

void FightManager::enterFight()
{

}
void FightManager::exitFight()
{

}

int FightManager::getCurrentRate()
{
	return 1;
}

bool FightManager::enoughMoney()
{
	return true;
}
bool FightManager::enoughAnger()
{
	if (currentAnger >= getRole()->getSkillCost())
	{
		int skillNum = INSTANCE(UserData)->getSkillNum();
		INSTANCE(UserData)->setSkillNum(skillNum + 1);
		return true;
	}
	return false;
}
float FightManager::getAnger()
{
	return float(currentAnger) / float(getRole()->getSkillCost());
}

BaseRole* FightManager::getRole()
{
	return INSTANCE(UserData)->getRole();
}

void FightManager::roleSkill()
{
	currentAnger = 0;
	INSTANCE(UserData)->setAnger(currentAnger);
}


//角色攻击后的一些效果
void FightManager::roleAttack(int multiple)
{
	//attackMultiple = multiple;
	//attackSuccess = attackNpcSuccess();
	//int gainGold = 0;
	//auto rR = getRole()->getAttackRect();
}

int FightManager::getEvenStrokes()
{
	return evenStrokes;
}

//本轮攻击是否成功
bool FightManager::attackNpcSuccess()
{
	//TODO:
	return true;
}
//获取本轮攻击获得分数
int FightManager::getGainScore()
{
	return 1;
}
int FightManager::currentGainScore()
{
	return 1;
}

//释放技能
void FightManager::skill(int skillId)
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("");
	switch (skillId)
	{
	case 30001:
		skill_30001();
		break;
	case 30002:
		skill_30002();
		break;
	case 30003:
		skill_30003();
		break;
	case 30004:
		skill_30004();
		break;
	case 30005:
		skill_30005();
		break;
	case 30006:
		skill_30006();
		break;
	default:
		break;
	}
}

void FightManager::skill_30001()
{
	int gainGold = 0;
	auto winSize = Director::getInstance()->getWinSize();
	//所有npc
}
void FightManager::skill_30002()
{

}
void FightManager::skill_30003()
{

}
void FightManager::skill_30004()
{

}
void FightManager::skill_30005()
{

}
void FightManager::skill_30006()
{

}
