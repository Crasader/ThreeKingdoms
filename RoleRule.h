#pragma once

#include "cocos2d.h"
#include "tools/GameCommon.h"

USING_NS_CC;
using namespace std;

enum RoleStatus
{
    RoleStatusNone,
    RoleStatusStand,
    RoleStatusWalk,
    RoleStatusRun,
    RoleStatusAttack,
    RoleStatusAttack_1,
    RoleStatusAttack_2,
    RoleStatusAttack_3,
    RoleStatusAttack_4,
    RoleStatusAttack_5,
    RoleStatusHurt,
    RoleStatusDie,
    RoleStatusSkill,
    RoleStatusAttackEffect,
    RoleStatusSkillEffect,
};

//人物朝向
enum RoleDirection
{
	RoleDirection_left,
	RoleDirection_right,
};

class RoleRule : public Ref
{
public:
	CLASS_INSTANCE(RoleRule);
	bool init();

	//获取角色图片名
	string getRoleFrameNameByRoleId(int roleId,RoleStatus status, bool containPng = false);
	//获取角色站立第一帧
	string getRoleFirstFrameNameByRoleId(int roleId,RoleStatus status);
	//获取角色模型ID
	int getRoleModelId(int roleId);
	//获取角色锚点
	Vec2 getRoleAnchorPoint(int roleId);
	//获取角色名
	string getRoleName(int roleId);
	//获取角色图片资源路径
	string getRoleImgPath(int roleId);
	//获取角色技能id
	int getRoleSkillId(int roleId);
public:

	vector<int> getAllRoleId();
private:
	string getRoleAttribute(int roleId,const string& attributeName);
	ValueMap getRoleDic(int roleId);

	ValueMap mainDic;
	ValueMap lastSubDic;
};
