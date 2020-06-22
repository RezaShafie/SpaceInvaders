#ifndef SPACE_INVADERS_OPTIONS_SCENE
#define SPACE_INVADERS_OPTIONS_SCENE
#include "cocos2d.h"
#include "ScrollingBgLayer.h"
using namespace cocos2d;
class OptionsMenu : public cocos2d::CCLayer
{
public:
    virtual bool init();  
    static cocos2d::CCScene* scene();
    void update(float dt);
    void MainMenu(CCObject* pSender);
    CREATE_FUNC(OptionsMenu);
	void SoundControl(CCObject *pSender);
	
	// --------------  Variables  --------------------
	ScrollingBgLayer* scrollingBgLayer;

	CCMenuItemImage *soundOn;
	CCMenuItemImage *soundOff;
};
#endif