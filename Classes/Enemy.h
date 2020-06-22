#ifndef SPACE_INVADERS_ENEMY_
#define SPACE_INVADERS_ENEMY_
#pragma once
#include "cocos2d.h"
#include "GameplayLayer.h"
#include "HelloWorldScene.h"
#include "Projectile.h"
using namespace cocos2d;

class Enemy : public CCSprite
{
public:
	Enemy(void);
	~Enemy(void);
	static Enemy* CreateEnemy(GameplayLayer *_gameplayLayer);
	bool InitEnemy(GameplayLayer *_gameplayLayer);
	void Shoot(float dt);
	void Update();
	//-----------------------  Variables  ------------------------------
	HelloWorld *helloWorld;
	GameplayLayer *gameplayLayer;
	Projectile *projectile;
	
};

#endif