#include "ScrollingBgLayer.h"

ScrollingBgLayer::ScrollingBgLayer(float speed)
{
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();

	//background
	CCSprite* bg = CCSprite::create("blackBg.jpg");
	bg->setPosition(ccp(visibleSize.width* 0.5, visibleSize.height * 0.5));
	addChild(bg, -1);

	space = ScrollingBackground::Create("stars.png", speed*0.5, visibleSize.width * 0.5);
	addChild(space);
}

ScrollingBgLayer::~ScrollingBgLayer(){}

void ScrollingBgLayer::Update()
{
	space->Update();

}
