#include "Boss.h"
#include "Projectile.h"


Boss::Boss()
{
	helloWorld = new HelloWorld();
	isLeft = true;
	visibleSize = CCDirector::sharedDirector()->getVisibleSize();
}


Boss::~Boss(){}

Boss* Boss::CreateBoss(GameplayLayer* _gamplayLayer)
{
	Boss* ob = new Boss();
	if (ob && ob->createEnemies(_gamplayLayer))
	{
		ob->autorelease();
		return ob;
	}
	CC_SAFE_DELETE(ob);
	return nullptr;
}



bool Boss::initUfo()
{ 
	initWithFile("ufo1.png");
	setPosition(ccp(visibleSize.width*0.2, visibleSize.height*0.8));
	setScale(0.75);

	helloWorld->PlayAnimation(this, "ufo1.png", "enemiesAnimation.png", "enemiesAnimation.plist", "ufo%.png", 4, 0.5);

	return true;
}

bool Boss::initSkull()
{
	return true;
}

void Boss::ufoUpdate()
{
	if (isLeft)
	{
		MoveRight();
		if (getPosition().x >= visibleSize.width*0.8)
			isLeft = false;
	}
	if (!isLeft)
	{
		MoveLeft();
		if (getPosition().x <= visibleSize.width*0.2)
			isLeft = true;
	}

}

void Boss::MoveRight()
{
	CCMoveBy *moveRight = CCMoveBy::create(2, ccp(2, 0));
	runAction(moveRight);
}

void Boss::MoveLeft()
{
	CCMoveBy *moveLeft = CCMoveBy::create(2, ccp(-2, 0));
	runAction(moveLeft);
}

bool Boss::createEnemies(GameplayLayer* _gameplayLayer)
{
	gameplayLayer = _gameplayLayer;
	initWithFile("crab1.png");
	setPosition(ccp(visibleSize.width*0.2, visibleSize.height*0.8));
	setScale(0.75);

	helloWorld->PlayAnimation(this, "crab1.png", "enemiesAnimation.png", "enemiesAnimation.plist", "crab%.png", 2, 0.5);
	return true;
}

void Boss::UpdateEnemy()
{
	CCMoveBy *moveDown = CCMoveBy::create(1, ccp(0, -0.01));
	runAction(moveDown);
}

void Boss::Shoot(float dt)
{
	CCPoint p = this->getPosition();
	p.y = p.y - this->getContentSize().height / 4;
	p.x = p.x - this->getContentSize().width * 0.02;
	Projectile* pr = Projectile::CreateProjectile(p, 1);
	gameplayLayer->addChild(pr);
	gameplayLayer->GetEnemyBulletsArray()->addObject(pr);
}
