#include "MenuScene.h"
#include "resource.h"
#include "VisibleRect.h"
#include "GameScene.h"
#include <stdio.h>
#include <string>
#include "SimpleAudioEngine.h"
#include "TitleScene.h"

using namespace CocosDenshion;



#define LINE_SPACE          80

const std::string g_Menu[] = {
	"Resume",
	"Restart",
	"Option",
    "Back Menu",
};

const float volume[]={1.0f,0.75f,0.5f,0.25f,0.0f};
const char s_pClick[] = "audio/click.wav";




PopoutMenu::PopoutMenu()
{
	setPosition(0,6*LINE_SPACE);

}
PopoutMenu::~PopoutMenu()
{

}



void PopoutMenu::jumpIn()
{
	CCActionInterval*  drop = CCMoveBy::create(0.5f, ccp( 0,  -6*LINE_SPACE));
	CCActionInterval*  move_ease_in = CCEaseElasticOut::create((CCActionInterval*)(drop->copy()->autorelease()) , 0.5f);
	runAction(move_ease_in);
}

void PopoutMenu::jumpOut()
{
	CCActionInterval*  drop = CCMoveBy::create(0.3f, ccp( 0,  6*LINE_SPACE));
	CCActionInterval* move_ease_in = CCEaseIn::create((CCActionInterval*)(drop->copy()->autorelease()) , 2.0f);
	runAction(move_ease_in);
}





MenuScene::MenuScene()
{
	m_sound=0;
	m_music=0;
	SimpleAudioEngine::sharedEngine()->preloadEffect( s_pClick );
	m_pMainMenu = CCMenu::create();

	

	// add menu resume game
	CCLabelBMFont* resumelabel = CCLabelBMFont::create(g_Menu[0].c_str(), s_pPathMenuFont);     
    CCMenuItemLabel* pResumeItem = CCMenuItemLabel::create(resumelabel, this, menu_selector(MenuScene::resumeCallback));
    m_pMainMenu->addChild(pResumeItem, 2);
    pResumeItem->setPosition( ccp( VisibleRect::center().x, (VisibleRect::top().y - 2* LINE_SPACE) ));



    // add menu new game

	CCLabelBMFont* newlabel = CCLabelBMFont::create(g_Menu[1].c_str(), s_pPathMenuFont);     
    CCMenuItemLabel* pNewItem = CCMenuItemLabel::create(newlabel, this, menu_selector(MenuScene::newCallback));
    m_pMainMenu->addChild(pNewItem, 2);
    pNewItem->setPosition( ccp( VisibleRect::center().x, (VisibleRect::top().y - 1* LINE_SPACE) ));


	// add option
	CCLabelBMFont* oplabel = CCLabelBMFont::create(g_Menu[2].c_str(), s_pPathMenuFont);     
    CCMenuItemLabel* pOptionItem = CCMenuItemLabel::create(oplabel, this, menu_selector(MenuScene::optionCallback));
    m_pMainMenu->addChild(pOptionItem, 2);
    pOptionItem->setPosition( ccp( VisibleRect::center().x, (VisibleRect::top().y - 3 * LINE_SPACE) ));

	

	// add menu quit
	CCLabelBMFont* quitlabel = CCLabelBMFont::create(g_Menu[3].c_str(), s_pPathMenuFont);     
    CCMenuItemLabel* pQuitItem = CCMenuItemLabel::create(quitlabel, this, menu_selector(MenuScene::quitCallback));
    m_pMainMenu->addChild(pQuitItem, 2);
    pQuitItem->setPosition( ccp( VisibleRect::center().x, (VisibleRect::top().y - 4 * LINE_SPACE) ));




	CCLabelBMFont* item1Label = CCLabelBMFont::create("100%", s_pPathScoreFont);
	CCMenuItemLabel* item1 = CCMenuItemLabel::create(item1Label);
	CCLabelBMFont* item2Label = CCLabelBMFont::create("75%", s_pPathScoreFont);
	CCMenuItemLabel* item2 = CCMenuItemLabel::create(item2Label);
	CCLabelBMFont* item3Label = CCLabelBMFont::create("50%", s_pPathScoreFont);
	CCMenuItemLabel* item3 = CCMenuItemLabel::create(item3Label);
	CCLabelBMFont* item4Label = CCLabelBMFont::create("25%", s_pPathScoreFont);
	CCMenuItemLabel* item4 = CCMenuItemLabel::create(item4Label);
	CCLabelBMFont* item5Label = CCLabelBMFont::create("Off", s_pPathScoreFont);
	CCMenuItemLabel* item5 = CCMenuItemLabel::create(item5Label);

	CCLabelBMFont* item6Label = CCLabelBMFont::create("100%", s_pPathScoreFont);
	CCMenuItemLabel* item6 = CCMenuItemLabel::create(item6Label);
	CCLabelBMFont* item7Label = CCLabelBMFont::create("75%", s_pPathScoreFont);
	CCMenuItemLabel* item7 = CCMenuItemLabel::create(item7Label);
	CCLabelBMFont* item8Label = CCLabelBMFont::create("50%", s_pPathScoreFont);
	CCMenuItemLabel* item8 = CCMenuItemLabel::create(item8Label);
	CCLabelBMFont* item9Label = CCLabelBMFont::create("25%", s_pPathScoreFont);
	CCMenuItemLabel* item9 = CCMenuItemLabel::create(item9Label);
	CCLabelBMFont* item10Label = CCLabelBMFont::create("Off", s_pPathScoreFont);
	CCMenuItemLabel* item10 = CCMenuItemLabel::create(item10Label);



	CCLabelBMFont* soundlabel = CCLabelBMFont::create("Sound", s_pPathScoreFont);
	CCMenuItemLabel* sound = CCMenuItemLabel::create(soundlabel);
    //sound->setEnabled(false);
    CCMenuItemToggle* soundVolume = CCMenuItemToggle::createWithTarget(this, 
                                                                menu_selector(MenuScene::setSoundCallback), 
																item1,
																item2,
																item3,
																item4,
                                                                item5,
                                                                NULL );
	
	CCLabelBMFont* musiclabel = CCLabelBMFont::create("Music", s_pPathScoreFont);
	CCMenuItemLabel* music = CCMenuItemLabel::create(musiclabel);
    //music->setEnabled(false);
    CCMenuItemToggle *musicVolume = CCMenuItemToggle::createWithTarget(this, 
                                                                menu_selector(MenuScene::setMusicCallback),
																item6,
																item7,
																item8,
																item9,
                                                                item10,
                                                                NULL );
    
	CCLabelBMFont* backlabel = CCLabelBMFont::create("Back", s_pPathScoreFont);
	CCMenuItemLabel* back = CCMenuItemLabel::create(backlabel, this, menu_selector(MenuScene::backCallback) );
	m_pSubMenu = CCMenu::create(
                  sound, soundVolume,
                  music, musicVolume,
                  back, NULL ); // 9 items.
    
    m_pSubMenu->alignItemsInColumns(2, 2, 1, NULL);

	m_pSubMenu->retain();



    m_pMainMenu->setContentSize(CCSizeMake(VisibleRect::getVisibleRect().size.width, 5 * (LINE_SPACE)));
    m_pMainMenu->setPosition(CCPointZero);
    addChild(m_pMainMenu,1);
	m_pMainMenu->retain();

	
	    // add "HelloWorld" splash screen"
    CCSprite* pSprite = CCSprite::create(s_pPathMenuBG);
    pSprite->setPosition(ccp( VisibleRect::center().x,  VisibleRect::center().y ));
    addChild(pSprite, 0);
}
MenuScene::~MenuScene()
{
	m_pSubMenu->release();
	m_pMainMenu->release();
}

void MenuScene::newCallback(CCObject* pSender)
{
	CCNode *pNode=getParent();
    GameScene *pScene = static_cast<GameScene*>(pNode);

    // run
	pScene->menuLayer->jumpOut();
	pScene->restart();

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
    CCScene *pScene =new TitleScene();
	
    // run
    CCDirector::sharedDirector()->replaceScene(pScene);
	pScene->release();
}

void MenuScene::optionCallback(CCObject* pSender)
{
	removeChild(m_pMainMenu);
	addChild(m_pSubMenu);
}

void MenuScene::backCallback(CCObject* pSender)
{
	removeChild(m_pSubMenu);
	addChild(m_pMainMenu);
}

void MenuScene::setSoundCallback(CCObject* pSender)
{
	m_sound=(m_sound+1)%5;
	SimpleAudioEngine::sharedEngine()->setEffectsVolume(volume[m_sound]);
	SimpleAudioEngine::sharedEngine()->playEffect(s_pClick);
}

void MenuScene::setMusicCallback(CCObject* pSender)
{
	m_music=(m_music+1)%5;
	SimpleAudioEngine::sharedEngine()->setEffectsVolume(volume[m_music]);
	SimpleAudioEngine::sharedEngine()->playEffect(s_pClick);
}

RankScene::RankScene()
{

}

RankScene::~RankScene()
{

}

void RankScene::rank(int input)
{

}

void RankScene::inputName()
{

}