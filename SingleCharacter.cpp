#include "SingleCharacter.h"
#include "RoleRule.h"
#include "tools/AnimationUtils.h"
#include "tools/GameUtils.h"
#include "UserData.h"

SingleCharacter::SingleCharacter(int roleId)
{
	this->roleId = roleId;
}

SingleCharacter::~SingleCharacter()
{

}

SingleCharacter* SingleCharacter::create(int roleId)
{
	SingleCharacter* sc = new SingleCharacter(roleId);
	if (sc && sc->init())
	{
		sc->autorelease();
		return sc;
	}
	else
	{
		delete sc;
		sc = nullptr;
		return nullptr;
	}
}
bool SingleCharacter::init()
{
	if (!Sprite::initWithSpriteFrameName(getFrameName(roleId,FrameType_role)))
	{
		return false;
	}
	setAnchorPoint(INSTANCE(RoleRule)->getRoleAnchorPoint(roleId));
	setColor(Color3B::BLACK);


	initContent();

	return true;
}

void SingleCharacter::initContent()
{
	lightEffect = Sprite::createWithSpriteFrameName(getFrameName(roleId,FrameType_lightEffect));
	addChild(lightEffect,-1);
	lightEffect->setPosition(getAnchorPointInPoints()+Vec2::ZERO);
	lightEffect->setColor(Color3B::BLACK);

	selectedFlag = Sprite::createWithSpriteFrameName("createCharacter_selectedFlag.png");
	addChild(selectedFlag,-1);
	selectedFlag->setPosition(getAnchorPointInPoints()+Vec2(0,150));
	selectedFlag->setVisible(false);

	roleName = Sprite::createWithSpriteFrameName(getFrameName(roleId,FrameType_name));
	addChild(roleName);
	roleName->setPosition(getAnchorPointInPoints()+Vec2(0,-40));
	roleName->setVisible(false);

	auto name = Label::create();
	name->setString(INSTANCE(RoleRule)->getRoleName(roleId));
	//log("%s",INSTANCE(RoleRule)->getRoleName(roleId).c_str());
	roleName->addChild(name);
	name->setPosition(INSTANCE(GameUtils)->getNodeCenterPosition(roleName));

	//1.首先设置一个触摸区域
	auto evenNode = Node::create();
	evenNode->setContentSize(Size(this->getContentSize().width * 0.2f,this->getContentSize().height*0.4f));
	this->addChild(evenNode);
	evenNode->setPosition(this->getAnchorPointInPoints() + Vec2(-50,50));

	//2.用这个触摸区域来订阅触摸消息
	auto listener = EventListenerTouchOneByOne::create();
	//listener->setSwallowTouches(true);
	listener->onTouchBegan = [&](Touch* touch, Event* event){
		//setSelect(true);
		auto target = static_cast<Sprite*>(event->getCurrentTarget());

		Vec2 locationInNode = target->convertToNodeSpace(touch->getLocation());
		Size s = target->getContentSize();
		Rect rect = Rect(0, 0, s.width, s.height);
		//3.触摸点在触摸区才执行
		if (rect.containsPoint(locationInNode))
		{
			//log("sprite began... x = %f, y = %f", locationInNode.x, locationInNode.y);
			//发送取消所有选择的消息
			_eventDispatcher->dispatchCustomEvent(UnselectAllSingleCharacter);
			setSelect(true);
			//保存当前角色id
			INSTANCE(UserData)->setCurrentRoleId(roleId);
			return true;
		}
		return false;
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener,evenNode);
}

string SingleCharacter::getFrameName(int roleId,FrameType type)
{
	string result;
	switch (type)
	{
	case FrameType_role:
		result = INSTANCE(RoleRule)->getRoleFirstFrameNameByRoleId(roleId,RoleStatusStand);
		break;
	case FrameType_name:
		result = "createCharacter_roleName.png";
		break;
	case FrameType_lightEffect:
		result = getLightEffect(roleId);
		break;
	default:
		break;
	}
	return result;
}
string SingleCharacter::getLightEffect(int roleId)
{
	string result;
	switch (roleId)
	{
	case 20003:
		result = "createCharacter_lightEffect_purple.png";
		break;
	case 20002:
		result = "createCharacter_lightEffect_blue.png";
		break;
	case 20005:
		result = "createCharacter_lightEffect_yellow.png";
		break;
	case 20001:
		result = "createCharacter_lightEffect_red.png";
		break;
	default:
		break;
	}
	return result;
}

void SingleCharacter::setSelect(bool select)
{
	if (select)
	{
		selectedFlag->setVisible(true);
		roleName->setVisible(true);
		setColor(Color3B::WHITE);
		lightEffect->setColor(Color3B::WHITE);
		stopAllActions();
		auto animate = INSTANCE(AnimationUtils)->getModelAnimate(roleId,RoleStatusSkill,0.1f);
		runAction(Sequence::create(animate,
			CallFunc::create(CC_CALLBACK_0(SingleCharacter::skillComplete,this)),nullptr));
	}
	else
	{
		selectedFlag->setVisible(false);
		roleName->setVisible(false);
		setColor(Color3B::BLACK);
		lightEffect->setColor(Color3B::BLACK);
		stopAllActions();
		setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(
			INSTANCE(RoleRule)->getRoleFirstFrameNameByRoleId(roleId,RoleStatusStand)));
	}
}

void SingleCharacter::skillComplete()
{
	stopAllActions();
	auto animate = INSTANCE(AnimationUtils)->getModelAnimate(roleId,RoleStatusStand,0.1f);
	runAction(RepeatForever::create(animate));
}
