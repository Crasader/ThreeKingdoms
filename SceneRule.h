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
	//��ȡ���еĳ���ID
	vector<int> getAllSceneId();
	//��ȡ����ͼƬID
	int getSceneImgId(int sceneId);

	//��ȡ����npc ID
	vector<int> getAllNpcId(int sceneId);
	//��ȡBoos id
	vector<int> getSceneBossId(int sceneId);
	//��ȡ ���ܱ�id
	vector<int> getSkillNpcId(int sceneId);
	//��ȡʿ��id
	vector<int> getNpcId(int sceneId);
	//��stringת����Vector<int>
	vector<int> SceneRule::stringToVectorInt(string str);
private:
	ValueMap getSceneDic(int sceneId);
	string getSceneAttribute(int sceneId,const string& attributeName);

	ValueMap mainDic;
	ValueMap lastSubDic;
};
