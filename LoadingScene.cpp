#include "LoadingScene.h"
#include "tools/GameUtils.h"
#include "tools/AnimationUtils.h"
#include "UserData.h"
#include "SceneRule.h"
#include "ResourceManager.h"
#include "FightScene.h"

LoadingScene::LoadingScene()
{

}
LoadingScene::~LoadingScene()
{

}
Scene* LoadingScene::createScene()
{
	auto scene = Scene::create();
	auto layer = LoadingScene::create();
	scene->addChild(layer);
	return scene;
}

void LoadingScene::onEnter()
{
	Layer::onEnter();
	setPosition(INSTANCE(GameUtils)->getWindowsCenterPosition());
	startLoad();
}

void LoadingScene::onExit()
{
	Layer::onExit();
	removeAllChildren();
}

bool LoadingScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	initContent();

	return true;
}

void LoadingScene::initContent()
{
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("ui/loadingScene/loadingScene.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("ui/loadingScene/loading_fire.plist");

	auto role = Sprite::createWithSpriteFrameName("loadingScene_role.png");
	addChild(role);
	role->setPosition(Vec2(240,0));

	auto logo = Sprite::createWithSpriteFrameName("loadingScene_logo.png");
	addChild(logo);
	logo->setPosition(Vec2(0,20));

	frame = Sprite::createWithSpriteFrameName("loadingScene_frame.png");
	addChild(frame);
	frame->setPosition(Vec2(0,-150));

	loadingBar = ProgressTimer::create(Sprite::createWithSpriteFrameName("loadingScene_bar.png"));
	loadingBar->setType(ProgressTimer::Type::BAR);
	loadingBar->setBarChangeRate(Vec2::ANCHOR_BOTTOM_RIGHT);
	loadingBar->setMidpoint(Vec2::ZERO);
	loadingBar->setPercentage(0.0f);
	frame->addChild(loadingBar);
	loadingBar->setPosition(getCenterPosition(frame));

	fire = Sprite::createWithSpriteFrameName("loading_fire_0000.png");
	fire->setAnchorPoint(Vec2::ANCHOR_MIDDLE_RIGHT);
	frame->addChild(fire);
	fire->setPosition(Vec2(50,frame->getContentSize().height/2));

	auto animate = Animate::create(
		INSTANCE(AnimationUtils)->getCommonAnimation("ui/loadingScene/loading_fire.plist","loading_fire",0.07f));
	auto repeat = RepeatForever::create(animate);
	fire->runAction(repeat);
}

void LoadingScene::startLoad()
{
	int sceneId = INSTANCE(UserData)->getCurrentSceneId();
	//npc资源,soSoldierXml有点问题需要修改
	vector<int> npcId = INSTANCE(SceneRule)->getAllNpcId(sceneId);
	for (auto id : npcId)
	{
		vector<string> tv = INSTANCE(ResourceManager)->getNpcResourceImg(id);
		resourceVector.insert(resourceVector.end(),tv.begin(),tv.end());
	}

	//主角资源
	vector<string> rv = INSTANCE(ResourceManager)->getRoleResourceImg(INSTANCE(UserData)->getCurrentRoleId());
	resourceVector.insert(resourceVector.end(),rv.begin(),rv.end());
	//地图和UI资源
	resourceVector.push_back(string("maps/")+Value(sceneId).asString()+".png");
	resourceVector.push_back("ui/fightUI/fightUI.png");

	currentLoadNum = 0;
	for (auto id : resourceVector)
	{
		Director::getInstance()->getTextureCache()->addImageAsync(id,CC_CALLBACK_0(LoadingScene::loadHandler,this));
	}

	//for(auto x : resourceVector)
	//{
	//	log("%s",Value(x).asString().c_str());
	//}
}
void LoadingScene::loadHandler()
{
	currentLoadNum++;
	loadingBar->setPercentage(100.0f * (float)currentLoadNum / resourceVector.size());
	
	int py = 25 + 545 *(loadingBar->getPercentage()/100);
	if(py >= 50)
	{
		fire->setPosition(Vec2(py, fire->getPositionY()));
	}

	//如果资源加载完成，进入到战斗界面
	if (currentLoadNum >= resourceVector.size())
	{
		resourceVector.clear();
		//进入到战斗界面
		Director::getInstance()->replaceScene(FightScene::createScene());
	}
}
