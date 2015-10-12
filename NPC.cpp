#include "NPC.h"
#include "NPCRule.h"
#include "tools/GameCommon.h"
#include "FightManager.h"
#include "tools/AnimationUtils.h"
#include "NPCManager.h"
#include "tools/GameUtils.h"


NPC::NPC(int npcId, RoleDirection direction, int speed, bool isBoos, TroopsType troopsType)
{
	this->npcId = npcId;
	this->currentDirection = direction;
	this->isBoos = isBoos;
	this->troopsType = troopsType;
	if (speed == 0)
	{
		this->npcSpeed = INSTANCE(NPCRule)->getNpcSpeed(npcId);
	}
	else
	{
		this->npcSpeed = speed;
	}

	currentStatus = RoleStatusNone;
	isDead = false;
	npcRole = nullptr;

	accelerated = false;
	isDead = false;
	attackable = true;
}
NPC::~NPC()
{

}

NPC* NPC::create(int npcId, RoleDirection direction, int speed, bool isBoos, TroopsType troopsType)
{
	NPC* npc = new NPC(npcId, direction, speed, isBoos, troopsType);
	if (npc && npc->init())
	{
		npc->autorelease();
		return npc;
	}
	else
	{
		delete npc;
		npc = nullptr;
		return nullptr;
	}
}

bool NPC::init()
{
	if (!Node::init())
	{
		return false;
	}
	string img = INSTANCE(NPCRule)->getNpcImgPath(npcId);
	img.append(INSTANCE(NPCRule)->getNpcFrameNameByNpcId(npcId,RoleStatusWalk));
	img.append(".plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(img);

	img = INSTANCE(NPCRule)->getNpcFirstFrameNameByNpcId(npcId,RoleStatusWalk);
	npcRole = Sprite::createWithSpriteFrameName(img);
	addChild(npcRole);
	npcRole->setAnchorPoint(INSTANCE(NPCRule)->getNpcAnchorPoint(npcId));
	if (currentDirection == RoleDirection_right)
	{
		npcRole->setFlippedX(false);
	}
	else
	{
		npcRole->setFlippedX(true);
	}
	auto shadow = Sprite::create("fightImg/role_shadow.png");
	npcRole->addChild(shadow, -1);
	shadow->setPosition(npcRole->getAnchorPointInPoints());

	if (INSTANCE(NPCRule)->getNpcSkillId(npcId) != 0)
	{
		auto effect = Sprite::create();
		auto animation = INSTANCE(AnimationUtils)->getCommonAnimation("fightImg/skillNpcEffect.plist","skillNpcEffect");
		auto action = RepeatForever::create(Animate::create(animation));
		effect->runAction(action);
		npcRole->addChild(effect);
		effect->setAnchorPoint(Vec2(0.5f,0.2f));
		effect->setPosition(npcRole->getAnchorPointInPoints());
	}

	hurtSize = INSTANCE(NPCRule)->getNpcHurtSize(npcId);
	skillId = INSTANCE(NPCRule)->getNpcSkillId(npcId);
	missRate = INSTANCE(NPCRule)->getNpcDodge(npcId);
	npcMoney = INSTANCE(NPCRule)->getNpcMoney(npcId);
	npcIntegral = INSTANCE(NPCRule)->getNpcIntegral(npcId);
	npcAnger = INSTANCE(NPCRule)->getNpcAnger(npcId);
	standProbability = INSTANCE(NPCRule)->getNpcStandProbability(npcId);
	npcAttackType = INSTANCE(NPCRule)->getNpcAttackType(npcId);
	runAwayStatus = RunAwayStatus_none;
	attackPenalty = INSTANCE(NPCRule)->getNpcAttackPenalty(npcId);

	return true;
}
void NPC::onEnter()
{
	Node::onEnter();
	//创建npc后就开始移动
	playWalk();
	if (troopsType == TroopsType_none && standProbability > 0)
	{
		getScheduler()->schedule(CC_SCHEDULE_SELECTOR(NPC::playStand),this,3 + INSTANCE(GameUtils)->getRandom(3),false);
	}
}
void NPC::onExit()
{
	Node::onExit();
}

int NPC::getNpcId()
{
	return npcId;
}

Animate* NPC::getAnimate(RoleStatus status)
{
	string img = INSTANCE(NPCRule)->getNpcFrameNameByNpcId(npcId,status);
	float duration;
	if (status == RoleStatusWalk)
	{
		duration = 6.0f/npcSpeed;
		if (accelerated)
		{
			duration = duration / (ClearNpcSpeedCoefficient/2);
		}
		if (runAwayStatus == RunAwayStatus_speedUp)
		{
			duration = duration / (NpcRunAwaySpeedCoefficient/2);
		}
		else if (runAwayStatus == RunAwayStatus_speedDown)
		{
			duration = duration * NpcRunAwaySpeedCoefficient;
		}
	}
	else
	{
		duration = 0.1;
	}

	auto animation = INSTANCE(AnimationUtils)->getModelAnimation(INSTANCE(NPCRule)->getNpcModelId(npcId),img,img,duration);
	auto animate = Animate::create(animation);
	return animate;
}

void NPC::playWalkAnimate(bool changeY)
{
	this->stopAllActions();
	npcRole->stopAllActions();
	auto action = RepeatForever::create(getAnimate(RoleStatusWalk));
	npcRole->runAction(action);
	startMove(changeY);
}

void NPC::playWalk()
{
	if (currentStatus == RoleStatusWalk)
	{
		return;
	}
	currentStatus = RoleStatusWalk;
	playWalkAnimate();
}
void NPC::playHurt(bool hit)
{
	if (isDead)
	{
		return;
	}
	//停止反击
	getScheduler()->unschedule(CC_SCHEDULE_SELECTOR(NPC::startAttackBack),this);
	currentStatus = RoleStatusHurt;
	stopMove();

	npcRole->stopAllActions();

	if (hit)
	{
		isDead = true;
		getScheduler()->unscheduleAllForTarget(this);
	}

	float duration;
	if (accelerated)
	{
		duration = 0.05f;
	}
	else
	{
		duration = 0.1f;
	}

	auto animate = getAnimate(RoleStatusHurt);
	auto action = Sequence::create(animate,
		DelayTime::create(0.1f),
		CallFuncN::create(CC_CALLBACK_0(NPC::hurtComplete,this)),nullptr);
	npcRole->runAction(action);
	
	playBlood();

}
void NPC::hurtComplete()
{
	if (isDead)
	{
		playDie();
	}
	else
	{
		if (isStop)
		{
			npcRole->stopAllActions();
			npcRole->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(
				INSTANCE(NPCRule)->getNpcFirstFrameNameByNpcId(npcId,RoleStatusWalk)));
		}
		else
		{
			bool isAttackBack;
			int attackType = INSTANCE(NPCRule)->getNpcAttackType(npcId);
			if (troopsType == TroopsType_none)
			{
				if (attackType == 0 || attackType == 2)
				{
					isAttackBack = false;
				}
				else
				{
					if (INSTANCE(GameUtils)->getRandomFromFloat(INSTANCE(NPCRule)->getNpcAttackProbability(npcId)))
					{
						isAttackBack = true;
					}
					else
					{
						isAttackBack = false;
					}
				}
			}
			else if (troopsType == TroopsType_attack)
			{
				isAttackBack = false;
			}
			else
			{
				isAttackBack = false;
			}


			if (isAttackBack)
			{
				//在攻击范围内反击
				if (INSTANCE(FightManager)->npcCanAttackRole(this))
				{
					playAttackBack();
				}
				else
				{
					playWalk();
				}
			}
			else
			{
				float speedUpP = INSTANCE(NPCRule)->getNpcSpeedUpProbability(npcId);
				float speedDownP = INSTANCE(NPCRule)->getNpcSpeedDownProbability(npcId);
				if (speedUpP == 0 && speedDownP == 0)
				{
					//不反击不逃跑
					playWalk();
				}
				else if (speedUpP != 0)
				{
					//加速逃跑
					if (INSTANCE(GameUtils)->getRandomFromFloat(speedUpP))
					{
						runAway(true);
					}
					else
					{
						playWalk();
					}
				}
				else
				{
					//减速
					if (INSTANCE(GameUtils)->getRandomFromFloat(speedDownP))
					{
						runAway(false);
					}
					else
					{
						playWalk();
					}
				}
			}
		}
	}
}

void NPC::playDie()
{
	if (currentStatus == RoleStatusDie)
	{
		return;
	}
	stopMove();
	getScheduler()->unscheduleAllForTarget(this);
	npcRole->stopAllActions();
	
	auto animate = getAnimate(RoleStatusDie);
	float duration = animate->getDuration()/2;
	auto action = Sequence::create(animate,DelayTime::create(5.0f),CallFuncN::create(CC_CALLBACK_0(NPC::dieComplete,this)),nullptr);
	npcRole->runAction(action);

	MoveBy* move;
	if (INSTANCE(FightManager)->getRole()->getPositionX() > getPositionX())
	{
		//向左偏移
		int offset = Director::getInstance()->getWinSize().width/2 - getPositionX() + 300;
		move = MoveBy::create(duration, Vec2(offset > -350 ? -350 : offset,0));
		npcRole->setFlippedX(true);
	}
	else
	{
		//向右偏移
		int offset = Director::getInstance()->getWinSize().width/2 - getPositionX() - 300;
		move = MoveBy::create(duration, Vec2(offset < 350 ? 350 : offset,0));
		npcRole->setFlippedX(false);
	}
	this->runAction(move);

	INSTANCE(NPCManager)->removeNPC(this);

	if (skillId != 0)
	{
		//TODO
		//INSTANCE(FightManager)->npcSkill(skillId);
	}
	if (npcAnger > 0)
	{
		//TODO
	}
}
void NPC::dieComplete()
{
	removeFromParent();
}
void NPC::playStop()
{
	if (!isDead)
	{
		currentStatus = RoleStatusNone;
		isStop = true;
		stopAllActions();
		npcRole->stopAllActions();
		getScheduler()->pauseTarget(this);
	}
}
void NPC::playStand(float dt)
{
	getScheduler()->unschedule(CC_SCHEDULE_SELECTOR(NPC::playStand),this);
	if (currentStatus == RoleStatusStand)
	{
		return;
	}
	stopMove();

	currentStatus = RoleStatusStand;

	npcRole->stopAllActions();
	auto animate = getAnimate(RoleStatusStand);
	auto action = RepeatForever::create(animate);
	npcRole->runAction(action);
	getScheduler()->schedule(CC_SCHEDULE_SELECTOR(NPC::standComplete),this,3 + INSTANCE(GameUtils)->getRandom(3),false);
}
void NPC::standComplete(float dt)
{
	getScheduler()->unschedule(CC_SCHEDULE_SELECTOR(NPC::standComplete),this);
	if (INSTANCE(GameUtils)->getRandomFromFloat(standProbability))
	{
		getScheduler()->schedule(CC_SCHEDULE_SELECTOR(NPC::playStand),this,3 + INSTANCE(GameUtils)->getRandom(3),false);
	}
	playWalk();
}
void NPC::playAttack()
{
	if (currentStatus == RoleStatusAttack || !attackable)
	{
		return;
	}
	currentStatus = RoleStatusAttack;
	stopMove();
	npcRole->stopAllActions();
	auto animate = getAnimate(RoleStatusAttack);
	auto action = Sequence::create(animate,CallFunc::create(CC_CALLBACK_0(NPC::attackComplete,this)),nullptr);
	npcRole->runAction(action);
	
	getScheduler()->schedule(CC_SCHEDULE_SELECTOR(NPC::startAttack),this,animate->getDuration()/2.0f,false);
	attackable = false;
	getScheduler()->schedule(CC_SCHEDULE_SELECTOR(NPC::setAttackableHandler),this,2.0f,false);
}
void NPC::startMove(bool changeY)
{
	float duration;
	int _x;
	int tempSpeed = npcSpeed;
	if (accelerated)
	{
		tempSpeed = npcSpeed * ClearNpcSpeedCoefficient;
	}

	if (runAwayStatus == RunAwayStatus_speedUp)
	{
		tempSpeed = tempSpeed * NpcRunAwaySpeedCoefficient;
	}
	else if (runAwayStatus == RunAwayStatus_speedDown)
	{
		tempSpeed = tempSpeed / NpcRunAwaySpeedCoefficient;
	}

	if (currentDirection == RoleDirection_right)
	{
		duration = (740 - getPositionX()) / tempSpeed;
		_x = 740;
	}
	else
	{
		duration = (740 + getPositionX()) / tempSpeed;
		_x = -740;
	}

	int posY = getNpcPositionY() - getPositionY();
	auto move = MoveTo::create(duration, Vec2(_x,getPositionY()));
	if (changeY)
	{
		int offsetY = INSTANCE(GameUtils)->getRandomFromFloat(0.5f) ? 60:-60;
		if (getPositionY() + offsetY > -10 || getPositionY() + offsetY < -250)
		{
			offsetY = -offsetY;
		}
		posY += offsetY;
	}

	if (posY != 0)
	{
		auto moveY = MoveBy::create(0.4f,Vec2(0,posY));
		this->runAction(moveY);
	}

	this->runAction(move);
}
void NPC::stopMove()
{
	this->stopAllActions();
}


void NPC::setNpcStatus(RoleStatus status)
{
	currentStatus = status;
}
RoleStatus NPC::getNpcStatus()
{
	return currentStatus;
}

RoleDirection NPC::getCurrentDirection()
{
	return currentDirection;
}

Rect NPC::getHurtRect()
{
	return Rect(getPositionX() - hurtSize.width/2,getPositionY() - hurtSize.height/2, hurtSize.width, hurtSize.height);
}
Rect NPC::getAttackRect()
{
	auto size = INSTANCE(NPCRule)->getNpcAttackSize(npcId);
	if (currentDirection == RoleDirection_left)
	{
		return Rect(getPositionX() - size.width/2,getPositionY() - size.height/2,size.width,size.height);
	}
	else
	{
		return Rect(getPositionX(),getPositionY() - size.height/2,size.width,size.height);
	}
}

float NPC::getMiss()
{
	return missRate;
}

//int NPC::getRow();

void NPC::setIsStop(bool stop)
{
	isStop = stop;
	if (!stop)
	{
		getScheduler()->resumeTarget(this);
	}
}

bool NPC::getNpcIsDead()
{
	return isDead;
}

//这个boss系数是多少，怎么获取
int NPC::getNpcMoney()
{
	if (isBoos)
	{
		return npcMoney * 10;
	}
	return npcMoney;
}
int NPC::getNpcIntegral()
{
	return npcIntegral;
}
int NPC::getNpcAnger()
{
	return npcAnger;
}
bool NPC::getNpcIsBoss()
{
	return isBoos;
}

//npc加速离开
void NPC::acceleratedMove()
{
	getScheduler()->unschedule(CC_SCHEDULE_SELECTOR(NPC::playStand),this);
	accelerated = true;
	//不是受伤状态才能逃跑
	if (currentStatus != RoleStatusHurt)
	{
		playWalkAnimate();
	}
}

int NPC::getNpcAttackType()
{
	return npcAttackType;
}

TroopsType NPC::getNpcTroopsType()
{
	return troopsType;
}

//npc的攻击效果
int NPC::getNpcAttackPenalty()
{
	return attackPenalty;
}

void NPC::stopAll()
{
	stopAllActions();
	getScheduler()->unscheduleAllForTarget(this);
	npcRole->stopAllActions();
}

Sprite* NPC::getSprite()
{
	return npcRole;
}
int NPC::getSkillId()
{
	return skillId;
}


void NPC::playBlood()
{
	string imgPath = "fightImg/blood.plist";
	auto animation = INSTANCE(AnimationUtils)->getCommonAnimation(imgPath,"blood",0.07f);
	auto blood = Sprite::create();
	auto action = Sequence::create(Animate::create(animation), CallFuncN::create(CC_CALLBACK_0(Sprite::removeFromParent,blood)),nullptr);
	blood->runAction(action);
	addChild(blood);
	blood->setPosition(Vec2(0,100));
}

void NPC::startAttack(float dt)
{
	getScheduler()->unschedule(CC_SCHEDULE_SELECTOR(NPC::startAttack),this);
	INSTANCE(FightManager)->npcAttack(this);
}
void NPC::attackComplete()
{
	playWalk();
}
//被击后反击
void NPC::playAttackBack()
{
	npcRole->stopAllActions();
	auto animate = getAnimate(RoleStatusAttack);
	auto action = Sequence::create(animate,CallFunc::create(CC_CALLBACK_0(NPC::attackBackComplete,this)),nullptr);
	npcRole->runAction(action);
	getScheduler()->schedule(CC_SCHEDULE_SELECTOR(NPC::startAttackBack),this,0.3f,false);
}
void NPC::attackBackComplete()
{
	playWalk();
}
void NPC::startAttackBack(float dt)
{
	getScheduler()->unschedule(CC_SCHEDULE_SELECTOR(NPC::startAttackBack),this);
	INSTANCE(FightManager)->npcAttack(this);
}
//被击后逃跑
void NPC::runAway(bool speedUp)
{
	getScheduler()->unschedule(CC_SCHEDULE_SELECTOR(NPC::runAwayComplete),this);
	if (speedUp)
	{
		//加速换线逃跑
		runAwayStatus = RunAwayStatus_speedUp;
		playWalkAnimate(true);
	}
	else
	{
		//减速不换线
		runAwayStatus = RunAwayStatus_speedDown;
		playWalkAnimate();
	}

	getScheduler()->schedule(CC_SCHEDULE_SELECTOR(NPC::runAwayComplete),this,2 + INSTANCE(GameUtils)->getRandom(2),false);
}
void NPC::runAwayComplete(float dt)
{
	getScheduler()->unschedule(CC_SCHEDULE_SELECTOR(NPC::runAwayComplete),this);
	if (!isDead)
	{
		runAwayStatus = RunAwayStatus_none;
		playWalkAnimate();
	}
}


int NPC::getNpcPositionY()
{
	float positionY = getPositionY();
	if (positionY == -250.0f || positionY == -190.0f || positionY == -130.0f || positionY == -70.0f || positionY == -10.0f)
	{
		return positionY;
	}
	else
	{
		positionY = -(int((-10 - positionY)/60))*60-10;
		return positionY;
	}
}

void NPC::setAttackableHandler(float dt)
{
	getScheduler()->unschedule(CC_SCHEDULE_SELECTOR(NPC::setAttackableHandler),this);
	attackable = true;
}






