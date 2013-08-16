#include "TitleScene.h"
#include "resource.h"
#include "VisibleRect.h"
#include "GameScene.h"

#define LINE_SPACE          40
static CCPoint s_tCurPos = CCPointZero;

const std::string g_Menu[3] = {
    "New Game",
    "Quit Game",
};

CCScene* TitleScene::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
	CCLayer * pLayer = new TitleScene();

    scene->addChild(pLayer);

    return scene;
}

TitleScene::TitleScene()
{
	CCMenuItemImage *pCloseItem = CCMenuItemImage::create(s_pPathCloseNormal, s_pPathCloseSelect, this, menu_selector(TitleScene::closeCallback) );
    CCMenu* pMenu =CCMenu::create(pCloseItem, NULL);

    pMenu->setPosition( CCPointZero );
    pCloseItem->setPosition(ccp( VisibleRect::right().x - 30, VisibleRect::top().y - 30));

	m_pItemMenu = CCMenu::create();

    // add menu new game
	CCLabelTTF* newlabel = CCLabelTTF::create(g_Menu[0].c_str(), "Marker Felt", 24);     
    CCMenuItemLabel* pNewItem = CCMenuItemLabel::create(newlabel, this, menu_selector(TitleScene::startGame));
    m_pItemMenu->addChild(pNewItem, 1);
    pNewItem->setPosition( ccp( VisibleRect::center().x, (VisibleRect::top().y - 2* LINE_SPACE) ));

	// add menu quit
	CCLabelTTF* quitlabel = CCLabelTTF::create(g_Menu[1].c_str(), "Marker Felt", 24);     
    CCMenuItemLabel* pQuitItem = CCMenuItemLabel::create(quitlabel, this, menu_selector(TitleScene::closeCallback));
    m_pItemMenu->addChild(pQuitItem, 2);
    pQuitItem->setPosition( ccp( VisibleRect::center().x, (VisibleRect::top().y - 3 * LINE_SPACE) ));



    m_pItemMenu->setContentSize(CCSizeMake(VisibleRect::getVisibleRect().size.width, 3 * (LINE_SPACE)));
    m_pItemMenu->setPosition(s_tCurPos);
    addChild(m_pItemMenu,1);

    addChild(pMenu, 1);

	
	    // add "HelloWorld" splash screen"
    CCSprite* pSprite = CCSprite::create(s_pPathBG);
    pSprite->setPosition(ccp( VisibleRect::center().x,  VisibleRect::center().y ));
    addChild(pSprite, 0);
	
}

TitleScene::~TitleScene()
{
}

void TitleScene::startGame(CCObject* pSender)
{
	CCDirector* pDirector = CCDirector::sharedDirector();
    GameScene *pScene = new GameScene();

    // run
	pScene->runThisTest();
	pScene->release();
}


void TitleScene::closeCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
