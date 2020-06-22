#ifndef SPACE_INVADERS_SCROLLING_BG_LAYER
#define SPACE_INVADERS_SCROLLING_BG_LAYER
#include <iostream>
#include "ScrollingBackground.h"
#include "layers_scenes_transitions_nodes/CCLayer.h"

class ScrollingBgLayer : public cocos2d::CCLayer
{
public:
	ScrollingBgLayer(float speed);
	~ScrollingBgLayer();
	void Update();

	//---------------  Variables  ------------------
	ScrollingBackground* space;

};
#endif