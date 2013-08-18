#include "MenuScene.h"
#include "resource.h"
#include "VisibleRect.h"
#include "GameScene.h"

#define LINE_SPACE          80

const std::string g_Menu[3] = {
    "New Game",
	"Resume Game",
    "Quit Game",
};


MenuScene::MenuScene()
{
	m_pItemMenu = CCMenu::create();

    // add menu new game

	CCLabelBMFont* newlabel = CCLabelBMFont::create(g_Menu[0].c_str(), s_pPathMenuFont);     
    CCMenuItemLabel* pNewItem = CCMenuItemLabel::create(newlabel, this, menu_selector(MenuScene::newCallback));
    m_pItemMenu->addChild(pNewItem, 2);
    pNewItem->setPosition( ccp( VisibleRect::center().x, (VisibleRect::top().y - 1* LINE_SPACE) ));

	// add menu new game
	CCLabelBMFont* resumelabel = CCLabelBMFont::create(g_Menu[1].c_str(), s_pPathMenuFont);     
    CCMenuItemLabel* pResumeItem = CCMenuItemLabel::create(resumelabel, this, menu_selector(MenuScene::resumeCallback));
    m_pItemMenu->addChild(pResumeItem, 2);
    pResumeItem->setPosition( ccp( VisibleRect::center().x, (VisibleRect::top().y - 2* LINE_SPACE) ));

	// add menu quit
	CCLabelBMFont* quitlabel = CCLabelBMFont::create(g_Menu[2].c_str(), s_pPathMenuFont);     
    CCMenuItemLabel* pQuitItem = CCMenuItemLabel::create(quitlabel, this, menu_selector(MenuScene::quitCallback));
    m_pItemMenu->addChild(pQuitItem, 2);
    pQuitItem->setPosition( ccp( VisibleRect::center().x, (VisibleRect::top().y - 3 * LINE_SPACE) ));



    m_pItemMenu->setContentSize(CCSizeMake(VisibleRect::getVisibleRect().size.width, 3 * (LINE_SPACE)));
    m_pItemMenu->setPosition(CCPointZero);
    addChild(m_pItemMenu,1);

	
	    // add "HelloWorld" splash screen"
    CCSprite* pSprite = CCSprite::create(s_pPathBG);
    pSprite->setPosition(ccp( VisibleRect::center().x,  VisibleRect::center().y ));
    addChild(pSprite, 0);
}
MenuScene::~MenuScene()
{
}

void MenuScene::newCallback(CCObject* pSender)
{
	CCNode *pNode=getParent();
    GameScene *pScene = static_cast<GameScene*>(pNode);

    // run
	pScene->startGame();
}

void MenuScene::resumeCallback(CCObject* pSender)
{
	CCNode *pNode=getParent();
    GameScene *pScene = static_cast<GameScene*>(pNode);

    // run
	pScene->resumeGame();
}

void MenuScene::quitCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
