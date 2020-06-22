#ifndef SPACE_INVADERS_MAIN_MENU_SCENE
#define SPACE_INVADERS_MAIN_MENU_SCENE
#include "cocos2d.h"
#include "ScrollingBgLayer.h"
#include "OptionsScene.h"
using namespace cocos2d;
class MainMenu : public cocos2d::CCLayer
{
public:
	virtual bool init();
	void OptionsScene(CCObject* pSender);
	void PlayInfiniteMode(CCObject* pSender);
	
	void update(float dt);
	static cocos2d::CCScene* scene();
	CREATE_FUNC(MainMenu);
	

	//-------------------- Variables  ------------------
	ScrollingBgLayer* scrollingBgLayer;
};
#endif