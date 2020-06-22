#include "MainMenuScene.h"
#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "MainScene.h"

using namespace std;

#pragma execution_character_set("utf-8")

bool MainMenu::init()
{
	scrollingBgLayer = new ScrollingBgLayer(0.5f);

	
	CCSize visibleSize =
		CCDirector::sharedDirector()->getVisibleSize();
	CCPoint origin =
		CCDirector::sharedDirector()->getVisibleOrigin();

	this->addChild(scrollingBgLayer);

	//check if background music needs to be played
	bool isPaused = CCUserDefault::sharedUserDefault() ->
	getBoolForKey("soundPaused");
	if (isPaused)
	{
		CocosDenshion::SimpleAudioEngine::sharedEngine() ->
		pauseBackgroundMusic();
	}
	else
	{
		CocosDenshion::SimpleAudioEngine::sharedEngine() ->
		resumeBackgroundMusic();
	}

	/*CCLabelBMFont *space_label =
		CCLabelBMFont::create("Space", "MainFont.fnt");*/
	CCLabelTTF *space_label = CCLabelTTF::create("مهاجمان", "fonts/A Pixel.ttf", 70);

	ccColor3B color;
	color.b = 0;
	color.g = 0;
	color.r = 0;
		//space_label->setFontFillColor(color);

	space_label->setPosition(ccp(visibleSize.width / 2,
		visibleSize.height * 0.89));/*visibleSize.width / 2,
		visibleSize.height * 0.89);*/

	space_label->setRotationX(-20);
	
	/*CCLabelBMFont *invaders_label =
		CCLabelBMFont::create("Invaders", "MainFont.fnt");*/
	CCLabelTTF *invaders_label = CCLabelTTF::create("فضايی", "fonts/A Pixel.ttf", 70);
	
	invaders_label->setPosition(ccp(visibleSize.width / 2,
		visibleSize.height * 0.7));
	invaders_label->setRotationX(20);

	addChild(space_label);
	addChild(invaders_label);

	//buttons
	CCMenuItemImage *pPlayItem =
		CCMenuItemImage::create("PlayButton.png", "PlayButtonPressed.png",
		this, menu_selector(MainMenu::PlayInfiniteMode));
	pPlayItem->setPosition(ccp(visibleSize.width * 0.4, visibleSize.height * 0.4));
	pPlayItem->setScale(0.2);

	

	CCMenuItemImage *pOptionsItem =
		CCMenuItemImage::create("OptionsButton.png",
		"OptionsButtonPressed.png", this, menu_selector(MainMenu::OptionsScene));
	pOptionsItem->setPosition(ccp(visibleSize.width * 0.6, visibleSize.height
		* 0.4));

	// create menu, it's an autorelease object
	CCMenu* pMenu = CCMenu::create(pOptionsItem, pPlayItem, NULL);
	pMenu->setPosition(CCPointZero);
	this->addChild(pMenu, 10);

	//highscore labels
	CCLabelBMFont* newHighScoreLabel =
		CCLabelBMFont::create("CURRENT HIGH SCORE", "invaderFont.fnt");
	newHighScoreLabel->setPosition(ccp(visibleSize.width * 0.5,
		visibleSize.height * 0.15));
	//highscore
	CCLabelBMFont* highScoreLabel = CCLabelBMFont::create("0",
		"invaderFont.fnt");
	highScoreLabel->setPosition(ccp(visibleSize.width * 0.5, visibleSize.height
		* 0.1));
	this->addChild(highScoreLabel, 10);
	highScoreLabel->setScale(0.5);
	int highScore = CCUserDefault::sharedUserDefault() ->
	getIntegerForKey("GameHighScore");
	char scoreTxt[100];
	sprintf(scoreTxt, "%d", highScore);
	highScoreLabel->setString(scoreTxt);

	scheduleUpdate();

	return true;
}

void MainMenu::update(float dt)
{
	scrollingBgLayer->Update();
}

CCScene* MainMenu::scene()
{
	CCScene *scene = CCScene::create();
	MainMenu *layer = MainMenu::create();
	scene->addChild(layer);
	return scene;
}

void MainMenu::OptionsScene(CCObject* pSender)
{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sounds/MenuTap.ogg");

	CCScene *mScene = OptionsMenu::scene();
	CCDirector::sharedDirector()->replaceScene(mScene);
}

void MainMenu::PlayInfiniteMode(CCObject* pSender)
{
	bool isPaused = CCUserDefault::sharedUserDefault() ->
		getBoolForKey("soundPaused");
	if (isPaused)
	{
		//CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sounds/MenuTap.ogg");

		CocosDenshion::SimpleAudioEngine::sharedEngine()->
			pauseBackgroundMusic();
	}
	else
	{
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sounds/MenuTap.ogg");

		CocosDenshion::SimpleAudioEngine::sharedEngine()->
			playBackgroundMusic("sounds/level1.ogg", true);
	}
	
	

	CCScene *mScene = HelloWorld::scene();
	CCDirector::sharedDirector()->replaceScene(mScene);
}
