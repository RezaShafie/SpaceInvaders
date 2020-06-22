#include "AppDelegate.h"
#include "HelloWorldScene.h"
#include "MainMenuScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    CCDirector* pDirector = CCDirector::sharedDirector();
    CCEGLView* pEGLView = CCEGLView::sharedOpenGLView();

    pDirector->setOpenGLView(pEGLView);
	
    // turn on display FPS
    pDirector->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);

	//bg music preload
	CocosDenshion::SimpleAudioEngine::sharedEngine()->
	preloadBackgroundMusic("sounds/MainMenu.ogg");

	CocosDenshion::SimpleAudioEngine::sharedEngine()->
		preloadBackgroundMusic("sounds/level1.ogg");

	//bg music play
	bool isPaused = CCUserDefault::sharedUserDefault() ->
		getBoolForKey("soundPaused");
	if (!isPaused)
		CocosDenshion::SimpleAudioEngine::sharedEngine()->
			playBackgroundMusic("sounds/MainMenu.ogg");

	//effects preload
	CocosDenshion::SimpleAudioEngine::sharedEngine() ->
	preloadEffect("sounds/enemyLaser1.ogg");
	CocosDenshion::SimpleAudioEngine::sharedEngine() ->
	preloadEffect("sounds/enemyLaser2.ogg");
	CocosDenshion::SimpleAudioEngine::sharedEngine() ->
	preloadEffect("sounds/enemyLaser3.ogg");
	CocosDenshion::SimpleAudioEngine::sharedEngine() ->
	preloadEffect("sounds/MenuTap.ogg");
	CocosDenshion::SimpleAudioEngine::sharedEngine()->
	preloadEffect("sounds/spaceshipLaser.ogg");
	CocosDenshion::SimpleAudioEngine::sharedEngine()->
		preloadEffect("sounds/explosion.ogg");
	


	//multi-resolution support
	pEGLView->setDesignResolutionSize(480, 320, kResolutionFixedWidth);

    // create a scene. it's an autorelease object
    CCScene *pScene = MainMenu::scene();

    // run
    pDirector->runWithScene(pScene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    CCDirector::sharedDirector()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause

	bool isPaused = CCUserDefault::sharedUserDefault() ->
		getBoolForKey("soundPaused");
	if (isPaused)
		CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    CCDirector::sharedDirector()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
	bool isPaused = CCUserDefault::sharedUserDefault() ->
		getBoolForKey("soundPaused");
	if(!isPaused)
		CocosDenshion::SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}
