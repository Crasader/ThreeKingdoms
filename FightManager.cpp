#include "FightManager.h"
#include "UserData.h"
#include "SceneRule.h"
#include "tools/GameUtils.h"
#include "SystemConfigRule.h"
#include "NPCManager.h"

bool FightManager::init()
{
	currentRate = 1;
	currentAnger = INSTANCE(UserData)->getAnger();
	return true;
}

void FightManager::enterFight()
{
	int sceneId = INSTANCE(UserData)->getCurrentSceneId();
	selectBossId();

	skillNpcVector = INSTANCE(SceneRule)->getSkillNpcId(sceneId);

	//����npc
	Director::getInstance()->getScheduler()->schedule(CC_SCHEDULE_SELECTOR(FightManager::createNpc),this,5.0f,false);

	//npc��������
	INSTANCE(NPCManager)->startUpdate();
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

//�Ƿ񹥻���Χ��
bool FightManager::attackabel(Rect attackRect,Rect hurtRect)
{
	return attackRect.intersectsRect(hurtRect);
}

bool FightManager::npcCanAttackRole(NPC* npc)
{
	auto rR = getRole()->getHurtRect();
	auto nR = npc->getAttackRect();
	if (attackabel(nR,rR))
	{
		return true;
	}
	return false;
}

//npc������ɫ���ͷż���
void FightManager::npcAttack(NPC* npc)
{
	if (npcCanAttackRole(npc))
	{
		getRole()->playHurt(npc->getNpcAttackPenalty());
	}
}

void FightManager::npcSkill(int skillId)
{

}

void FightManager::roleSkill()
{
	currentAnger = 0;
	INSTANCE(UserData)->setAnger(currentAnger);
}


//��ɫ�������һЩЧ��
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

//���ֹ����Ƿ�ɹ�
bool FightManager::attackNpcSuccess()
{
	//TODO:
	return true;
}
//��ȡ���ֹ�����÷���
int FightManager::getGainScore()
{
	return 1;
}
int FightManager::currentGainScore()
{
	return 1;
}

//�ͷż���
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
	//����npc
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

void FightManager::selectBossId()
{
	int sceneId = INSTANCE(UserData)->getCurrentSceneId();
	if (bossVector.size() == 0)
	{
		bossVector = INSTANCE(SceneRule)->getSceneBossId(sceneId);
	}

	currentBossVector.clear();
	int count = INSTANCE(SceneRule)->getSceneBossCount(sceneId);
	//ÿ��ĵ�һ��boss���뵽��ǰboss��
	for (int i = 0; i < count; i++)
	{
		currentBossVector.push_back(bossVector[0]);
		bossVector.erase(bossVector.begin());
	}
}

void FightManager::createNpc(float dt)
{
	Director::getInstance()->getScheduler()->unschedule(CC_SCHEDULE_SELECTOR(FightManager::createNpc),this);
	//npc������
	log("max:%d",INSTANCE(SystemConfigRule)->getSentTroopsMaxNumber());
	log("min:%d",INSTANCE(SystemConfigRule)->getSentTroopsMinNumber());
	int npcNum = INSTANCE(SystemConfigRule)->getSentTroopsMinNumber() + 
		INSTANCE(GameUtils)->getRandom(INSTANCE(SystemConfigRule)->getSentTroopsMaxNumber() - INSTANCE(SystemConfigRule)->getSentTroopsMinNumber() + 1);
	//ʱ����
	int refreshTime = INSTANCE(SystemConfigRule)->getSendTroopsMinTime() +
		INSTANCE(GameUtils)->getRandom(INSTANCE(SystemConfigRule)->getSendTroopsMaxTime() - INSTANCE(SystemConfigRule)->getSendTroopsMinTime() + 1);

	int sceneId = INSTANCE(UserData)->getCurrentSceneId();
	vector<int> npcIds = INSTANCE(SceneRule)->getNpcId(sceneId);
	for (int i = 0; i < npcNum; i++)
	{
	  int npcId = INSTANCE(GameUtils)->getRandomFromVector(npcIds);
	  INSTANCE(NPCManager)->createRandomNpc(npcId);
	}
	

	Director::getInstance()->getScheduler()->schedule(CC_SCHEDULE_SELECTOR(FightManager::createNpc),this,refreshTime,false);
	//Director::getInstance()->getScheduler()->schedule(CC_SCHEDULE_SELECTOR(FightManager::createNpc),this,5.0f,false);
}


