#include "HelloWorldScene.h"
#include "CheckerBoard.h"

USING_NS_CC;

CCScene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);


	//boardLayer->autorelease();
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                        "CloseNormal.png",
                                        "CloseSelected.png",
                                        this,
                                        menu_selector(HelloWorld::menuCloseCallback));
    
	pCloseItem->setPosition(ccp(origin.x + visibleSize.width - pCloseItem->getContentSize().width/2 ,
                                origin.y + pCloseItem->getContentSize().height/2));

	CCMenuItemFont *pauseItem = CCMenuItemFont::create("Pause", this, menu_selector(HelloWorld::Pause) );

    pauseItem->setFontSizeObj(30);
    pauseItem->setFontName("Marker Felt");
	pauseItem->setPosition(ccp(origin.x +pauseItem->getContentSize().width/2 ,origin.y + visibleSize.height-pauseItem->getContentSize().height/2));
	CCMenuItemFont *resumeItem = CCMenuItemFont::create("Resume", this, menu_selector(HelloWorld::Resume) );

    resumeItem->setFontSizeObj(30);
    resumeItem->setFontName("Marker Felt");
	resumeItem->setPosition(ccp(origin.x +resumeItem->getContentSize().width/2 ,origin.y + visibleSize.height-pauseItem->getContentSize().height-resumeItem->getContentSize().height/2));
    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(pCloseItem, pauseItem, resumeItem,NULL);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    CCLabelTTF* pLabel = CCLabelTTF::create("Hello World", "Arial", 24);
    
    // position the label on the center of the screen
    pLabel->setPosition(ccp(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - pLabel->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(pLabel, 1);

    // add "HelloWorld" splash screen"
    CCSprite* pSprite = CCSprite::create("HelloWorld.png");

    // position the sprite on the center of the screen
    pSprite->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(pSprite, 0);
    
    return true;
}

void HelloWorld::Pause(CCObject* pSender)
{
	CCDirector::sharedDirector()->pause();
}

void HelloWorld::Resume(CCObject* pSender)
{
	CCDirector::sharedDirector()->resume();
}

void HelloWorld::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
