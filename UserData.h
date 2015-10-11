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

	//用UserDefault代替数据库存档
	//判断是否有存档
	bool isHaveSaveFile();
	//读取存档
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

	//当前role id
	CC_SYNTHESIZE(int,currentRoleId,CurrentRoleId);
	//当前场景id
	CC_SYNTHESIZE(int,currentSceneId,CurrentSceneId);
	//当前角色
	CC_SYNTHESIZE(BaseRole*, role,Role);
private:
	//拥有的角色Id
	string roles;
    //当前元宝
    int currentMoney;
    //当前积分
    int currentIntegral;
    //击杀boss数量
    int killBossNum;
    //元宝总消耗(首次游戏时累计)
    int totleCost;
    //元宝总获取(首次游戏时累计)
    int totleGain;

    //当前头衔等级
    int currentTitleLevel;
    //当前升级积分
    int currentUpgradeIntegral;
    //上次领取登录奖励时间
    int64_t lastReceiveLoginRewardTime;
    //上次领取在线奖励
    int64_t lastReceiveOnlineRewardTime;
    //当前连续登陆天数
    int currentContinuousDay;
    //技能释放次数
    int skillNum;
    
    //vip等级
    int vipLevel;
    //关卡状态
    string chapterStatus;
    //转盘次数
    int wheelTimes;
    //通关次数
    int finishChapterTimes;
    //当前彩池奖金
    int currentPotGold;
    
    //当前领取在线奖励次数
    int receiveOnlineRewardTimes;
    
    //每日任务次数
    int taskCount;
    
    int anger;
    
    int64_t receiveTaskTime;
    
    int loginCount;
    
    //int chargeAmount;
    
    //vector<string> productIds;

};