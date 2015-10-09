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
private:
	ValueMap getSceneDic(int sceneId);
	string getSceneAttribute(int sceneId,const string& attributeName);

	ValueMap mainDic;
	ValueMap lastSubDic;
};
