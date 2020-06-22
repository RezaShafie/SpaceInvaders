#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__



#include "cocos2d.h"
#include "GameplayLayer.h"
#include "HudLayer.h"
#include "ScrollingBgLayer.h"
#include "MainMenuScene.h"


using namespace cocos2d;

class HelloWorld : public cocos2d::CCLayer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
    
       
    // implement the "static node()" method manually
    CREATE_FUNC(HelloWorld);

	//update function
	virtual void update(float delta);

	//touch methods
	virtual void ccTouchesBegan(CCSet* pTouches, CCEvent* event);
	virtual void ccTouchesMoved(CCSet* pTouches, CCEvent* event);
	virtual void ccTouchesEnded(CCSet* pTouches, CCEvent* event);
	
	void SpawnEnemies(float dt);

	

	void FireLaser(CCObject *pSender);

	void GameOver();

	void GamePaused();
	void GameResumed();

	void PlayAnimation(CCSprite* sprite, char* firstSprite, char* pngImage, char* plistFile, char* spriteName_numbered, int spriteCount,float speed = 0.1f);

	void MainMenuScene(CCObject *pSener);
	// ------------------------------  Variables  ----------------------------
	CCSize visibleSize;
	CCSprite *spaceship;
	
	GameplayLayer *gameplayLayer;
	CCLabelBMFont *scoreLabel;
	HudLayer *hudLayer;

	ScrollingBgLayer *scrollingBgLayer;

	
};

#endif // __HELLOWORLD_SCENE_H__
