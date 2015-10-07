#include "GameUtils.h"

bool GameUtils::init()
{
	return true;
}

//��ȡ�ڵ����ĵ�
Vec2 GameUtils::getWindowsCenterPosition()
{
	auto size = Director::getInstance()->getWinSize();
	auto p = Vec2(size.width/2,size.height/2);
	return p;
}
Vec2 GameUtils::getNodeCenterPosition(Node* node)
{
	return Vec2(node->getContentSize().width/2,node->getContentSize().height/2);
}

int GameUtils::getRandom(int size)
{
	//ʹ�����������
	default_random_engine e1(time(0));
	int r = e1()%size;
	return r;
}

int GameUtils::getRandomFromVector(vector<vector<float>> param)
{
	return 1;
}

int GameUtils::getRandomFromVector(vector<int> param)
{
	//���ɾ��ȷֲ��������(0~param.size())
	uniform_int_distribution<unsigned> u(0,param.size());
	default_random_engine e;
	int r = u(e);
	return param[r];
}

bool GameUtils::vectorContainInt(vector<int> v,int _p)
{
	for (auto i : v)
	{
		if (_p == i)
		{
			return true;
		}
	}
	return false;
}
