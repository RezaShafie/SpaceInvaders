#include "ScrollingBackground.h"

ScrollingBackground* ScrollingBackground::Create(string _name, float _speed, float _yPos)
{
	ScrollingBackground* ob = new ScrollingBackground();
	if (ob && ob->InitScrollingBackground(_name, _speed, _yPos))
	{
		ob->autorelease();
		return ob;
	}
	CC_SAFE_DELETE(ob);
	return NULL;
}

bool ScrollingBackground::InitScrollingBackground(string _name, float _speed, float _yPos)
{
	winSize = CCDirector::sharedDirector()->getWinSize();
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();

	speed = _speed;
	gameBg1 = CCSprite::create(_name.c_str());
	gameBg1->setPosition(ccp(winSize.width, winSize.height*0.01));
	gameBg1->setAnchorPoint(ccp(0.5, 0.0));
	gameBg1->setScaleX(1.01);
	addChild(gameBg1);
	gameBg2 = CCSprite::create(_name.c_str());
	gameBg2->setPosition(ccp(winSize.width, _yPos));
	gameBg2->setAnchorPoint(ccp(0.5, 0.0));
	gameBg2->setScaleX(1.01);
	addChild(gameBg2);
	return true;
}

void ScrollingBackground::Update()
{
	// scroll bg up or down
	CCPoint bg1pos = gameBg1->getPosition();
	gameBg1->setPosition(ccp(bg1pos.x, bg1pos.y - speed));

	if (gameBg1->getPosition().y < -winSize.height / 2)
		gameBg1->setPosition(ccp(winSize.width + winSize.width / 2, gameBg1 ->
		getPosition().y));

	CCPoint bg2pos = gameBg2->getPosition();
	//changing the y position
	gameBg2->setPosition(ccp(bg2pos.x, bg2pos.y-speed));

	if (gameBg2->getPosition().y < -winSize.height / 2)
		gameBg2->setPosition(ccp(winSize.width + winSize.width / 2, gameBg2 ->
		getPosition().y));
}
