#include "AnimationUtils.h"
#include "ModelRule.h"

bool AnimationUtils::init()
{
	return true;
}

Animation* AnimationUtils::getModelAnimation(int modelId,const string& fileName,const string& frameName,float duration)
{
	string imgPath = INSTANCE(ModelRule)->getModelPath(modelId);
	imgPath += fileName;
	imgPath += ".plist";

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(imgPath);
	return getAnimation(frameName,duration);
}
Animation* AnimationUtils::getModelAnimation(int modelId,const string& fileName,const string& frameName,float duration,int startIndex,int endIndex)
{
	string imgPath = INSTANCE(ModelRule)->getModelPath(modelId);
	imgPath += fileName;
	imgPath += ".plist";

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(imgPath);
	return getAnimation(frameName,duration,startIndex,endIndex);
}

Animate* AnimationUtils::getModelAnimate(int modelId,RoleStatus status,float duration)
{
	string img = INSTANCE(RoleRule)->getRoleFrameNameByRoleId(modelId,status);
	auto animation = getModelAnimation(INSTANCE(RoleRule)->getRoleModelId(modelId),img,img,duration);
	auto animate = Animate::create(animation);
	return animate;
}

Animation* AnimationUtils::getCommonAnimation(const string& fileName,const string& frameName, float duration)
{
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(fileName);
	return getAnimation(frameName,duration);
}


Animation* AnimationUtils::getAnimation(const string& frameName,float duration)
{
	Vector<SpriteFrame*> animFrames;

	string name_str = frameName;
	name_str += "_000";
	int i = name_str.size();
	char str[80];
	for (int k=0; k<=30; k++)
	{
		if (k <= 9)
		{
			sprintf_s(str,"%s%d.png",name_str.c_str(),(k));
		}
		else
		{
			sprintf_s(str,"%s%d.png",name_str.substr(0,i-1).c_str(),(k));
		}
		auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(Value(str).asString());
		if (frame)
		{
			animFrames.pushBack(frame);
		}
		else
		{
			break;
		}
	}
	auto animation = Animation::createWithSpriteFrames(animFrames,duration);
	return animation;
}
Animation* AnimationUtils::getAnimation(const string& frameName,float duration,int startIndex,int endIndex)
{
	Vector<SpriteFrame*> animFrames;
	string name_str = frameName;
	name_str += "_000";
	int i = name_str.size();
	char str[80];
	for (int k = startIndex; k <= endIndex ; k++)
	{
		if (k <= 9)
		{
			sprintf_s(str, "%s%d.png",name_str.c_str(),(k));
		}
		else
		{
			sprintf_s(str, "%s%d.png",name_str.substr(0,i-1).c_str(),(k));
		}

		auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(Value(str).asString());
		if (frame)
		{
			animFrames.pushBack(frame);
		}
		else
		{
			break;
		}
	}
	auto animation = Animation::createWithSpriteFrames(animFrames,duration);
	return animation;
}
