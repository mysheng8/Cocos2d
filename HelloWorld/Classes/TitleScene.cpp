#include "TitleScene.h"
#include "resource.h"
#include "VisibleRect.h"
#include "GameScene.h"

#define LINE_SPACE          80

const std::string g_TitleMenu[2] = {
    "New Game",
    "Quit Game",
};

CCScene* TitleScene::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
	CCLayer * pLayer = new TitleScene();

    scene->addChild(pLayer);

	pLayer->release();

    return scene;
}

TitleScene::TitleScene()
{
	m_pItemMenu = CCMenu::create();

    // add menu new game

	CCLabelBMFont *newlabel = CCLabelBMFont::create(g_TitleMenu[0].c_str(),s_pPathMenuFont);
    CCMenuItemLabel* pNewItem = CCMenuItemLabel::create(newlabel, this, menu_selector(TitleScene::startGame));
    m_pItemMenu->addChild(pNewItem, 1);
    pNewItem->setPosition( ccp( VisibleRect::center().x, (VisibleRect::top().y - 1* LINE_SPACE) ));
	
	// add menu quit
	CCLabelBMFont* quitlabel = CCLabelBMFont::create(g_TitleMenu[1].c_str(), s_pPathMenuFont); 
    CCMenuItemLabel* pQuitItem = CCMenuItemLabel::create(quitlabel, this, menu_selector(TitleScene::closeCallback));
    m_pItemMenu->addChild(pQuitItem, 2);
    pQuitItem->setPosition( ccp( VisibleRect::center().x, (VisibleRect::top().y - 2 * LINE_SPACE) ));
	
	
    m_pItemMenu->setContentSize(CCSizeMake(VisibleRect::getVisibleRect().size.width, 2 * (LINE_SPACE)));
    m_pItemMenu->setPosition(CCPointZero);
	addChild(m_pItemMenu,1);

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
	pScene->startGame();
	pScene->release();
}


void TitleScene::closeCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
