//
//����һ��Id��ȡ���id����Դ��
//
#pragma once

#include <iostream>
#include "tools/GameCommon.h"
#include "cocos2d.h"

using namespace std;
USING_NS_CC;

class ResourceManager:public Ref
{
public:
    CLASS_INSTANCE(ResourceManager);
    bool init();
    
	vector<string> getNpcResourceImg(int npcId);
	vector<string> getRoleResourceImg(int roleId);
};

