#ifndef SPACE_INVADERS_BOSS
#define SPACE_INVADERS_BOSS
#pragma once
#include "cocos2d.h"
#include "HelloWorldScene.h"
using namespace cocos2d;
class Boss : public CCSprite
{
public:
	Boss(void);
	~Boss(void);
	static Boss* CreateBoss(GameplayLayer* _gamplayLayer);
	bool initUfo();
	bool initSkull();
	void ufoUpdate();
	void MoveRight();
	void MoveLeft();
	bool createEnemies(GameplayLayer* _gameplayLayer);
	void UpdateEnemy();
	void Shoot(float dt);

	//--------------  Variables -------------------
	HelloWorld *helloWorld;
	bool isLeft;
	GameplayLayer *gameplayLayer;

	CCSize visibleSize;
};
#endif