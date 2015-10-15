#include "UserData.h"
#include "BaseDataManager.h"
#include "SceneRule.h"

bool UserData::init()
{
	reloadData();
	role = nullptr;
	return true;
}

//判断是否有存档
bool UserData::isHaveSaveFile()
{
	if(!UserDefault::getInstance()->getBoolForKey("isHaveSaveFileXml"))
	{
		UserDefault::getInstance()->setBoolForKey("isHaveSaveFileXml",true);
		UserDefault::getInstance()->flush();
		return false;
	}
	return true;
}
//读取存档
void UserData::reloadData()
{
	//打印保存的位置
	log("xxxxxxxxxxxx,%s",FileUtils::getInstance()->getWritablePath().c_str());
	if (!isHaveSaveFile())
	{
		UserDefault::getInstance()->setIntegerForKey("Gold",0);
		UserDefault::getInstance()->setIntegerForKey("Intergral",0);
		UserDefault::getInstance()->setIntegerForKey("KillBossNum",0);
		UserDefault::getInstance()->setIntegerForKey("TotleCost",0);
		UserDefault::getInstance()->setIntegerForKey("TotleGain",0);
		UserDefault::getInstance()->setIntegerForKey("TitleLevel",1);
		UserDefault::getInstance()->setIntegerForKey("UpgradeIntegral",10);
		UserDefault::getInstance()->setIntegerForKey("LastReceiveLoginRewardTime",100);
		UserDefault::getInstance()->setIntegerForKey("LastReceiveOnlineRewardTime",100);
		UserDefault::getInstance()->setIntegerForKey("ContinuousLoginDay",1);
		UserDefault::getInstance()->setIntegerForKey("SkillNum",0);
		UserDefault::getInstance()->setIntegerForKey("Vip",0);
		UserDefault::getInstance()->setStringForKey("Roles","20001_20002_20003");
		UserDefault::getInstance()->setStringForKey("ChapterStatus","0");
		UserDefault::getInstance()->setIntegerForKey("WheelTimes",5);
		UserDefault::getInstance()->setIntegerForKey("FinishChapterTimes",1);//1~20
		UserDefault::getInstance()->setIntegerForKey("PotGold",1000);
		UserDefault::getInstance()->setIntegerForKey("ReceiveOnlineRewardTimes",3);
		UserDefault::getInstance()->setIntegerForKey("TaskCount",6);
		UserDefault::getInstance()->setIntegerForKey("ReceiveTaskTime",2);
		UserDefault::getInstance()->setIntegerForKey("Anger",1);
		UserDefault::getInstance()->setIntegerForKey("LoginCount",1);
	}
	currentMoney =					UserDefault::getInstance()->getIntegerForKey("Gold");
	currentIntegral =				UserDefault::getInstance()->getIntegerForKey("Intergral");
	killBossNum =					UserDefault::getInstance()->getIntegerForKey("KillBossNum");
	totleCost =						UserDefault::getInstance()->getIntegerForKey("TotleCost");
	totleGain =						UserDefault::getInstance()->getIntegerForKey("TotleGain");
	currentTitleLevel =				UserDefault::getInstance()->getIntegerForKey("TitleLevel");
	currentUpgradeIntegral =		UserDefault::getInstance()->getIntegerForKey("UpgradeIntegral");
	lastReceiveLoginRewardTime =	UserDefault::getInstance()->getIntegerForKey("LastReceiveLoginRewardTime");
	lastReceiveOnlineRewardTime =	UserDefault::getInstance()->getIntegerForKey("LastReceiveOnlineRewardTime");
	currentContinuousDay =			UserDefault::getInstance()->getIntegerForKey("ContinuousLoginDay");
	skillNum =						UserDefault::getInstance()->getIntegerForKey("SkillNum");
	vipLevel =						UserDefault::getInstance()->getIntegerForKey("Vip");
	roles =							UserDefault::getInstance()->getStringForKey("Roles");
	chapterStatus =					UserDefault::getInstance()->getStringForKey("ChapterStatus");
	if (chapterStatus == "0")
	{
		chapterStatus = "";
	}
	wheelTimes =					UserDefault::getInstance()->getIntegerForKey("WheelTimes");
	finishChapterTimes =			UserDefault::getInstance()->getIntegerForKey("FinishChapterTimes");
	currentPotGold =				UserDefault::getInstance()->getIntegerForKey("PotGold");
	receiveOnlineRewardTimes =		UserDefault::getInstance()->getIntegerForKey("ReceiveOnlineRewardTimes");
	taskCount =						UserDefault::getInstance()->getIntegerForKey("TaskCount");
	receiveTaskTime =				UserDefault::getInstance()->getIntegerForKey("ReceiveTaskTime");
	anger =							UserDefault::getInstance()->getIntegerForKey("Anger");
	loginCount =					UserDefault::getInstance()->getIntegerForKey("LoginCount");
}

void UserData::setCurrentMoney(int money)
{
	currentMoney = money;
	UserDefault::getInstance()->setIntegerForKey("Gold",money);
}
void UserData::addCurrentMoney(int money)
{
	currentMoney += money;
	UserDefault::getInstance()->setIntegerForKey("Gold",money);
}
void UserData::costCurrentMoney(int money)
{
	currentMoney -= money;
	if (currentMoney < 0)
	{
		currentMoney = 0;
	}
	UserDefault::getInstance()->setIntegerForKey("Gold",money);
}
int UserData::getCurrentMoney()
{
	return currentMoney;
}


void UserData::setCurrentIntegral(int integral)
{
	currentIntegral = integral;
	UserDefault::getInstance()->setIntegerForKey("Intergral",integral);
}
int UserData::getCurrentIntegral()
{
	return currentIntegral;
}

void UserData::setKillBossNum(int num)
{
	killBossNum = num;
	UserDefault::getInstance()->setIntegerForKey("KillBossNum",num);
}
int UserData::getKillBossNum()
{
	return killBossNum;
}

void UserData::setTotleCost(int cost)
{
	totleCost = cost;
	UserDefault::getInstance()->setIntegerForKey("TotolCost",cost);
}
int UserData::getTotleCost()
{
	return totleCost;
}

void UserData::setTotleGain(int gain)
{
	totleGain = gain;
	UserDefault::getInstance()->setIntegerForKey("TotleGain",gain);
}
int UserData::getTotleGain()
{
	return totleGain;
}

void UserData::setTitleLevel(int titleLevel)
{
	currentTitleLevel = titleLevel;
	UserDefault::getInstance()->setIntegerForKey("TitleLevel",titleLevel);
}
int UserData::getTitleLevel()
{
	return currentTitleLevel;
}

void UserData::setCurrentUpgradeIntegral(int upgradeIntegral)
{
	currentUpgradeIntegral = upgradeIntegral;
	UserDefault::getInstance()->setIntegerForKey("UpgradeIntegral",upgradeIntegral);
}
int UserData::getCurrentUpgradeIntegral()
{
	return currentUpgradeIntegral;
}

void UserData::setLastReceiveLoginRewardTime(int64_t time)
{
	lastReceiveLoginRewardTime = time;
	UserDefault::getInstance()->setIntegerForKey("LastReceiveLoginRewardTime",time);
}
int64_t UserData::getLastReceiveLoginRewardTime()
{
	return lastReceiveLoginRewardTime;
}

void UserData::setLastReceiveOnlineRewardTime(int64_t time)
{
	lastReceiveOnlineRewardTime = time;
	UserDefault::getInstance()->setIntegerForKey("LastReceiveOnlineRewardTime",time);
}
int64_t UserData::getLastReceiveOnlineRewardTime()
{
	return lastReceiveOnlineRewardTime;
}

void UserData::setContinuousDay(int dayNum)
{
	currentContinuousDay = dayNum;
	UserDefault::getInstance()->setIntegerForKey("ContinuousLoginDay",dayNum);
}
int UserData::getContinuousDay()
{
	return currentContinuousDay;
}

void UserData::setSkillNum(int skillNum)
{
	this->skillNum = skillNum;
	UserDefault::getInstance()->setIntegerForKey("SkillNum",skillNum);
}
int UserData::getSkillNum()
{
	return skillNum;
}

void UserData::setVipLevel(int vipLevel)
{
	this->vipLevel = vipLevel;
	UserDefault::getInstance()->setIntegerForKey("vip",vipLevel);
}
int UserData::getVipLevel()
{
	return vipLevel;
}

void UserData::setRoles(string roles)
{
	this->roles = roles;
	UserDefault::getInstance()->setStringForKey("Roles",roles);
}
string UserData::getRoles()
{
	return this->roles;
}
void UserData::addRole(int roleId)
{
	roles.append("_"+Value(roleId).asString());
	setRoles(roles);
}

void UserData::setChapterStatus(int chapterId,int bossId)
{
	//INSTANCE(BaseDataManager)->split(chapterStatus,"_");
	vector<int> sceneVec = INSTANCE(SceneRule)->getAllSceneId();
	//vector<int> bossIdVec = INSTANCE(SceneRule)->getSceneBossId(chapterId);
	map<int, vector<int> > tempM;
	for (auto& sId : sceneVec)
	{
		tempM[sId] = INSTANCE(SceneRule)->getSceneBossId(sId);
	}
	//返回指向关键字为chapterid的元素，如果chapterid不在容器中，则返回尾后迭代器 end()
	map<int, vector<int> >::iterator it = tempM.find(chapterId);
	if (it != tempM.end())
	{
		it->second[0] = bossId;
	}
	else
	{
		vector<int> t;
		t.push_back(bossId);
		tempM[chapterId] = t;
	}
	//再将map转换成string
	string result("");
	for (map<int,vector<int>>::iterator it = tempM.begin();it != tempM.end();it++)
	{
		string resultT("");
		vector<int> t = it->second;
		for (auto& id : t)
		{
			resultT.append(Value(id).asString());
		}
		if (it == tempM.begin())
		{
			result.append(resultT);
		}
		else
		{
			result.append("|"+resultT);
		}
	}
	//他们的格式是：
	//BossID1_BossID2_BossID3|BossID1_BossID2_BossID3|BossID1_BossID2_BossID3
	chapterStatus = result;
}
int UserData::getChapterStatus(int chapterId)
{
	map<int,vector<string>> result;
	vector<string> chapterIds = INSTANCE(BaseDataManager)->split(chapterStatus,"|");
	for (int i=0;i<chapterIds.size();i++)
	{
		vector<string> bossIds = INSTANCE(BaseDataManager)->split(chapterIds[i],"_");
		result[i] = bossIds;
	}
	map<int, vector<string> >::iterator it = result.find(chapterId);
	if (it != result.end())
	{
		return Value(it->second[0]).asInt();
	}
	return 0;
}

void UserData::setWheelTimes(int times)
{
	wheelTimes = times;
	UserDefault::getInstance()->setIntegerForKey("WheelTimes",times);
}
void UserData::addWheelTimes(int times)
{
	wheelTimes += times;
	UserDefault::getInstance()->setIntegerForKey("WheelTimes",wheelTimes);
}
int UserData::getWheelTimes()
{
	return wheelTimes;
}

void UserData::setFinishChapterTimes(int times)
{
	finishChapterTimes = times;
	UserDefault::getInstance()->setIntegerForKey("FinishChapterTimes",times);
}
void UserData::addFinishChapterTimes(int times)
{
	finishChapterTimes += times;
	UserDefault::getInstance()->setIntegerForKey("FinishChapterTimes",finishChapterTimes);
}
int UserData::getFinishChapterTimes()
{
	return finishChapterTimes;
}

void UserData::setPotGold(int gold)
{
	currentPotGold = gold;
	UserDefault::getInstance()->setIntegerForKey("PotGold",gold);
}
void UserData::addPotGold(int gold)
{
	currentPotGold += gold;
	UserDefault::getInstance()->setIntegerForKey("PotGold",currentPotGold);
}
int UserData::getPotGold()
{
	return currentPotGold;
}
int UserData::getPotWinning()
{
	return currentPotGold * 0.5f;
}

void UserData::setReceiveOnlineRewardTimes(int times)
{
	receiveOnlineRewardTimes = times;
	UserDefault::getInstance()->setIntegerForKey("ReceiveOnlineRewardTimes",times);
}
void UserData::addReceiveOnlineRewardTimes(int times)
{
	receiveOnlineRewardTimes += times;
	UserDefault::getInstance()->setIntegerForKey("ReceiveOnlineRewardTimes",receiveOnlineRewardTimes);
}
int UserData::getReceiveOnlineRewardTimes()
{
	return receiveOnlineRewardTimes;
}

void UserData::setTaskCount(int count)
{
	taskCount = count;
	UserDefault::getInstance()->setIntegerForKey("TaskCount",count);
}
void UserData::addTaskCount(int count)
{
	taskCount += count;
	UserDefault::getInstance()->setIntegerForKey("TaskCount",taskCount);
}
int UserData::getTaskCount()
{
	return taskCount;
}

void UserData::setReceiveTaskTime(int64_t time)
{
	receiveTaskTime = time;
	UserDefault::getInstance()->setIntegerForKey("ReceiveTaskTime",time);
}
int64_t UserData::getReceiveTaskTime()
{
	return receiveTaskTime;
}

void UserData::setAnger(int anger)
{
	this->anger = anger;
	UserDefault::getInstance()->setIntegerForKey("Anger",anger);
}
int UserData::getAnger()
{
	return this->anger;
}

void UserData::addLoginCount(int count)
{
	loginCount = count;
	UserDefault::getInstance()->setIntegerForKey("LoginCount",count);
}
int UserData::getLoginCount()
{
	return loginCount;
}
