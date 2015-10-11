#include "BaseRole.h"
#include "tools/AnimationUtils.h"
#include "JoyStickLayer.h"
#include "SkillRule.h"
#include "FightManager.h"

BaseRole* BaseRole::create(int roleId)
{
	auto role = new BaseRole(roleId);
	if (role && role->init())
	{
		role->autorelease();
		return role;
	}
	else
	{
		delete role;
		role = nullptr;
		return nullptr;
	}
}
BaseRole::BaseRole(int roleId)
{
	this->roleId = roleId;
	currentRoleDirection = RoleDirection_right;
	currentRoleStatus = RoleStatusNone;
	speedX = INSTANCE(RoleRule)->getRoleSpeed(roleId) * 1.0f;
	speedY = speedX * 2 / 3;
	attackSpeed = INSTANCE(RoleRule)->getRoleAttackSpeed(roleId) * 1.0f;
	speedCoefficient = 0.6f;
	attackCompleted = true;
}

BaseRole::~BaseRole()
{

}

void BaseRole::onEnter()
{
	Node::onEnter();
	listener = EventListenerCustom::create(JoyStick_status,[=](EventCustom* event){
		//Note:event->getUserData()返回的void*类型,不能转换到string
		string buff(static_cast<char*>(event->getUserData()));
		if (currentRoleStatus == RoleStatusHurt)
		{
			return;
		}
		if (buff == JoyStick_up)
		{
			setRolePosition(Vec2(0,speedY));
		}
		else if (buff == JoyStick_down)
		{
			setRolePosition(Vec2(0,-speedY));
		}
		else if (buff == JoyStick_right)
		{
			setRolePosition(Vec2(speedX,0));
		}
		else if (buff == JoyStick_left)
		{
			setRolePosition(Vec2(-speedX,0));
		}
		else if (buff == JoyStick_right_down)
		{
			setRolePosition(Vec2(speedX * speedCoefficient, -speedY * speedCoefficient));
		}
		else if (buff == JoyStick_right_up)
		{
			setRolePosition(Vec2(speedX* speedCoefficient,speedY * speedCoefficient));
		}
		else if (buff == JoyStick_left_down)
		{
			setRolePosition(Vec2(-speedX * speedCoefficient,-speedY * speedCoefficient));
		}
		else if (buff == JoyStick_left_up)
		{
			setRolePosition(Vec2(-speedX * speedCoefficient,speedY * speedCoefficient));
		}
		else if (buff == JoyStick_skill)
		{
			playSkill();
		}
		else if (buff == JoyStick_attack)
		{
			playAttack();
		}
		else if (buff == JoyStick_none)
		{
			if (!isAttacking() && currentRoleStatus != RoleStatusSkill)
			{
				playStand();
			}
		}
	});
	_eventDispatcher->addEventListenerWithFixedPriority(listener,1);
}
void BaseRole::onExit()
{
	Node::onExit();
	_eventDispatcher->removeEventListener(listener);
}

bool BaseRole::init()
{
	if (!Node::init())
	{
		return false;
	}
	//evenStrokes = INSTANCE(TitleRule);
	evenStrokes = 5;
	initRole();
	return true;
}


void BaseRole::initRole()
{
	string img = INSTANCE(RoleRule)->getRoleImgPath(roleId);
	img.append(INSTANCE(RoleRule)->getRoleFrameNameByRoleId(roleId,RoleStatusStand));
	img.append(".plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(img);
	img = INSTANCE(RoleRule)->getRoleFirstFrameNameByRoleId(roleId,RoleStatusStand);
	role = Sprite::createWithSpriteFrameName(img);
	addChild(role);
	role->setAnchorPoint(INSTANCE(RoleRule)->getRoleAnchorPoint(roleId));

	playStand();

	//人物脚下的阴影
	auto shadow = Sprite::create("fightImg/role_shadow.png");
	role->addChild(shadow,-1);
	shadow->setPosition(role->getAnchorPointInPoints());

	//人物头上的箭头
	auto arrow = Sprite::create();
	auto animation = INSTANCE(AnimationUtils)->getCommonAnimation("fightImg/roleArrow.plist","roleArrow");
	auto action = RepeatForever::create(Animate::create(animation));
	arrow->runAction(action);
	addChild(arrow);
	arrow->setPosition(Vec2(0,250));
}

void BaseRole::playStand()
{
	if (currentRoleStatus == RoleStatusStand)
	{
		return;
	}
	currentRoleStatus = RoleStatusStand;

	role->stopAllActions();
	auto action = RepeatForever::create(getAnimate(RoleStatusStand));
	role->runAction(action);
}

void BaseRole::playRun()
{
	if (currentRoleStatus == RoleStatusRun)
	{
		return;
	}
	currentRoleStatus = RoleStatusRun;

	role->stopAllActions();
	auto action = RepeatForever::create(getAnimate(RoleStatusRun,0.07f));
	role->runAction(action);
}

void BaseRole::playSkill()
{
	if (currentRoleStatus == RoleStatusSkill || isAttacking())
	{
		return;
	}
	currentRoleStatus = RoleStatusSkill;

	role->stopAllActions();

	auto action = Sequence::create(getAnimate(RoleStatusSkill),CallFuncN::create(CC_CALLBACK_0(BaseRole::skillComplete,this)),nullptr);
	role->runAction(action);

	//Director::getInstance()->getScheduler()->schedule(CC_SCHEDULE_SELECTOR(BaseRole::startSkill),this,1.0f,false);
}

void BaseRole::startSkill(float dt)
{
	//INSTANCE(FightManager)->roleSkill();
}

void BaseRole::skillComplete()
{
	playStand();
}

void BaseRole::playAttack()
{
	RoleStatus status = currentRoleStatus;
	//evenStrokes = INSTANCE(FightManager)->getEvenStrokes();
	evenStrokes = 5;

	if (currentRoleStatus == RoleStatusSkill)
	{
		return;
	}

	if (isAttacking())
	{
		if (attackCompleted)
		{
			if (currentRoleStatus == RoleStatusAttack_1)
			{
				currentRoleStatus = RoleStatusAttack_2;
			}
			else if (currentRoleStatus == RoleStatusAttack_2)
			{
				currentRoleStatus = RoleStatusAttack_3;
			}
			else if (currentRoleStatus == RoleStatusAttack_3)
			{
				currentRoleStatus = RoleStatusAttack_4;
			}
			else if (currentRoleStatus == RoleStatusAttack_4)
			{
				currentRoleStatus = RoleStatusAttack_5;
			}
			else if (currentRoleStatus == RoleStatusAttack_5)
			{
				return;
			}
		}
		else
		{
			return;
		}
	}
	else
	{
		currentRoleStatus = RoleStatusAttack_1;
	}

	INSTANCE(FightManager)->setAttackMultiple(getAttackMultiple());
	
	attackCompleted = false;
	role->stopAllActions();

	auto animate = getAnimate(currentRoleStatus, attackSpeed);
	auto action = Sequence::create(animate,CallFuncN::create(CC_CALLBACK_0(BaseRole::attackComplete,this)),nullptr);
	role->runAction(action);

	Director::getInstance()->getScheduler()->schedule(CC_SCHEDULE_SELECTOR(BaseRole::startAttack),this,animate->getDuration()/2.0f,false);
	Director::getInstance()->getScheduler()->schedule(CC_SCHEDULE_SELECTOR(BaseRole::allowNextAttack),this,animate->getDuration() - 0.1f,false);
}

void BaseRole::startAttack(float dt)
{
	//播放音效
	//取消定时器
	this->getScheduler()->unschedule(CC_SCHEDULE_SELECTOR(BaseRole::startAttack),this);
	//角色攻击后的一些效果，敌人受伤，加金币等
	INSTANCE(FightManager)->roleAttack(getAttackMultiple());
}
void BaseRole::allowNextAttack(float dt)
{
	this->getScheduler()->unschedule(CC_SCHEDULE_SELECTOR(BaseRole::allowNextAttack),this);
	if (evenStrokes == 1 && currentRoleStatus == RoleStatusAttack_1)
	{
		attackCompleted = false;
	}
	else if (evenStrokes == 2 && currentRoleStatus == RoleStatusAttack_2)
	{
		attackCompleted = false;
	}
	else if (evenStrokes == 3 && currentRoleStatus == RoleStatusAttack_3)
	{
		attackCompleted = false;
	}
	else if (evenStrokes == 4 && currentRoleStatus == RoleStatusAttack_4)
	{
		attackCompleted = false;
	}
	else if (evenStrokes == 5 && currentRoleStatus == RoleStatusAttack_5)
	{
		attackCompleted = false;
	}
	else
	{
		attackCompleted = true;
	}
}

int BaseRole::getAttackMultiple()
{
	switch (currentRoleStatus)
	{
	case RoleStatusAttack_1:
		return 1;
		break;
	case RoleStatusAttack_2:
		return 2;
		break;
	case RoleStatusAttack_3:
		return 3;
		break;
	case RoleStatusAttack_4:
		return 4;
		break;
	case RoleStatusAttack_5:
		return 5;
		break;
	default:
		return 0;
		break;
	}
}

void BaseRole::attackComplete()
{
	playStand();
}

Animate* BaseRole::getAnimate(RoleStatus status,float duration)
{
	string img = INSTANCE(RoleRule)->getRoleFrameNameByRoleId(roleId, status);

	auto animation = INSTANCE(AnimationUtils)->getModelAnimation(
		INSTANCE(RoleRule)->getRoleModelId(roleId),
		img,img,duration);
	auto animate = Animate::create(animation);
	return animate;
}


bool BaseRole::isAttacking()
{
	if (currentRoleStatus == RoleStatusAttack_1 ||
		currentRoleStatus == RoleStatusAttack_2 ||
		currentRoleStatus == RoleStatusAttack_3 ||
		currentRoleStatus == RoleStatusAttack_4 ||
		currentRoleStatus == RoleStatusAttack_5 )
	{
		return true;
	}
	return false;
}

void BaseRole::setRolePosition(Vec2 p)
{
	//如果角色正在攻击中，或者释放技能中，直接返回
	if (isAttacking() || currentRoleStatus == RoleStatusSkill)
	{
		return;
	}
	if (p.x < 0)
	{
		currentRoleDirection = RoleDirection_left;
		role->setFlippedX(true);
	}
	else
	{
		currentRoleDirection = RoleDirection_right;
		role->setFlippedX(false);
	}

	auto nP = getPosition() + p;
	auto winSize = Director::getInstance()->getWinSize();

	float _x;
	float _y;
	if (nP.y > 20 || nP.y < -280)
	{
		_y = getPositionY();
	}
	else
	{
		_y = nP.y;
	}

	if (nP.x >= winSize.width/2 || nP.x <= -winSize.width/2)
	{
		_x = getPositionX();
	}
	else
	{
		_x = nP.x;
	}
	setPosition(Vec2(_x,_y));

	playRun();
}

//roleid-->skillId-->skillCost
int BaseRole::getSkillCost()
{
	return INSTANCE(SkillRule)->getSkillCost(INSTANCE(RoleRule)->getRoleSkillId(roleId));
}

//获取角色方向
RoleDirection BaseRole::getRoleDirection()
{
	return currentRoleDirection;
}

//获取角色攻击区域和受伤区域
Rect BaseRole::getAttackRect()
{
	//根据人物位置，和区域大小确定攻击区域位置
	auto size = INSTANCE(RoleRule)->getRoleAttackSize(roleId);
	if (currentRoleDirection == RoleDirection_left)
	{
		return Rect(getPositionX() - size.width, getPositionY() - size.height/2,size.width, size.height);
	}
	else
	{
		return Rect(getPositionX(), getPositionY() - size.height/2,size.width, size.height);
	}
}
Rect BaseRole::getHurtRect()
{
	//受伤区域就是整个人物了，坐标应该在人物左下角
	auto size = INSTANCE(RoleRule)->getRoleHurtSize(roleId);
	return Rect(getPositionX() - size.width/2, getPositionY() - size.height/2, size.width, size.height);
}
