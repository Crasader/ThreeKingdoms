#include "SneakyButtonSkinnedBase.h"


bool SneakyButtonSkinnedBase::init()
{
	if (!Layer::init())
	{
		return false;
	}

	this->defaultSprite = nullptr;
	this->activatedSprite = nullptr;
	this->disabledSprite = nullptr;
	this->pressSprite = nullptr;
	this->sbutton = nullptr;
	this->schedule(schedule_selector(SneakyButtonSkinnedBase::watchSelf));

	return true;
}

SneakyButtonSkinnedBase::~SneakyButtonSkinnedBase()
{
	if (defaultSprite)
	{
		defaultSprite->release();
		defaultSprite = nullptr;
	}
	if (activatedSprite)
	{
		activatedSprite->release();
		activatedSprite = nullptr;
	}
	if (disabledSprite)
	{
		disabledSprite->release();
		disabledSprite = nullptr;
	}
	if (pressSprite)
	{
		pressSprite->release();
		pressSprite = nullptr;
	}
	if (sbutton)
	{
		sbutton->release();
		sbutton = nullptr;
	}
}


void SneakyButtonSkinnedBase::watchSelf(float delta) //Be Careful Here
{
	if (!this->sbutton->getStatus()){
		if(disabledSprite){
			disabledSprite->setVisible(true);
		}
		else {
			disabledSprite->setVisible(false);
		}
	}
	else {
		if(!this->sbutton->getIsActive()){
			pressSprite->setVisible(false);
			if(this->sbutton->getValue() == 0){
				activatedSprite->setVisible(false);
				if(defaultSprite){
					defaultSprite->setVisible(true);
				}
			}
			else {
				activatedSprite->setVisible(true);
			}
		}
		else {
			defaultSprite->setVisible(false);
			if(pressSprite){
				pressSprite->setVisible(true);
			}
		}
	}
}

void SneakyButtonSkinnedBase::setContentSize(Size s)
{
	Layer::setContentSize(s);
	defaultSprite->setContentSize(s);
	//button->setRadius(s.width/2);
}

void SneakyButtonSkinnedBase::setDefaultSprite(Sprite *aSprite)
{
	if(defaultSprite){
		if(defaultSprite->getParent())
			defaultSprite->getParent()->removeChild(defaultSprite, true);
		defaultSprite->release();
	}
	aSprite->retain();
	defaultSprite = aSprite; //Check again here
	if(aSprite){
		this->addChild(defaultSprite, 0);

		this->setContentSize(defaultSprite->getContentSize());
	}
}

void SneakyButtonSkinnedBase::setActivatedSprite(Sprite *aSprite)
{
	if(activatedSprite){
		if(activatedSprite->getParent())
			activatedSprite->getParent()->removeChild(activatedSprite, true);
		activatedSprite->release();
	}
	aSprite->retain();
	activatedSprite = aSprite;
	if(aSprite){
		this->addChild(activatedSprite, 1);
		
		this->setContentSize(activatedSprite->getContentSize());
	}
}

void SneakyButtonSkinnedBase::setDisabledSprite(Sprite *aSprite)
{
	if(disabledSprite){
		if(disabledSprite->getParent())
			disabledSprite->getParent()->removeChild(disabledSprite, true);
		disabledSprite->release();
	}
	aSprite->retain();
	disabledSprite = aSprite;
	if(aSprite){
		this->addChild(disabledSprite, 2);
		
		this->setContentSize(disabledSprite->getContentSize());
	}
}

void SneakyButtonSkinnedBase::setPressSprite(Sprite *aSprite)
{
	if(pressSprite){
		if(pressSprite->getParent())
			pressSprite->getParent()->removeChild(pressSprite, true);
		pressSprite->release();
	}
	aSprite->retain();
	pressSprite = aSprite;
	if(aSprite){
		this->addChild(pressSprite, 3);
		
		this->setContentSize(pressSprite->getContentSize());
	}
}

void SneakyButtonSkinnedBase::setButton(SneakyButton *aButton)
{
	if(sbutton){
		if(sbutton->getParent())
			sbutton->getParent()->removeChild(sbutton, true);
		sbutton->release();
	}
	aButton->retain();
	sbutton = aButton;
	if(aButton){
		this->addChild(sbutton, 4);
		if(defaultSprite)
			sbutton->setRadius(defaultSprite->boundingBox().size.width/2);
	}
}









