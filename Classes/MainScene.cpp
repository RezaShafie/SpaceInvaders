#include "MainScene.h"

#include "cocos2d.h"
#include "ScrollingBgLayer.h"
#include "SimpleAudioEngine.h"
#include "Projectile.h"
#include "Enemy.h"
#include "Boss.h"

cocos2d::CCScene* MainScene::scene()
{
	CCScene *scene = CCScene::create();
	MainScene *layer = MainScene::create();
	scene->addChild(layer);
	return scene;
}

MainScene::MainScene()
{
	helloWorld = new HelloWorld();

	
}


MainScene::~MainScene()
{
}

bool MainScene::init()
{
	visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

	//enabling touch function
	setTouchEnabled(true);

	//adding background
	scrollingBgLayer = new ScrollingBgLayer(0.5f);
	addChild(scrollingBgLayer);

	//spaceship
	spaceship = CCSprite::create("spaceship0.png");
	spaceship->setPosition(ccp(visibleSize.width * 0.5, visibleSize.height *
		0.1));
	addChild(spaceship, 5);

	//spaceship animation
	helloWorld->PlayAnimation(spaceship, "spaceship1.png", "spaceship.png", "spaceship.plist", "spaceship%d.png", 3);


	//adding gameplay layer
	gameplayLayer = new GameplayLayer(spaceship,false);
	this->addChild(gameplayLayer);
	Boss* b	= Boss::CreateBoss(gameplayLayer);
	gameplayLayer->addChild(b);
	b->Shoot(5);

	//shoot button
	CCMenuItemImage *pshootItem = CCMenuItemImage::create("laserButton.png",
		"laserButtonPressed.png", this, menu_selector(MainScene::FireLaser));
	pshootItem->setPosition(ccp(visibleSize.width * 0.09,
		visibleSize.height * 0.15));
	pshootItem->setScale(0.25);
	CCMenu *pMenu = CCMenu::create(pshootItem, NULL);
	pMenu->setPosition(CCPointZero);
	addChild(pMenu, 1);


	//HudLayer
	hudLayer = new HudLayer();
	addChild(hudLayer, 15);

	//schedule update
	scheduleUpdate();

	return true;
}


void MainScene::update(float dt)
{
	if (!gameplayLayer->gameOver)
	{


		gameplayLayer->Update();
		this->schedule(schedule_selector(MainScene::SpawnEnemies), 1);
		scrollingBgLayer->Update();
		hudLayer->UpdateScore(gameplayLayer->score);


	}
	else
		GameOver();
}

void MainScene::ccTouchesMoved(CCSet* pTouches, CCEvent* event)
{
	CCTouch* touch = (CCTouch*)pTouches->anyObject();

	CCPoint location = touch->getLocationInView();
	location = CCDirector::sharedDirector()->convertToGL(location);


	CCMoveTo * actionMove = CCMoveTo::create(95555, location);
	CCEaseOut *easeOut = CCEaseOut::create(actionMove, 5);
	spaceship->runAction(easeOut);
}

void MainScene::FireLaser(CCObject* pSender)
{
	CCPoint p = spaceship->getPosition();

	p.x = p.x - spaceship->getContentSize().width * 0.01;
	p.y = p.y + spaceship->getContentSize().height* 0.5;

	Projectile* laser = Projectile::CreateProjectile(p, 2);

	CocosDenshion::SimpleAudioEngine::sharedEngine()->
		playEffect("sounds/spaceshipLaser.ogg");

	gameplayLayer->addChild(laser);

	gameplayLayer->GetSpaceshipLasersArray()->addObject(laser);
}

//void HelloWorld::ccTouchesMoved(CCSet* pTouches, CCEvent* event)
//{
//	if (!gameplayLayer->gameOver)//stopping the spaceship movement in case of game over
//	{
//		
//	}
//
//}

void MainScene::SpawnEnemies(float dt)
{

	Enemy* e = Enemy::CreateEnemy(gameplayLayer);
	gameplayLayer->addChild(e);
	gameplayLayer->GetEnemiesArray()->addObject(e);
}
void MainScene::GameOver()
{
	//spaceship explosion
	CCParticleSystemQuad *explosion = CCParticleSystemQuad::create("explosion.plist");
	explosion->setPosition(spaceship->getPosition());
	removeChild(spaceship);
	explosion->setScale(0.2);
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sounds/explosion.ogg");
	addChild(explosion);
	explosion->setAutoRemoveOnFinish(true);


	CCLabelBMFont *gameoverLabel = CCLabelBMFont::create("GOTCHA", "GameOverFont.fnt");

	gameoverLabel->setPosition(ccp(visibleSize.width * 0.5, visibleSize.height
		* 0.7));
	addChild(gameoverLabel, 10);

	unscheduleAllSelectors();

	if (gameplayLayer->GetEnemiesArray()->count() >0)
	{
		for (int i = 0; i< gameplayLayer->GetEnemiesArray()->count(); i++)
		{
			Enemy* en = (Enemy*)gameplayLayer->GetEnemiesArray()
				->objectAtIndex(i);
			en->unscheduleAllSelectors();
		}
	}
	int highScore = CCUserDefault::sharedUserDefault()->getIntegerForKey("GameHighScore");
	if (gameplayLayer->score > highScore)
	{
		CCUserDefault::sharedUserDefault() ->
			setIntegerForKey("GameHighScore", gameplayLayer->score);
		CCUserDefault::sharedUserDefault()->flush();
		CCLabelBMFont* newHighScoreLabel = CCLabelBMFont::create(
			"NEW HIGHSCORE", "invaderFont.fnt");
		newHighScoreLabel->setPosition(ccp(visibleSize.width * 0.5,
			visibleSize.height * 0.45));
		this->addChild(newHighScoreLabel, 10);
		newHighScoreLabel->setScale(0.5);
		CCLabelBMFont* gOscoreLabel = CCLabelBMFont::create("0",
			"invaderFont.fnt");
		gOscoreLabel->setPosition(ccp(visibleSize.width * 0.5,
			visibleSize.height * 0.4));
		this->addChild(gOscoreLabel, 10);
		gOscoreLabel->setScale(0.75);
		char scoreTxt[100];
		sprintf(scoreTxt, "%d", gameplayLayer->score);
		gOscoreLabel->setString(scoreTxt);
	}
	else
	{
		CCLabelBMFont* newHighScoreLabel = CCLabelBMFont::create
			("Try Harder", "invaderFont.fnt");
		newHighScoreLabel->setPosition(ccp(visibleSize.width * 0.5,
			visibleSize.height * 0.45));
		this->addChild(newHighScoreLabel, 10);
		newHighScoreLabel->setScale(0.75);
	}
	//back to main menu
	CCMenuItemImage *mainmenuItem =
		CCMenuItemImage::create("HomeButton.png",
		"HomeButtonPressed.png", this,
		menu_selector(MainScene::MainMenuScene));
	mainmenuItem->setPosition(ccp(visibleSize.width *0.4, visibleSize.height *
		0.2));

	CCMenuItemImage *playmenuItem =
		CCMenuItemImage::create("PlayButton.png",
		"PlayButtonPressed.png", this,
		menu_selector(MainMenu::PlayInfiniteMode));
	playmenuItem->setPosition(ccp(visibleSize.width *0.6, visibleSize.height *
		0.2));
	playmenuItem->setScale(0.2);
	CCMenu *mainMenu = CCMenu::create(mainmenuItem, playmenuItem, NULL);
	mainMenu->setPosition(CCPointZero);
	this->addChild(mainMenu);
}

void MainScene::GamePaused()
{
	this->unscheduleUpdate();
	this->unschedule(schedule_selector(MainScene::SpawnEnemies));
	if (gameplayLayer->GetEnemiesArray()->count() >0)
	{
		for (int i = 0; i< gameplayLayer->GetEnemiesArray()->count(); i++)
		{
			Enemy* en = (Enemy*)gameplayLayer->GetEnemiesArray() ->
				objectAtIndex(i);
			en->pauseSchedulerAndActions();
		}
	}
}

void MainScene::GameResumed()
{
	this->scheduleUpdate();
	this->schedule(schedule_selector(MainScene::SpawnEnemies), 3.0);
	if (gameplayLayer->GetEnemiesArray()->count() >0)
	{
		for (int i = 0; i< gameplayLayer->GetEnemiesArray()->count(); i++)
		{
			Enemy* en = (Enemy*)gameplayLayer->GetEnemiesArray() ->
				objectAtIndex(i);
			en->resumeSchedulerAndActions();
		}
	}
}
void MainScene::MainMenuScene(CCObject* pSener)
{
	bool isPaused = CCUserDefault::sharedUserDefault() ->
		getBoolForKey("soundPaused");
	if (!isPaused)
		CocosDenshion::SimpleAudioEngine::sharedEngine()->
		playBackgroundMusic("sounds/MainMenu.ogg");

	CCScene *mScene = MainMenu::scene();
	CCDirector::sharedDirector()->replaceScene(mScene);
}

