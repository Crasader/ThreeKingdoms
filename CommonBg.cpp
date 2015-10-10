#include "CommonBg.h"
#include "tools/GameUtils.h"

CommonBg::CommonBg(string title)
{
	this->title = title;
}
CommonBg::~CommonBg()
{

}

CommonBg* CommonBg::create(string title)
{
	CommonBg* commonBg = new CommonBg(title);
	if (commonBg && commonBg->init())
	{
		commonBg->autorelease();
		return commonBg;
	}
	else
	{
		delete commonBg;
		commonBg = nullptr;
		return nullptr;
	}
}

bool CommonBg::init()
{
	if (!Node::init())
	{
		return false;
	}
	initContent();
	return true;
}

void CommonBg::initContent()
{
	auto winSize = Director::getInstance()->getWinSize();
	setContentSize(winSize);
	setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	setPosition(INSTANCE(GameUtils)->getWindowsCenterPosition());
	
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("ui/chapter/chapter.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("common/common.plist");

	auto topBar = Scale9Sprite::createWithSpriteFrame(
		SpriteFrameCache::getInstance()->getSpriteFrameByName("chapter_texture.png"));
	topBar->setPreferredSize(Size(winSize.width,115));
	topBar->setAnchorPoint(Vec2::ANCHOR_MIDDLE_TOP);
	topBar->setPosition(Vec2(0,winSize.height/2));
	addChild(topBar);

	auto bottomBar = Scale9Sprite::createWithSpriteFrame(
		SpriteFrameCache::getInstance()->getSpriteFrameByName("chapter_texture.png"));
	bottomBar->setPreferredSize(Size(winSize.width,115));
	bottomBar->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
	bottomBar->setPosition(Vec2(0,-winSize.height/2));
	addChild(bottomBar);

	auto frame1 = Sprite::createWithSpriteFrameName("chapter_frame_1.png");
	addChild(frame1);
	frame1->setAnchorPoint(Vec2::ANCHOR_MIDDLE_TOP);
	frame1->setPosition(Vec2(0,winSize.height/2));

	auto frame2 = Sprite::createWithSpriteFrameName("chapter_frame_1.png");
	addChild(frame2);
	frame2->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
	frame2->setPosition(Vec2(0,-winSize.height/2));
	frame2->setFlippedY(true);

	auto frameLeft = Sprite::createWithSpriteFrameName("chapter_frame_2.png");
	addChild(frameLeft);
	frameLeft->setAnchorPoint(Vec2::ANCHOR_MIDDLE_RIGHT);
	frameLeft->setPosition(Vec2(-winSize.width/2,0));
	frameLeft->setRotation(180);

	auto frameRight = Sprite::createWithSpriteFrameName("chapter_frame_2.png");
	addChild(frameRight);
	frameRight->setAnchorPoint(Vec2::ANCHOR_MIDDLE_RIGHT);
	frameRight->setPosition(Vec2(winSize.width/2,0));

	auto colorLayer = LayerColor::create(Color4B(61,34,0,255));
	addChild(colorLayer);
	colorLayer->setPosition(Vec2(-winSize.width/2+7,-winSize.height/2+115));
	colorLayer->setContentSize(Size(winSize.width-14,410));

	auto line_1 = Sprite::createWithSpriteFrameName("chapter_line.png");
	addChild(line_1);
	line_1->setPosition(Vec2(-1,winSize.height/2 - 115));

	auto line_2 = Sprite::createWithSpriteFrameName("chapter_line.png");
	addChild(line_2);
	line_2->setPosition(Vec2(-1,-winSize.height/2+ 115));
	line_2->setFlippedY(true);

	auto titleBg = Sprite::createWithSpriteFrameName("common_titleBg.png");
	addChild(titleBg);
	titleBg->setPosition(Vec2(40,240));

	//显示不了中文，莫名其妙！！！
	//需要转换成utf-8格式
	auto title = Label::createWithBMFont("font/font_uiTitle.fnt",this->title);
    //auto title = Label::createWithTTF("hello world", "fonts/Marker Felt.ttf", 24);
	//auto title = Label::createWithBMFont("fonts/bitmapFontChinese.fnt", "中国.");
	//auto title = Label::createWithBMFont("fonts/futura-48.fnt", "Chapter");
	addChild(title);
	title->setPosition(Vec2(0,240));
	title->setColor(Color3B::RED);
}
