#include "SceneRule.h"
#include "BaseDataManager.h"

bool SceneRule::init()
{
	return true;
}

//获取所有的场景ID
vector<int> SceneRule::getAllSceneId()
{
	//if (mainDic.empty())
	//{
	//	//mainDic = INSTANCE(BaseDataManager)->getXml(ScenesXml);
	//	mainDic = INSTANCE(BaseDataManager)->getXml(RoleXml);
	//}

	//vector<int> result;
	//for (const auto& key : INSTANCE(BaseDataManager)->getXml(RoleXml))
	//{
	//	result.push_back(Value(key.first).asInt());
	//}
	//for (auto& i : result)
	//{
	//	log("scenesXml:%d",i);
	//}
	//return result;
	vector<int> result;
	for (const auto& key : INSTANCE(BaseDataManager)->getXml(ScenesXml))
	{
		result.push_back(Value(key.first).asInt());
	}
	for (auto& i : result)
	{
		log("scenesXml:%d",i);
	}
	return result;

}

//获取场景图片ID
int SceneRule::getSceneImgId(int sceneId)
{
	return Value(getSceneAttribute(sceneId,"image")).asInt();
}

//获取所有npc ID
vector<int> SceneRule::getAllNpcId(int sceneId)
{
	vector<int> result;
	vector<int> v1 = getSceneBossId(sceneId);
	vector<int> v2 = getSkillNpcId(sceneId);
	vector<int> v3 = getNpcId(sceneId);
	result.insert(result.end(),v1.begin(),v1.end());
	result.insert(result.end(),v2.begin(),v2.end());
	result.insert(result.end(),v3.begin(),v3.end());
	return result;
}

//获取Boos id
vector<int> SceneRule::getSceneBossId(int sceneId)
{
	return stringToVectorInt(getSceneAttribute(sceneId,"bossIds"));
}
//获取 技能兵id
vector<int> SceneRule::getSkillNpcId(int sceneId)
{
	return stringToVectorInt(getSceneAttribute(sceneId,"skillSoldierIds"));

}
//获取士兵id
vector<int> SceneRule::getNpcId(int sceneId)
{
	return stringToVectorInt(getSceneAttribute(sceneId,"soldierIds"));
}
vector<int> SceneRule::stringToVectorInt(string str)
{
	vector<string> strVec = INSTANCE(BaseDataManager)->split(str,"_");
	vector<int> result;
	for (auto& id : strVec)
	{
		result.push_back(Value(id).asInt());
	}
	return result;
}

	
ValueMap SceneRule::getSceneDic(int sceneId)
{
	if (mainDic.empty())
	{
		mainDic = INSTANCE(BaseDataManager)->getXml(ScenesXml);
	}
	
	lastSubDic = mainDic[Value(sceneId).asString()].asValueMap();
	return lastSubDic;
}

string SceneRule::getSceneAttribute(int sceneId,const string& attributeName)
{
	return getSceneDic(sceneId)[attributeName].asString();
}

//获取场景名
string SceneRule::getSceneName(int sceneId)
{
	return INSTANCE(BaseDataManager)->getLan(getSceneAttribute(sceneId,"name"));
}
//获取场景描述
string SceneRule::getSceneDesc(int sceneId)
{
	return getSceneAttribute(sceneId,"description");
}
//获取场景所需等级
int SceneRule::getSceneNeedLevel(int sceneId)
{
	return Value(getSceneAttribute(sceneId,"level")).asInt();
}
//获取场景所需vip
int SceneRule::getSceneNeedVip(int sceneId)
{
	return Value(getSceneAttribute(sceneId,"viplevel")).asInt();
}
//获取场景阵型Id
string SceneRule::getSceneFormation(int sceneId)
{
	return getSceneAttribute(sceneId,"baseFormationIds");
}

//获取场景阵型
vector<vector<int> > SceneRule::getSceneFormationVector(int sceneId)
{
	vector<vector<int>> result;
	string temp = getSceneFormation(sceneId);
	vector<string> tmp1 = INSTANCE(BaseDataManager)->split(temp,"|");
	for (int i = 0; i < tmp1.size(); i++)
	{
		vector<string> tmp2 = INSTANCE(BaseDataManager)->split(tmp1[i],"_");
		vector<int> r1;
		for (auto& t2 : tmp2)
		{
			r1.push_back(Value(t2).asInt());
		}
		result[i] = r1;
	}
	return result;
}

//获取boss出现数量
int SceneRule::getSceneBossCount(int sceneId)
{
	return Value(getSceneAttribute(sceneId,"ariseBossCount")).asInt();
}

//获取士兵概率
vector<float> SceneRule::getNpcProbabilitys(int sceneId)
{
	vector<string> temp = INSTANCE(BaseDataManager)->split(getSceneAttribute(sceneId,"soldierProbabilitys"),"_");
	vector<float> result;
	for (auto& t : temp)
	{
		result.push_back(Value(t).asFloat());
	}
	return result;
}

//获取技能兵概率
float SceneRule::getSkillNpcProbability(int sceneId)
{
	return Value(getSceneAttribute(sceneId,"skillSoldierProbability")).asFloat();
}

//获取得分区间
vector<int> SceneRule::getScoreVector(int sceneId,int type)
{
	vector<string> temp;
	if (type == 1)
	{
		temp = INSTANCE(BaseDataManager)->split(getSceneAttribute(sceneId,"scoreInterregional"),"_");
	}
	else if (type == 2)
	{
		temp = INSTANCE(BaseDataManager)->split(getSceneAttribute(sceneId,"scoreInterregional2"),"_");
	}
	else
	{
		temp = INSTANCE(BaseDataManager)->split(getSceneAttribute(sceneId,"scoreInterregional3"),"_");
	}
	vector<int> result;
	for (auto& t : temp)
	{
		result.push_back(Value(t).asInt());
	}
	return result;
}
//获取影响系数
float SceneRule::getScoreCoefficient(int sceneId)
{
	return Value(getSceneAttribute(sceneId,"defaultMaxWinScoreCoefficient")).asFloat();
}
//获取得分周期影响系数加成
float SceneRule::getCycleScoreCoefficientAddition(int sceneId)
{
	return Value(getSceneAttribute(sceneId,"scoreCycleCoefficientAddition")).asFloat();
}
//获取攻击累计加成影响系数
float SceneRule::getAttackScoreCoefficientAddition(int sceneId)
{
	return Value(getSceneAttribute(sceneId,"attackCumulativeCoefficientAddition")).asFloat();
}


//场景倍率
int SceneRule::getSceneMagnification(int sceneId)
{
	return Value(getSceneAttribute(sceneId,"magnification")).asInt();
}
//出分周期命中率
float SceneRule::getSceneScoreHitRate(int sceneId)
{
	return Value(getSceneAttribute(sceneId,"scoreCycleHitRate")).asFloat();
}
//吃分周期命中率
float SceneRule::getSceneLoseHitRate(int sceneId)
{
	return Value(getSceneAttribute(sceneId,"loseScoreCycleHitRate")).asFloat();
}
//得分部队命中率
float SceneRule::getTroopsHitRate(int sceneId)
{
	return Value(getSceneAttribute(sceneId,"scoreTroopsHitRate")).asFloat();
}
