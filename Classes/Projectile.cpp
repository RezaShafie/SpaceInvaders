#include "Projectile.h"
#include "SimpleAudioEngine.h"

Projectile::Projectile(void)
{
	bulletType = 0;
	type = 0;
}
Projectile::~Projectile(void){}

Projectile* Projectile::CreateProjectile(CCPoint p, int _type)
{
	Projectile* ob = new Projectile();
	if (ob && ob->InitProjectile(p, _type))
	{
		ob->autorelease();
		return ob;
	}
	CC_SAFE_DELETE(ob);
	return NULL;
}

bool Projectile::InitProjectile(CCPoint p, int _type)
{
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	type = _type;
	if (type == 1)
	{
		bulletType = rand() % 3;
		switch (bulletType)
		{
			case 0:
				initWithFile("enemyLaser1.png");

				CocosDenshion::SimpleAudioEngine::sharedEngine() ->
					playEffect("sounds/enemyLaser1.ogg");
				break;;
			case 1:
				initWithFile("enemyLaser2.png");

				CocosDenshion::SimpleAudioEngine::sharedEngine() ->
					playEffect("sounds/enemyLaser2.ogg");
				break;;
			case 2:
				initWithFile("enemyLaser3.png");

				CocosDenshion::SimpleAudioEngine::sharedEngine() ->
					playEffect("sounds/enemyLaser3.ogg");
				break;
			default:
				initWithFile("enemyLaser3.png");

				CocosDenshion::SimpleAudioEngine::sharedEngine() ->
					playEffect("sounds/enemyLaser3.ogg");
				break;

		}
		
	}
	else if (type == 2)
	{
		initWithFile("laser.png");
	}
	this->setPosition(p);
	return true;
}

void Projectile::Update()
{
	if (type == 1)
	{
		CCPoint _mp = this->getPosition();
		CCPoint _Mp = ccpAdd(_mp, ccp(0, -2));
		this->setPosition(_Mp);
		/*CCMoveBy *moveBy = CCMoveBy::create(1, ccp(0, -0.75));
		CCEaseOut *easeOut = CCEaseOut::create(moveBy,0.5);
		runAction(easeOut);*/
	}
	else if (type == 2)
	{
		CCPoint _mp = this->getPosition();
		CCPoint _Mp = ccpAdd(_mp, ccp(0, 5));//was 5
		this->setPosition(_Mp);
	}
}

