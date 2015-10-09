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

//���ﳯ��
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

	//��ȡ��ɫͼƬ��
	string getRoleFrameNameByRoleId(int roleId,RoleStatus status, bool containPng = false);
	//��ȡ��ɫվ����һ֡
	string getRoleFirstFrameNameByRoleId(int roleId,RoleStatus status);
	//��ȡ��ɫģ��ID
	int getRoleModelId(int roleId);
	//��ȡ��ɫê��
	Vec2 getRoleAnchorPoint(int roleId);
	//��ȡ��ɫ��
	string getRoleName(int roleId);
	//��ȡ��ɫͼƬ��Դ·��
	string getRoleImgPath(int roleId);
	//��ȡ��ɫ����id
	int getRoleSkillId(int roleId);
public:

	vector<int> getAllRoleId();
private:
	string getRoleAttribute(int roleId,const string& attributeName);
	ValueMap getRoleDic(int roleId);

	ValueMap mainDic;
	ValueMap lastSubDic;
};
