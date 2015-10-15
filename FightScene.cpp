#include "FightScene.h"
#include "tools/GameUtils.h"
#include "SceneRule.h"
#include "UserData.h"
#include "FightUI.h"
#include "FightManager.h"
#include "NPCManager.h"

FightScene::FightScene()
{

}
FightScene::~FightScene()
{

}
Scene* FightScene::createScene()
{
	auto scene = Scene::create();
	auto layer = FightScene::create();
	scene->addChild(layer);
	//INSTANCE(FightManager)->setFightScene(layer);
	INSTANCE(NPCManager)->setFightScene(layer);
	return scene;
}

void FightScene::onEnter()
{
	//监听技能震屏
	listenerShake = EventListenerCustom::create(NoticeSkillShake,[=](EventCustom* event){
		shake();
	});
	_eventDispatcher->addEventListenerWithFixedPriority(listenerShake,1);

	Layer::onEnter();
	INSTANCE(FightManager)->enterFight();
}

void FightScene::onExit()
{
	_eventDispatcher->removeEventListener(listenerShake);
	Layer::onExit();
	INSTANCE(NPCManager)->removeAllNpc();
	removeAllChildren();
	INSTANCE(FightManager)->exitFight();
}

bool FightScene::init()
{
	if (!Layer::init())
	{
		return false;
	}
	setPosition(INSTANCE(GameUtils)->getWindowsCenterPosition());
	initMap();
	initUI();
	initRole();

	scheduleUpdate();
	return true;
}

void FightScene::initMap()
{
	mapNode = Node::create();
	mapNode->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	addChild(mapNode);
	string mapName = string("maps/") + Value(INSTANCE(SceneRule)->getSceneImgId(INSTANCE(UserData)->getCurrentSceneId())).asString() + ".png";
	bg = Sprite::create(mapName);
	mapNode->addChild(bg);
	bg->setPosition(Vec2(0,20));
}
void FightScene::initUI()
{
	addChild(FightUI::create());
}
void FightScene::initRole()
{
	role = BaseRole::create(INSTANCE(UserData)->getCurrentRoleId());
	role->setPosition(Vec2(0,-170));
	mapNode->addChild(role);
	
	INSTANCE(UserData)->setRole(role);
}

//globalZOrder 是用于 渲染器 中用来给“绘制命令”排序的
//localZOrder 是用于父节点的子节点数组中给 节点 对象排序的
void FightScene::update(float dt)
{
	role->setLocalZOrder(320 - role->getPositionY());

	for (auto& npc : INSTANCE(NPCManager)->getAllNpc())
	{
		npc->setLocalZOrder(320 - npc->getPositionY());
	}
}

void FightScene::addNpcToScene(NPC* npc)
{
	mapNode->addChild(npc);
}

void FightScene::shake()
{
	auto move_1 = MoveBy::create(0.08f,Vec2(8,8));
	auto move_2 = MoveBy::create(0.16f,Vec2(-16,-16));
	auto move_3 = MoveBy::create(0.14f,Vec2(14,14));
	auto move_4 = MoveBy::create(0.08f,Vec2(-8,-8));
	auto move_5 = MoveBy::create(0.06f,Vec2(6,6));
	auto move_6 = MoveBy::create(0.04f,Vec2(-4,-4));
	auto action =Sequence::create(move_1,move_2,move_3,move_4,move_5,move_6,nullptr);
	mapNode->runAction(action);
}
