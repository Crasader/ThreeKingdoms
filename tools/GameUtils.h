/************************************************************************/
/* ��Ϸ������                                                                     */
/* �����������
/************************************************************************/
#pragma once

#include "cocos2d.h"
#include "GameCommon.h"

//��ȡ�ڵ�����ĵ�
#define getCenterPosition(node) INSTANCE(GameUtils)->getNodeCenterPosition(node)

USING_NS_CC;
using namespace std;

class GameUtils : public Ref
{
public:
	CLASS_INSTANCE(GameUtils);
	bool init();

	//��ȡ�ڵ����ĵ�
	Vec2 getWindowsCenterPosition();
	Vec2 getNodeCenterPosition(Node* node);

	int getRandom(int size);

	int getRandomFromVector(vector<vector<float>> param);
	//ƽ������
	int getRandomFromVector(vector<int> param);

	//�Ƿ�鵽����_p
	bool vectorContainInt(vector<int> v,int _p);

};