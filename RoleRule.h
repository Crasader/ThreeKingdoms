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

    //获取角色技能特效锚点
    Vec2 getRoleSkillEffectAnchorPoint(int roleId);
    //获取角色普攻特效锚点
    Vec2 getRoleAttackEffectAnchorPoint(int roleId);
    //获取角色攻击点帧数
    int getRoleAttackFrameNum(int roleId);
    //获取角色技能攻击点帧数
    int getRoleSkillFrameNum(int roleId);
    //获取角色最大攻击
    int getRoleMaxAttack(int roleId);
    //获取角色最低攻击
    int getRoleMinAttack(int roleId);
    //获取角色速度
    int getRoleSpeed(int roleId);
    //获取角色攻击速度
    float getRoleAttackSpeed(int roleId);
    
    //角色描述
    string getRoleDesc(int roleId);
    
    //获取角色攻击范围
    Size getRoleAttackSize(int roleId);
    //获取角色受击范围
    Size getRoleHurtSize(int roleId);
    
    
    //vip等级限制
    int getRoleVip(int roleId);
    //元宝购买费用
    int getRoleCost(int roleId);
    //排序
    int getRoleSequence(int roleId);
    //是否拥有
    bool ownRole(int roleId);
    //获取免费角色
    vector<int> getFreeRolesVector();
    
    string getFreeRoles();
public:

	vector<int> getAllRoleId();
private:
	string getRoleAttribute(int roleId,const string& attributeName);
	ValueMap getRoleDic(int roleId);

	ValueMap mainDic;
	ValueMap lastSubDic;
};
