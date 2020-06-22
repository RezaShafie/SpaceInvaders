#include "HudLayer.h"
#include "HelloWorldScene.h"




HudLayer::HudLayer()
{
	visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	//moved the score label to the center
	scoreLabel = CCLabelBMFont::create("Score: 0", "invaderFont.fnt");
	scoreLabel->setPosition(ccp(visibleSize.width * 0.9,
		visibleSize.height * 0.95));
	addChild(scoreLabel, 10);
	scoreLabel->setScale(0.15);

	CCMenuItemImage *pauseItem = CCMenuItemImage::create
		("PauseButton.png", "PauseButtonPressed.png", this, menu_selector(HudLayer::PauseGame));;
	pauseItem->setScale(0.1);
	pauseItem->setPosition(ccp(visibleSize.width *0.05,visibleSize.height *0.91));

	pauseMenu = CCMenu::create(pauseItem, NULL);
	pauseMenu->setPosition(CCPointZero);
	addChild(pauseMenu);
}


HudLayer::~HudLayer()
{
}

void HudLayer::UpdateScore(int score)
{
	char scoreTxt[100];
	sprintf(scoreTxt, "Score: %d", score);
	scoreLabel->setString(scoreTxt);
}

void HudLayer::PauseGame(CCObject* pSender)
{
	HelloWorld *hello_world = (HelloWorld*)getParent();
	if (!hello_world->gameplayLayer->gameOver)
	{
		pauseMenu->setTouchEnabled(false);

		//resume game
		CCMenuItemImage* resumeItem =
			CCMenuItemImage::create("RefreshButton.png",
			"RefreshButtonPressed.png", this,
			menu_selector(HudLayer::ResumeGame));
		resumeItem->setScale(0.18);
		resumeItem->setPosition(ccp(visibleSize.width * 0.7,
			visibleSize.height* 0.6));

		//back to main menu
		CCMenuItemImage *mainmenuItem =
			CCMenuItemImage::create("HomeButton.png",
			"HomeButtonPressed.png", this,
			menu_selector(HelloWorld::MainMenuScene));
		mainmenuItem->setPosition(ccp(visibleSize.width *0.3, visibleSize.height * 0.6));

		resumeMenu = CCMenu::create(resumeItem,mainmenuItem, NULL);
		resumeMenu->setPosition(CCPointZero);
		this->addChild(resumeMenu);
		hello_world->GamePaused();

	}
}

void HudLayer::ResumeGame(CCObject* pSender)
{
	pauseMenu->setTouchEnabled(true);
	this->removeChild(resumeMenu);
	HelloWorld* helloWorld = (HelloWorld*)this->getParent();
	helloWorld->GameResumed();
}
