#include "GameplayLayer.h"
#include "Enemy.h"
#include "Projectile.h"
#include "HelloWorldScene.h"


GameplayLayer::GameplayLayer(CCSprite *_spaceship, bool _infiniteMode)
{
	spaceship = _spaceship;
	
	enemies = new CCArray();
	enemiesToBeDeleted = new CCArray();
	enemyBullets = new CCArray();
	enemyBulletsToBeDeleted = new CCArray();
	spaceshipLasers = new CCArray();

	score = 0;
	gameOver = false;

	infiniteMode = _infiniteMode;

	visibleSize = CCDirector::sharedDirector()->getVisibleSize();
}
GameplayLayer::~GameplayLayer(){}
void GameplayLayer::Update()
{
	
	if (infiniteMode)
	{

		//enemies deletion
		if (enemies->count() >= 0)
		{
			for (int i = 0; i < enemies->count(); i++)
			{
				Enemy* e = (Enemy*)enemies->objectAtIndex(i);

				e->Update();

				//game over if enemy is out of boundries
				if (e->getPositionY() + e->getContentSize().height / 2 < 0)
				{
					gameOver = true;
					enemiesToBeDeleted->addObject(e);
				}
			}
		}
		//enemy bullets
		if (enemyBullets->count() > 0)
		{
			for (int i = 0; i < enemyBullets->count(); i++)
			{
				Projectile* pr = (Projectile*)enemyBullets->objectAtIndex(i);
				pr->Update();
				if (pr->getPositionX() <= 0)
				{
					enemyBulletsToBeDeleted->addObject(pr);
				}
			}
		}
		CCObject* eb = NULL;
		CCARRAY_FOREACH(enemyBulletsToBeDeleted, eb)
		{
			Projectile *target = (Projectile*)(eb);
			enemyBullets->removeObject(target);
			enemyBulletsToBeDeleted->removeObject(target);
			this->removeChild(target, true);
		}

		CCObject* ee = NULL;
		CCARRAY_FOREACH(enemiesToBeDeleted, ee)
		{
			Enemy *target = (Enemy*)(ee);
			enemies->removeObject(target);
			enemiesToBeDeleted->removeObject(target);
			this->removeChild(target, true);
		}
		//player bullets
		if (spaceshipLasers->count() >= 0)
		{
			for (int i = 0; i < spaceshipLasers->count(); i++)
			{
				Projectile* p = (Projectile*)spaceshipLasers->objectAtIndex(i);
				p->Update();
				if (p->getPositionX() >= visibleSize.width)
				{
					this->removeChild(p);
					spaceshipLasers->removeObject(p);
				}
			}
		}
		//laser and enemies collision
		if (spaceshipLasers->count() >= 0)
		{
			for (int i = 0; i<spaceshipLasers->count(); i++)
			{
				Projectile* p = (Projectile*)spaceshipLasers->objectAtIndex(i);
				if (enemies->count() > 0)
				{
					for (int j = 0; j < enemies->count(); j++)
					{
						Enemy* en = (Enemy*)enemies->objectAtIndex(j);
						if (CheckCollision(p, en))
						{
							score += 2;

							this->removeChild(p);
							spaceshipLasers->removeObject(p);

							enemiesToBeDeleted->addObject(en);
							return;
						}
					}
				}
			}
		}

		//enemy lasers and spaceship collision
		if (enemyBullets->count() > 0)
		{
			for (int i = 0; i < enemyBullets->count(); i++)
			{
				Projectile* pr = (Projectile*)enemyBullets->objectAtIndex(i);
				if (CheckCollision(pr, spaceship))
				{
					enemyBulletsToBeDeleted->addObject(pr);
					gameOver = true;

					return;
				}
			}
		}
	}
	
	
	
}
CCArray* GameplayLayer::GetEnemiesArray()
{
	return enemies;
}

CCArray* GameplayLayer::GetEnemyBulletsArray()
{
	return  enemyBullets;
}

CCArray* GameplayLayer::GetSpaceshipLasersArray()
{
	return spaceshipLasers;
}

bool GameplayLayer::CheckCollision(CCSprite* sprite1, CCSprite* sprite2)
{
	CCRect sprite1_bb = sprite1->boundingBox();
	CCRect sprite2_bb = sprite2->boundingBox();

	return sprite1_bb.intersectsRect(sprite2_bb);
}


