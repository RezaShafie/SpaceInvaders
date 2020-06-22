#include "Enemy.h"
#include "HelloWorldScene.h"
#include "Projectile.h"
#include "SimpleAudioEngine.h"


Enemy::Enemy()
{
	helloWorld = new HelloWorld();
	projectile = new Projectile();
}


Enemy::~Enemy()
{
}

Enemy* Enemy::CreateEnemy(GameplayLayer* _gameplayLayer)
{
	Enemy* ob = new Enemy();
	
		if (ob && ob->InitEnemy(_gameplayLayer))
		{
			ob->autorelease();
			return ob;
		}
	
	CC_SAFE_DELETE(ob);
	return NULL;
}


bool Enemy::InitEnemy(GameplayLayer *_gameplayLayer)
{
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();

	gameplayLayer = _gameplayLayer;
	projectile = new Projectile();

	
	
	int count = 2;
	//Calls enemies shoot method(Shoot)
	schedule(schedule_selector(Enemy::Shoot), 2);
	
		float mrand = rand() % 5 + 2;
		//CCLOG("random height %f", mrand);
		float w = visibleSize.width * mrand * 0.15;
		char* firstSprite;
		char *numberedName;

		int enemyNo = rand() % 6;
		switch (enemyNo)
		{
		case 0:
			firstSprite = "crab1.png";
			numberedName = "crab%d.png";
			break;
		case 1:
			firstSprite = "cockroach1.png";
			numberedName = "cockroach%d.png";
			break;
		case 2:
			firstSprite = "locust1.png";
			numberedName = "locust%d.png";
			break;
		case 3:
			firstSprite = "octopus1.png";
			numberedName = "octopus%d.png";
			break;
		case 4:
			firstSprite = "pounder1.png";
			numberedName = "pounder%d.png";
			break;
		case 5:
			firstSprite = "shapeShifter1.png";
			numberedName = "shapeShifter%d.png";
			break;
		default:
			firstSprite = "crab1.png";
			numberedName = "crab%d.png";
			break;
		}
		
	
	

	initWithFile(firstSprite);
	CCPoint p = ccp(w, visibleSize.height + this->getContentSize().height / 2);
	setPosition(p);
	setScale(0.5);
	//enemies animation
	helloWorld->PlayAnimation(this, firstSprite, "enemiesAnimation.png", "enemiesAnimation.plist", numberedName, 2,0.8f);
	return true;
}


void Enemy::Update()
{
	CCPoint _mp = this->getPosition();
	//CCPoint _Mp = ccpAdd(_mp, ccp(0, -5));//0,-0.5

	
	CCMoveBy *moveDown = CCMoveBy::create(3, ccp(0,-1));
	CCMoveBy *moveLeft = CCMoveBy::create(3, ccp(-1, 0));
	CCMoveBy *moveRight = CCMoveBy::create(3, ccp(1,0));
	CCEaseOut *easeDown = CCEaseOut::create(moveDown,0.8);
	CCEaseOut *easeLeft = CCEaseOut::create(moveLeft,1);
	CCEaseOut *easeRight = CCEaseOut::create(moveRight, 1);
	CCSequence *seq = CCSequence::create(easeDown, easeLeft, easeRight,easeDown , NULL);
	runAction(seq);

	//this->setPosition(_Mp);
}


void Enemy::Shoot(float dt)
{
	
	//CCLog("[Enemy] shoot");
	CCPoint p = this->getPosition();
	p.y = p.y - this->getContentSize().height / 4;
	p.x = p.x - this->getContentSize().width * 0.02;
	Projectile* pr = Projectile::CreateProjectile(p, 1);
	gameplayLayer->addChild(pr);
	gameplayLayer->GetEnemyBulletsArray()->addObject(pr);
}


