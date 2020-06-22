#include "MainMenuScene.h"
#include "OptionsScene.h"
#include "SimpleAudioEngine.h"

CCScene* OptionsMenu::scene()
{
	CCScene *scene = CCScene::create();
	OptionsMenu *layer = OptionsMenu::create();
	scene->addChild(layer);
	return scene;
}
// on "init" you need to initialize your instance
bool OptionsMenu::init()
{
	CCSize visibleSize =
		CCDirector::sharedDirector()->getVisibleSize();
	CCPoint origin =
		CCDirector::sharedDirector()->getVisibleOrigin();

	scrollingBgLayer = new ScrollingBgLayer(0.5f);//change later
	this->addChild(scrollingBgLayer);

	CCLabelBMFont *nameLabel = CCLabelBMFont::
		create("Options Menu", "invaderFont.fnt");
	nameLabel->setPosition(visibleSize.width / 2, visibleSize.height * 0.85);
	this->addChild(nameLabel);
	nameLabel->setScale(0.5);
	
	CCMenuItemImage *pMainMenuItem =
		CCMenuItemImage::create("RefreshButton.png",
		"RefreshButtonPressed.png",this,
		menu_selector(OptionsMenu::MainMenu));
	pMainMenuItem->setPosition(ccp(visibleSize.width * 0.4, visibleSize.height * 0.5));
	pMainMenuItem->setScale(0.15);

	//sound onoff items
	soundOn =
		CCMenuItemImage::create
	("soundOn.png", "soundOn.png", this,NULL);
		soundOff =
		CCMenuItemImage::create
	("soundOff.png", "soundOff.png", this,NULL);

		bool isPaused = CCUserDefault::sharedUserDefault() ->
			getBoolForKey("soundPaused");
		CCMenuItemToggle* soundToggleItem;
		if (isPaused == false)
		{
			soundToggleItem =
				CCMenuItemToggle::createWithTarget(this, menu_selector(OptionsMenu::SoundControl),
				soundOn, soundOff, NULL);
		}
		else
		{
			soundToggleItem =
				CCMenuItemToggle::createWithTarget(this, menu_selector(OptionsMenu::SoundControl),
				soundOff, soundOn, NULL);
		}
		soundToggleItem->setPosition(ccp(visibleSize.width* 0.7, visibleSize.height
			* 0.5));

	CCMenu* pMenu = CCMenu::create(pMainMenuItem,soundToggleItem, NULL);

	pMenu->setPosition(CCPointZero);
	this->addChild(pMenu, 10);
	this->scheduleUpdate();
	return true;
}
void OptionsMenu::update(float dt)
{
	scrollingBgLayer->Update();
}
void OptionsMenu::MainMenu(CCObject* pSender)
{
	//CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sounds/MenuTap.ogg");
	CocosDenshion::SimpleAudioEngine::sharedEngine() ->
		playEffect("sounds/MenuTap.ogg");

	CCScene *mScene = MainMenu::scene();
	CCDirector::sharedDirector()->replaceScene(mScene);
}

void OptionsMenu::SoundControl(CCObject* pSender)
{
	CCMenuItemToggle *toggleItem = (CCMenuItemToggle *)pSender;
	CocosDenshion::SimpleAudioEngine::sharedEngine() ->
	playEffect("sounds/MenuTap.ogg");
	if (toggleItem->selectedItem() == soundOff)
	{
		CCUserDefault::sharedUserDefault() ->
		setBoolForKey("soundPaused", true);
		CCUserDefault::sharedUserDefault()->flush();
		CocosDenshion::SimpleAudioEngine::sharedEngine() ->
		pauseBackgroundMusic();
	}
	else if (toggleItem->selectedItem() == soundOn)
	{
		CCUserDefault::sharedUserDefault() ->
		setBoolForKey("soundPaused", false);
		CCUserDefault::sharedUserDefault()->flush();
		CocosDenshion::SimpleAudioEngine::sharedEngine() ->
		resumeBackgroundMusic();
	}
}
