#ifndef SPACE_INVADERS_PROJECTILE
#define SPACE_INVADERS_PROJECTILE
#pragma once
#include "cocos2d.h"
using namespace cocos2d;
class Projectile : public CCSprite
{
public:
	Projectile(void);
	~Projectile(void);
	static Projectile* CreateProjectile(CCPoint p, int _type);
	bool InitProjectile(CCPoint p, int _type);
	void Update();


	//------------------  Variables  -----------------------
	int type;
	int bulletType;
};
#endif