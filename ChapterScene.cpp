#include "ChapterScene.h"
#include "tools/GameUtils.h"
#include "CommonBg.h"
#include "tools/ButtonUtils.h"
#include "CommonTitleBar.h"
#include "SceneRule.h"
#include "UserData.h"
#include "LoadingScene.h"

ChapterScene::ChapterScene()
{
	currentSelectedSceneIndex = 0;
	frameWidth = 620;
	frameSpace = 100;
}
ChapterScene::~ChapterScene()
{

}
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

	sceneIdVector = INSTANCE(SceneRule)->getAllSceneId();
	for(auto& id : sceneIdVector)
	{
		log("%d",id);
	}
	//sceneIdVector = vector<int> v{40001,40002,40003,40004,40005,40006};
	//for (int i = 40001;i<=40006;i++)
	//{
	//	sceneIdVector.push_back(i);
	//}
	initContent();
	initScrollView();

	return true;
}

void ChapterScene::initContent()
{
	auto winSize = Director::getInstance()->getWinSize();
	addChild(CommonBg::create("关卡选择"));
	setPosition(INSTANCE(GameUtils)->getWindowsCenterPosition());

	auto backBtn = INSTANCE(ButtonUtils)->createButton("common_backBtn.png",Size(75,81),"");
	auto setBtn = INSTANCE(ButtonUtils)->createButton("common_setBtn.png",Size(75,81),"");
	auto rechargeBtn = INSTANCE(ButtonUtils)->createButton("common_rechargeBtn.png",Size(75,81),"");
	addChild(backBtn);
	addChild(setBtn);
	addChild(rechargeBtn);
	backBtn->setPosition(Vec2(winSize.width/2 - 60,260));
	setBtn->setPosition(Vec2(winSize.width/2 - 60,-260));
	rechargeBtn->setPosition(Vec2(winSize.width/2 - 160,-260));
	backBtn->addTargetWithActionForControlEvents(this,cccontrol_selector(ChapterScene::onBack),Control::EventType::TOUCH_UP_INSIDE);
	setBtn->addTargetWithActionForControlEvents(this,cccontrol_selector(ChapterScene::openSet),Control::EventType::TOUCH_UP_INSIDE);
	rechargeBtn->addTargetWithActionForControlEvents(this,cccontrol_selector(ChapterScene::openSet),Control::EventType::TOUCH_UP_INSIDE);

	titleBar = CommonTitleBar::create();
	addChild(titleBar);
	titleBar->setPosition(Vec2(60-winSize.width/2,60-winSize.height/2));

	moneyBar = CommonMoneyBar::create();
	addChild(moneyBar);
	moneyBar->setPosition(Vec2(360-winSize.width/2,60-winSize.height/2));

}

void ChapterScene::onBack(Ref* senderz,Control::EventType controlEvent)
{
	log("onBack");
}
void ChapterScene::openSet(Ref* senderz,Control::EventType controlEvent)
{
	log("openSet");
}

void ChapterScene::initScrollView()
{
	auto winSize = Director::getInstance()->getWinSize();
	layer = Layer::create();
	scrollView = ScrollView::create();
	//1.必须要继承ScrollViewDelegate
	//2.要想执行scrollViewDidScroll必须执行这一句
	scrollView->setDelegate(this);

	scrollView->setContainer(layer);
	scrollView->setDirection(ScrollView::Direction::HORIZONTAL);
	addChild(scrollView);
	scrollView->setPosition(Vec2(-winSize.width/2,-200));

	for (int i = 0;i < sceneIdVector.size();i++)
	{
		log("%s",Value(sceneIdVector[i]).asString().c_str());
		SingleSceneFrame* frame = SingleSceneFrame::create(sceneIdVector[i]);
		layer->addChild(frame);
		frame->setPosition(Vec2(frameWidth/2 -10 + i*frameWidth,200));
		frameVector.pushBack(frame);
		if (i != currentSelectedSceneIndex)
		{
			frame->setScale(0.8f);
		}
	}

	scrollView->setViewSize(Size(winSize.width,400));
	scrollView->setContentSize(Size(frameWidth*6,scrollView->getViewSize().height));
	scrollView->setContentOffset(Vec2((winSize.width - frameWidth)/2 - frameWidth* currentSelectedSceneIndex,0));


	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [=](Touch* touch,Event* event){
		return true;
	};
	listener->onTouchEnded = [=](Touch* touch,Event* event){
		adjustScrollView();
	};
	listener->onTouchCancelled = [=](Touch* touch,Event* event){
		adjustScrollView();
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener,this);


	startBtn = INSTANCE(ButtonUtils)->createButton("chapter_startBtn.png",Size(226,87),"Start",40,Color3B::BLACK);
	addChild(startBtn);
	startBtn->addTargetWithActionForControlEvents(this,cccontrol_selector(ChapterScene::startGame),Control::EventType::TOUCH_UP_INSIDE);

	INSTANCE(ButtonUtils)->setButtonTitle(startBtn,Value(currentSelectedSceneIndex).asString());
}

void ChapterScene::adjustScrollView()
{
	auto winSize = Director::getInstance()->getWinSize();
	int w = (winSize.width - frameWidth)/2;
	scrollView->unscheduleAllCallbacks();
	int x = scrollView->getContentOffset().x;

	Vec2 adjustPos;
	float adjustAnimDelay;

	int current = w - currentSelectedSceneIndex * frameWidth;

	if (x < current)
	{
		if (abs(x - current) > frameSpace/2)
		{
			adjustPos = Vec2(current - frameWidth, 0);
			currentSelectedSceneIndex++;
		}
		else
		{
			adjustPos = Vec2(current,0);
		}
	}
	else
	{
		if (abs(current - x) > frameSpace/2)
		{
			adjustPos = Vec2(current + frameWidth, 0);
			currentSelectedSceneIndex--;
		}
		else
		{
			adjustPos = Vec2(current,0);
		}
	}
	if (currentSelectedSceneIndex == -1)
	{
		currentSelectedSceneIndex = 0;
		adjustPos = Vec2(w,adjustPos.y);
	}
	if (currentSelectedSceneIndex >= sceneIdVector.size())
	{
		currentSelectedSceneIndex = sceneIdVector.size() -1;
		adjustPos = Vec2(current,adjustPos.y);
	}
	adjustAnimDelay = Value(abs(x - adjustPos.x) / 2000).asFloat();
	scrollView->setContentOffsetInDuration(adjustPos,adjustAnimDelay);
}

void ChapterScene::scrollViewDidScroll(ScrollView* view)
{
	int centerPointX = INSTANCE(GameUtils)->getWindowsCenterPosition().x;
	for(auto& f : frameVector)
	{
		auto frame = static_cast<SingleSceneFrame*>(f);
		int pX = frame->getParent()->convertToWorldSpace(frame->getPosition()).x;
		int scale = abs(pX - centerPointX);
		if (scale > 200)
		{
			frame->setScale(0.8f);
		}
		else
		{
			frame->setScale((100.0f - scale/10.0f)/100.0f);
		}
	}
}

void ChapterScene::startGame(Ref* senderz,Control::EventType controlEvent)
{
	log("startgame");
	int curSceneId = sceneIdVector[currentSelectedSceneIndex];

	log("%d",curSceneId);
	INSTANCE(UserData)->setCurrentSceneId(curSceneId);

	//进入游戏加载场景
	Director::getInstance()->replaceScene(LoadingScene::createScene());
}
