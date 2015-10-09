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

    //��ȡ��ɫ������Чê��
    Vec2 getRoleSkillEffectAnchorPoint(int roleId);
    //��ȡ��ɫ�չ���Чê��
    Vec2 getRoleAttackEffectAnchorPoint(int roleId);
    //��ȡ��ɫ������֡��
    int getRoleAttackFrameNum(int roleId);
    //��ȡ��ɫ���ܹ�����֡��
    int getRoleSkillFrameNum(int roleId);
    //��ȡ��ɫ��󹥻�
    int getRoleMaxAttack(int roleId);
    //��ȡ��ɫ��͹���
    int getRoleMinAttack(int roleId);
    //��ȡ��ɫ�ٶ�
    int getRoleSpeed(int roleId);
    //��ȡ��ɫ�����ٶ�
    float getRoleAttackSpeed(int roleId);
    
    //��ɫ����
    string getRoleDesc(int roleId);
    
    //��ȡ��ɫ������Χ
    Size getRoleAttackSize(int roleId);
    //��ȡ��ɫ�ܻ���Χ
    Size getRoleHurtSize(int roleId);
    
    
    //vip�ȼ�����
    int getRoleVip(int roleId);
    //Ԫ���������
    int getRoleCost(int roleId);
    //����
    int getRoleSequence(int roleId);
    //�Ƿ�ӵ��
    bool ownRole(int roleId);
    //��ȡ��ѽ�ɫ
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
