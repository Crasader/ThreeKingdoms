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
	return stringToVectorInt(getSceneAttribute(sceneId,"bossId"));
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
