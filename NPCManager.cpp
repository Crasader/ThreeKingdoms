#include "NPCManager.h"
#include "tools/GameUtils.h"
#include "FightManager.h"

bool NPCManager::init()
{
	isStop = false;
	return true;
}

void NPCManager::createTroopsNPC(int npcId,int formationIndex,RoleDirection direction,int speed,TroopsType troopsType)
{
	if(isStop)
	{
		return;
	}
	NPC* npc = NPC::create(npcId,direction,speed,false,troopsType);
	//����������npc��λ��
	npc->setPosition(getNPCPosition(formationIndex,direction));
	npcArray.pushBack(npc);
	getFightScene()->addChild(npc);
}

void NPCManager::createRandomNpc(int npcId,bool isBoss)
{
	if (isStop && !isBoss)
	{
		return;
	}
	//����0~1������޷��������
	default_random_engine e;
	uniform_real_distribution<float> u(0,1);
	RoleDirection direction = u(e) > 0.5f ? RoleDirection_left : RoleDirection_right;
	int speed = INSTANCE(NPCRule)->getNpcSpeed(npcId);
	//���һ����
	int index = INSTANCE(GameUtils)->getRandom(5);

	NPC* npc = NPC::create(npcId,direction,speed,isBoss,TroopsType_none);
	npc->setPosition(getNPCPosition(index,direction));
	//npc->setPosition(100.0f,100.0f);
	npcArray.pushBack(npc);
	getFightScene()->addChild(npc);
}

void NPCManager::removeNPC(NPC *npc)
{
	tempNpcArray.pushBack(npc);
	npcArray.eraseObject(npc);
}

void NPCManager::keepAllNpcStop(int second)
{

}
void NPCManager::allNpcStopComplete()
{

}

Vector<NPC*> NPCManager::getAllNpc()
{
	return npcArray;
}

void NPCManager::removeAllNpc()
{

}

void NPCManager::startUpdate()
{
	Director::getInstance()->getScheduler()->schedule(CC_SCHEDULE_SELECTOR(NPCManager::updateNpcInfo),this,0.3f,false);
}
void NPCManager::stopUpdate()
{

}

//void createGuideNpc_1();
//void createGuideNpc_2();

void NPCManager::setStop(bool param)
{

}

Vec2 NPCManager::getNPCPosition(int index,RoleDirection direction)
{
	if (direction == RoleDirection_right)
	{
		return Vec2(-700 - (index / 5)*100, (index % 5) * 60 - 250);
	}
	else
	{
		return Vec2(700 + (index / 5)*100, (index % 5) * 60 - 250);
	}
}

void NPCManager::updateNpcInfo(float dt)
{
	//for (auto& npc : npcArray)
	//��Ϊ��Ҫɾ��npcArray�е�Ԫ�أ��������ﲻ���÷�Χfor
	//����i��ʼ��ΪnpcArray�����һ�����ݼ�����
	for (int i = npcArray.size() - 1; i >= 0; i--)
	{
		NPC* npc = static_cast<NPC*>(npcArray.at(i));
		bool dead = false;
		if (npc->getCurrentDirection() == RoleDirection_left && npc->getPositionX() <= -720)
		{
			dead = true;
		}
		if (npc->getCurrentDirection() == RoleDirection_right && npc->getPositionX() >= 720)
		{
			dead = true;
		}

		if (dead)
		{
			npc->removeFromParent();
			npcArray.eraseObject(npc);
			if (npc->getNpcIsBoss())
			{
				//TODO
			}
		}
		else
		{
			if (npc->getNpcAttackType() == 2 ||
				(npc->getNpcTroopsType() == TroopsType_attack && npc->getNpcAttackType() != 0))
			{
				if (INSTANCE(FightManager)->npcCanAttackRole(npc))
				{
					npc->playAttack();
				}
			}
		}
	}
}

void NPCManager::stopHandler()
{

}


void NPCManager::removeNpcHandler()
{

}
