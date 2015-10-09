#include "BaseRole.h"

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
}
