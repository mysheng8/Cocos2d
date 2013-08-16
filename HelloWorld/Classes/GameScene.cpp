#include "GameScene.h"
#include "resource.h"
#include "VisibleRect.h"
#include "CheckerBoard.h"

USING_NS_CC;


// on "init" you need to initialize your instance
GameScene::GameScene()
{
	CCLayer *mLayer= CCLayer::create();
	addChild(mLayer);
	mLayer->release();
	CheckerBoard *boardLayer = CheckerBoard::create();
	addChild(boardLayer);
	boardLayer->release();

	


	CCMenuItemImage *pCloseItem = CCMenuItemImage::create(s_pPathCloseNormal, s_pPathCloseSelect, this, menu_selector(GameScene::menuCallback) );
    CCMenu* pMenu =CCMenu::create(pCloseItem, NULL);

    pMenu->setPosition( CCPointZero );
	mLayer->addChild(pMenu, 1);
    // add "HelloWorld" splash screen"
    CCSprite* pSprite = CCSprite::create(s_pPathBG);

    // position the sprite on the center of the screen
    pSprite->setPosition(ccp(VisibleRect::center().x,  VisibleRect::center().y));

    // add the sprite as a child to this layer
    mLayer->addChild(pSprite, 0);
}


void GameScene::menuCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void GameScene::runThisTest()
{
    CCDirector::sharedDirector()->replaceScene(this);
}