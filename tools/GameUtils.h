/************************************************************************/
/* 游戏工具类                                                                     */
/* 生成了随机数
/************************************************************************/
#pragma once

#include "cocos2d.h"
#include "GameCommon.h"

//获取节点的中心点
#define getCenterPosition(node) INSTANCE(GameUtils)->getNodeCenterPosition(node)

USING_NS_CC;
using namespace std;

class GameUtils : public Ref
{
public:
	CLASS_INSTANCE(GameUtils);
	bool init();

	//获取节点中心点
	Vec2 getWindowsCenterPosition();
	Vec2 getNodeCenterPosition(Node* node);

	int getRandom(int size);

	int getRandomFromVector(vector<vector<float>> param);
	//平均概率
	int getRandomFromVector(vector<int> param);

	//是否抽到概率_p
	bool vectorContainInt(vector<int> v,int _p);

};