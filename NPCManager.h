#pragma once

#include "cocos2d.h"
#include "cocos-ext.h"
#include "tools/GameCommon.h"
#include "NPC.h"
#include "FightScene.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace std;

class NPCManager:public Ref
{
public:
	CLASS_INSTANCE(NPCManager);
	bool init();

    void createTroopsNPC(int npcId,int formationIndex,RoleDirection direction,int speed,TroopsType troopsType);
    
    void createRandomNpc(int npcId,bool isBoss = false);
    
    void removeNPC(NPC *npc);
    
    void keepAllNpcStop(int second);
    void allNpcStopComplete();
    
    Vector<NPC*> getAllNpc();
    
    void removeAllNpc();
    
    void startUpdate();
    void stopUpdate();
    
    //void createGuideNpc_1();
    //void createGuideNpc_2();
    
    void setStop(bool param);

	//将npc添加到战斗场景需要有个场景的引用
	CC_SYNTHESIZE(FightScene*, fightScene,FightScene);
private:
    Vector<NPC*> npcArray;
    
    Vec2 getNPCPosition(int index,RoleDirection direction);
    
    void updateNpcInfo(float dt);
    
    void stopHandler();
    
    bool isStop;
    
    void removeNpcHandler();
    Vector<NPC*> tempNpcArray;
};
