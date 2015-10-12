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

    //��ȡ������
    string getSceneName(int sceneId);
    //��ȡ��������
    string getSceneDesc(int sceneId);
    //��ȡ��������ȼ�
    int getSceneNeedLevel(int sceneId);
    //��ȡ��������vip
    int getSceneNeedVip(int sceneId);
    //��ȡ��������Id
    string getSceneFormation(int sceneId);
    
    //��ȡboss��������
    int getSceneBossCount(int sceneId);
    
    //��ȡʿ������
    vector<float> getNpcProbabilitys(int sceneId);
    
    //��ȡ���ܱ�����
    float getSkillNpcProbability(int sceneId);
    
    //��ȡ�÷�����
    vector<int> getScoreVector(int sceneId,int type);
    //��ȡӰ��ϵ��
    float getScoreCoefficient(int sceneId);
    //��ȡ�÷�����Ӱ��ϵ���ӳ�
    float getCycleScoreCoefficientAddition(int sceneId);
    //��ȡ�����ۼƼӳ�Ӱ��ϵ��
    float getAttackScoreCoefficientAddition(int sceneId);
    
    //��ȡ��������
    vector<vector<int> > getSceneFormationVector(int sceneId);
    
    //��������
    int getSceneMagnification(int sceneId);
    //��������������
    float getSceneScoreHitRate(int sceneId);
    //�Է�����������
    float getSceneLoseHitRate(int sceneId);
    //�÷ֲ���������
    float getTroopsHitRate(int sceneId);
private:
	ValueMap getSceneDic(int sceneId);
	string getSceneAttribute(int sceneId,const string& attributeName);

	ValueMap mainDic;
	ValueMap lastSubDic;
};
