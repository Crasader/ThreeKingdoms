#include "BaseRole.h"
#include "tools/AnimationUtils.h"

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
}

BaseRole::~BaseRole()
{

}

bool BaseRole::init()
{
	if (!Node::init())
	{
		return false;
	}
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

	role->stopAllActions();
	auto action = RepeatForever::create(getAnimate(RoleStatusStand));
	role->runAction(action);
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
