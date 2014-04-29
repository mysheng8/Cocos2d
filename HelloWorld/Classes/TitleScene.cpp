#include "TitleScene.h"
#include "resource.h"
#include "VisibleRect.h"
#include "GameScene.h"
#include "MenuLayers.h"



const std::string g_TitleMenu[] = {
    "New Game",
	"High Score",
    "Quit Game"
};

TitleScene::TitleScene()
{
	CCScene::init();
	m_pItemMenu = CCMenu::create();

    // add menu new game

	CCLabelBMFont *newlabel = CCLabelBMFont::create(g_TitleMenu[0].c_str(),s_pPathMenuFont);
    CCMenuItemLabel* pNewItem = CCMenuItemLabel::create(newlabel, this, menu_selector(TitleScene::startGame));
    m_pItemMenu->addChild(pNewItem, 1);
	pNewItem->setPosition( ccp( VisibleRect::center().x, (VisibleRect::top().y - 3* VisibleRect::lineSpace()) ));

	// add rank quit
	CCLabelBMFont* ranklabel = CCLabelBMFont::create(g_TitleMenu[1].c_str(), s_pPathMenuFont); 
    CCMenuItemLabel* pRanktItem = CCMenuItemLabel::create(ranklabel, this, menu_selector(TitleScene::rankCallback));
    m_pItemMenu->addChild(pRanktItem, 2);
    pRanktItem->setPosition( ccp( VisibleRect::center().x, (VisibleRect::top().y - 4 * VisibleRect::lineSpace()) ));

	// add menu quit
	CCLabelBMFont* quitlabel = CCLabelBMFont::create(g_TitleMenu[2].c_str(), s_pPathMenuFont); 
    CCMenuItemLabel* pQuitItem = CCMenuItemLabel::create(quitlabel, this, menu_selector(TitleScene::closeCallback));
    m_pItemMenu->addChild(pQuitItem, 2);
    pQuitItem->setPosition( ccp( VisibleRect::center().x, (VisibleRect::top().y - 5 * VisibleRect::lineSpace()) ));
	
	
    m_pItemMenu->setContentSize(CCSizeMake(VisibleRect::getVisibleRect().size.width, 3 * (VisibleRect::lineSpace())));
    m_pItemMenu->setPosition(CCPointZero);
	addChild(m_pItemMenu,1);

	    // add "HelloWorld" splash screen"
    CCSprite* pSprite = CCSprite::create(s_pPathBG);
    pSprite->setPosition(ccp( VisibleRect::center().x,  VisibleRect::center().y ));
    addChild(pSprite, 0);
	setAnchorPoint(ccp(0,0));
	setScale(VisibleRect::layerScale());
	
	
}

TitleScene::~TitleScene()
{
}

void TitleScene::startGame(CCObject* pSender)
{
	CCDirector* pDirector = CCDirector::sharedDirector();
    // run
	GameScene::sharedGameScene().startGame();
}

void TitleScene::rankCallback(CCObject* pSender)
{
	RankLayer *next=new RankLayer();
	next->rank();
	next->addButtons(false);
	addChild(next,1);
	next->jumpIn();
	next->release();
}

void TitleScene::closeCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void TitleScene::keyBackClicked()
{
    CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
