#pragma once

#include "cocos2d.h"
#include "tools/GameCommon.h"

USING_NS_CC;
using namespace std;

class SceneRule : public Ref
{
public:
	CLASS_INSTANCE(SceneRule);
	bool init();
public:
	//获取所有的场景ID
	vector<int> getAllSceneId();
	//获取场景图片ID
	int getSceneImgId(int sceneId);

	//获取所有npc ID
	vector<int> getAllNpcId(int sceneId);
	//获取Boos id
	vector<int> getSceneBossId(int sceneId);
	//获取 技能兵id
	vector<int> getSkillNpcId(int sceneId);
	//获取士兵id
	vector<int> getNpcId(int sceneId);
	//将string转换成Vector<int>
	vector<int> SceneRule::stringToVectorInt(string str);

    //获取场景名
    string getSceneName(int sceneId);
    //获取场景描述
    string getSceneDesc(int sceneId);
    //获取场景所需等级
    int getSceneNeedLevel(int sceneId);
    //获取场景所需vip
    int getSceneNeedVip(int sceneId);
    //获取场景阵型Id
    string getSceneFormation(int sceneId);
    
    //获取boss出现数量
    int getSceneBossCount(int sceneId);
    
    //获取士兵概率
    vector<float> getNpcProbabilitys(int sceneId);
    
    //获取技能兵概率
    float getSkillNpcProbability(int sceneId);
    
    //获取得分区间
    vector<int> getScoreVector(int sceneId,int type);
    //获取影响系数
    float getScoreCoefficient(int sceneId);
    //获取得分周期影响系数加成
    float getCycleScoreCoefficientAddition(int sceneId);
    //获取攻击累计加成影响系数
    float getAttackScoreCoefficientAddition(int sceneId);
    
    //获取场景阵型
    vector<vector<int> > getSceneFormationVector(int sceneId);
    
    //场景倍率
    int getSceneMagnification(int sceneId);
    //出分周期命中率
    float getSceneScoreHitRate(int sceneId);
    //吃分周期命中率
    float getSceneLoseHitRate(int sceneId);
    //得分部队命中率
    float getTroopsHitRate(int sceneId);
private:
	ValueMap getSceneDic(int sceneId);
	string getSceneAttribute(int sceneId,const string& attributeName);

	ValueMap mainDic;
	ValueMap lastSubDic;
};
