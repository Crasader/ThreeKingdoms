#include "ChapterScene.h"
#include "tools/GameUtils.h"
#include "CommonBg.h"

Scene* ChapterScene::createScene()
{
	auto scene = Scene::create();
	auto layer = ChapterScene::create();
	scene->addChild(layer);
	return scene;
}
bool ChapterScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	initContent();

	return true;
}

void ChapterScene::initContent()
{
	auto winSize = Director::getInstance()->getWinSize();
	addChild(CommonBg::create("¹Ø¿¨Ñ¡Ôñ"));
	setPosition(INSTANCE(GameUtils)->getWindowsCenterPosition());

}
