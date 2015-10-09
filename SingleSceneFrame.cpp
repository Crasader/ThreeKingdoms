#include "SingleSceneFrame.h"


SingleSceneFrame* SingleSceneFrame::create(int sceneId)
{
	auto singleSceneFrame = new SingleSceneFrame(sceneId);
	if (singleSceneFrame && singleSceneFrame->init())
	{
		singleSceneFrame->autorelease();
		return singleSceneFrame;
	}
	else
	{
		delete singleSceneFrame;
		singleSceneFrame = nullptr;
		return nullptr;
	}
}
SingleSceneFrame::SingleSceneFrame(int sceneId)
{
	this->sceneId = sceneId;
}

SingleSceneFrame::~SingleSceneFrame()
{

}

bool SingleSceneFrame::init()
{
	if (!Node::init())
	{
		return false;
	}
	initContent();
	return true;
}

void SingleSceneFrame::initContent()
{
	auto frame = Sprite::createWithSpriteFrameName("chapter_frame.png");
	addChild(frame);
	string mapName("ui/chapter/miniMaps/mini_");
	mapName = mapName + Value(sceneId).asString() + ".png";
	auto map = Sprite::create(mapName);
	map->setPosition(Vec2(12,5));
	addChild(map);
}
