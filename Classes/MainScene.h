#ifndef SPACE_INVADERS_MAIN_SCENE
#define SPACE_INVADERS_MAIN_SCENE
#include "cocos2d.h"
#include "ScrollingBgLayer.h"
#include "HelloWorldScene.h"


using namespace cocos2d;
class MainScene: public cocos2d::CCLayer
{
public:
	MainScene();
	~MainScene();
	virtual bool init();
	static cocos2d::CCScene* scene();
	void update(float dt);
	CREATE_FUNC(MainScene);

	virtual void ccTouchesMoved(CCSet* pTouches, CCEvent* event);
	void FireLaser(CCObject *pSender);
	void SpawnEnemies(float dt);
	void GameOver();
	void GamePaused();
	void GameResumed();
	void MainMenuScene(CCObject* pSener);
	//------------- Variables ------------------
	ScrollingBgLayer *scrollingBgLayer;
	CCSize visibleSize;
	CCSprite *spaceship;

	HelloWorld *helloWorld;
	GameplayLayer *gameplayLayer;
	HudLayer *hudLayer;

};
#endif