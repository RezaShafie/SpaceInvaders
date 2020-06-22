#ifndef SPACE_INVADERS_HUD_LAYER
#define SPACE_INVADERS_HUD_LAYER
#pragma once
#include "cocos2d.h"
using namespace cocos2d;
class HelloWorldScene;

class HudLayer : public CCLayer
{
public:
	HudLayer(void);
	~HudLayer(void);
	void UpdateScore(int score);

	void PauseGame(CCObject *pSender);
	void ResumeGame(CCObject *pSender);

	//-------------------------  Variables  ------------------------
	CCSize visibleSize;
	CCLabelBMFont* scoreLabel;
	CCMenu *pauseMenu;
	CCMenu *resumeMenu;
};
#endif