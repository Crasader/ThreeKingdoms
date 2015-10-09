#include "FightScene.h"
#include "tools/GameUtils.h"
#include "SceneRule.h"
#include "UserData.h"
#include "FightUI.h"

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
	return scene;
}

void FightScene::onEnter()
{
	Layer::onEnter();
}

void FightScene::onExit()
{
	Layer::onExit();
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
}
