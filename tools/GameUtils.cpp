#include "GameUtils.h"

bool GameUtils::init()
{
	return true;
}

//获取节点中心点
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
	//使用随机数引擎
	default_random_engine e1(time(0));
	int r = e1()%size;
	return r;
}

int GameUtils::getRandomFromVector(vector<vector<float>> param)
{
	return 1;
}

bool GameUtils::getRandomFromFloat(float param)
{
	default_random_engine e(time(0));
	uniform_real_distribution<float> f(0,10);
	float r = f(e);
	float probability = param * 10.0f;
	if (r <= probability)
	{
		return true;
	}
	return false;
}

int GameUtils::getRandomFromVector(vector<int> param)
{
	default_random_engine e(time(0));
	//生成均匀分布的随机数(0~param.size())
	uniform_int_distribution<unsigned> u(0,param.size() - 1);
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
