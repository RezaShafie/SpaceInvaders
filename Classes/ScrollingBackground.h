#ifndef SPACE_INVADERS_SCROLLING_BACK_GROUND
#define SPACE_INVADERS_SCROLLING_BACK_GROUND
#include <iostream>
#include "cocos2d.h"
using namespace std;
using namespace cocos2d;
class ScrollingBackground : public CCNode
{
public:
	static ScrollingBackground* Create(string name, float _speed, float _yPos);
	bool InitScrollingBackground(string _name, float _speed, float _yPos);
	void Update();

	//------------------------  Variables  -------------------------
	CCSprite* gameBg1, *gameBg2;
	float speed;
	string name;
	CCSize winSize;

};
#endif /* defined(SPACE_INVADERS_SCROLLING_BACK_GROUND) */