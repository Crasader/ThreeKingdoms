#pragma once

#include "cocos2d.h"
#include "tools/GameCommon.h"
#include "BaseRole.h"

USING_NS_CC;
using namespace std;

class UserData : public Ref
{
public:
	CLASS_INSTANCE(UserData);
	bool init();

	//��UserDefault�������ݿ�浵
	//�ж��Ƿ��д浵
	bool isHaveSaveFile();
	//��ȡ�浵
	void reloadData();
public:

    void setCurrentMoney(int money);
    void addCurrentMoney(int money);
    void costCurrentMoney(int money);
    int getCurrentMoney();
    
    void setCurrentIntegral(int integral);
    int getCurrentIntegral();
    
    void setKillBossNum(int num);
    int getKillBossNum();
    
    void setTotleCost(int cost);
    int getTotleCost();
    
    void setTotleGain(int gain);
    int getTotleGain();
    
    void setTitleLevel(int titleLevel);
    int getTitleLevel();
    
    void setCurrentUpgradeIntegral(int upgradeIntegral);
    int getCurrentUpgradeIntegral();
    
    void setLastReceiveLoginRewardTime(int64_t time);
    int64_t getLastReceiveLoginRewardTime();
    
    void setLastReceiveOnlineRewardTime(int64_t time);
    int64_t getLastReceiveOnlineRewardTime();
    
    void setContinuousDay(int dayNum);
    int getContinuousDay();
    
    void setSkillNum(int skillNum);
    int getSkillNum();
    
    void setVipLevel(int vipLevel);
    int getVipLevel();
    
    void setRoles(string roles);
    string getRoles();
    void addRole(int roleId);
    
    void setChapterStatus(int chapterId,int bossId);
    int getChapterStatus(int chapterId);
    
    void setWheelTimes(int times);
    void addWheelTimes(int times);
    int getWheelTimes();
    
    void setFinishChapterTimes(int times);
    void addFinishChapterTimes(int times);
    int getFinishChapterTimes();
    
    void setPotGold(int gold);
    void addPotGold(int gold);
    int getPotGold();
    int getPotWinning();
    
    void setReceiveOnlineRewardTimes(int times);
    void addReceiveOnlineRewardTimes(int times);
    int getReceiveOnlineRewardTimes();
    
    void setTaskCount(int count);
    void addTaskCount(int count);
    int getTaskCount();
    
    void setReceiveTaskTime(int64_t time);
    int64_t getReceiveTaskTime();
    
    void setAnger(int anger);
    int getAnger();
    
    void addLoginCount(int count);
    int getLoginCount();

	//��ǰrole id
	CC_SYNTHESIZE(int,currentRoleId,CurrentRoleId);
	//��ǰ����id
	CC_SYNTHESIZE(int,currentSceneId,CurrentSceneId);
	//��ǰ��ɫ
	CC_SYNTHESIZE(BaseRole*, role,Role);
private:
	//ӵ�еĽ�ɫId
	string roles;
    //��ǰԪ��
    int currentMoney;
    //��ǰ����
    int currentIntegral;
    //��ɱboss����
    int killBossNum;
    //Ԫ��������(�״���Ϸʱ�ۼ�)
    int totleCost;
    //Ԫ���ܻ�ȡ(�״���Ϸʱ�ۼ�)
    int totleGain;

    //��ǰͷ�εȼ�
    int currentTitleLevel;
    //��ǰ��������
    int currentUpgradeIntegral;
    //�ϴ���ȡ��¼����ʱ��
    int64_t lastReceiveLoginRewardTime;
    //�ϴ���ȡ���߽���
    int64_t lastReceiveOnlineRewardTime;
    //��ǰ������½����
    int currentContinuousDay;
    //�����ͷŴ���
    int skillNum;
    
    //vip�ȼ�
    int vipLevel;
    //�ؿ�״̬
    string chapterStatus;
    //ת�̴���
    int wheelTimes;
    //ͨ�ش���
    int finishChapterTimes;
    //��ǰ�ʳؽ���
    int currentPotGold;
    
    //��ǰ��ȡ���߽�������
    int receiveOnlineRewardTimes;
    
    //ÿ���������
    int taskCount;
    
    int anger;
    
    int64_t receiveTaskTime;
    
    int loginCount;
    
    //int chargeAmount;
    
    //vector<string> productIds;

};