#ifndef SPACE_INVADERS_GAMEPLAY_LAYER_
#define SPACE_INVADERS_GAMEPLAY_LAYER_

#include "cocos2d.h"
using namespace cocos2d;

class GameplayLayer : public CCLayer
{
public:
	GameplayLayer(CCSprite *_spaceship, bool _infiniteMode = true);
	~GameplayLayer();
	void Update();
	CCArray *GetEnemiesArray();
	CCArray* GetEnemyBulletsArray();
	CCArray *GetSpaceshipLasersArray();
	bool CheckCollision(CCSprite *sprite1, CCSprite *sprite2);

	//-------------  Variables  -----------------
	CCArray *enemiesToBeDeleted;
	CCArray* enemyBullets;
	CCArray* enemyBulletsToBeDeleted;
	CCSprite *spaceship;

	int score;
	bool gameOver;
	bool infiniteMode;

private:
	


	//-------------  Variables  -----------------
	CCSize visibleSize;
	CCArray *enemies;
	CCArray *spaceshipLasers;
	
};
#endif /* defined(SPACE_INVADERS_GAMEPLAY_LAYER_) */