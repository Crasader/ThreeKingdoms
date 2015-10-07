#include "AnimateManager.h"

bool AnimateManager::init()
{
	return true;
}

void AnimateManager::showScaleAnimate(Node* sender)
{
	sender->setScale(0.2f);
	auto scale_1 = ScaleTo::create(0.2f,1.2f);
	auto scale_2 = ScaleTo::create(0.1f,1.0f);
	auto action = Sequence::create(scale_1,scale_2,DelayTime::create(2.0f),
		CallFuncN::create(CC_CALLBACK_1(AnimateManager::doRemoveFromParentAndCleanup,this,true)),nullptr);
	sender->runAction(action);
}
void AnimateManager::showAnimate(Node* sender)
{
	sender->setScale(0.2f);
	auto scale_1 = ScaleTo::create(0.2f,1.2f);
	auto scale_2 = ScaleTo::create(0.1f,1.0f);
	auto action = Sequence::create(scale_1,scale_2,nullptr);
	sender->runAction(action);
}
void AnimateManager::hideAnimate(Node* sender)
{
	sender->setScale(0.2f);
	auto scale_1 = ScaleTo::create(0.2f,1.2f);
	auto scale_2 = ScaleTo::create(0.1f,1.0f);
	auto action = Sequence::create(scale_1,scale_2,
		CallFuncN::create(CC_CALLBACK_1(AnimateManager::doRemoveFromParentAndCleanup,this,true)),nullptr);
	sender->runAction(action);
}

void AnimateManager::doRemoveFromParentAndCleanup(Node* sender,bool cleanup)
{
	sender->removeFromParentAndCleanup(cleanup);
}
