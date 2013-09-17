#include "MenuScene.h"
#include "resource.h"
#include "VisibleRect.h"
#include "GameScene.h"
#include "SimpleAudioEngine.h"
#include "TitleScene.h"
#include<stdio.h>
#include<fstream>
using namespace CocosDenshion;



#define LINE_SPACE          80
#define RANK_SPACE          30
const std::string g_PauseMenu[] = {
	"Resume",
	"Restart",
	"Option",
    "Main Menu"
};

const float volume[]={1.0f,0.75f,0.5f,0.25f,0.0f};
const char s_pClick[] = "audio/click.wav";

const std::string g_GameOverMenu[] = {
    "Submit Name",
    "Restart",
	"Back To Menu"
};

static CCRect getRect(CCNode * pNode)
{
    CCRect rc;
    rc.origin = pNode->getPosition();
    rc.size = pNode->getContentSize();
    rc.origin.x -= rc.size.width / 2;
    rc.origin.y -= rc.size.height / 2;
    return rc;
}

PopoutMenu::PopoutMenu()
{
    CCSprite* pSprite = CCSprite::create(s_pPathMenuBG);
    pSprite->setPosition(ccp( VisibleRect::center().x,  VisibleRect::center().y ));
    addChild(pSprite, 0);
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

void PopoutMenu::restartCallback(CCObject* pSender)
{
	CCNode *pNode=getParent();
    GameScene *pScene = static_cast<GameScene*>(pNode);

    // run
	pScene->restart();
}

void PopoutMenu::resumeCallback(CCObject* pSender)
{
	CCNode *pNode=getParent();
    GameScene *pScene = static_cast<GameScene*>(pNode);

    // run
	pScene->resumeGame();
}

void PopoutMenu::quitCallback(CCObject* pSender)
{
    CCScene *pScene =new TitleScene();
	
    // run
    CCDirector::sharedDirector()->replaceScene(pScene);
	pScene->release();
}

MenuScene::MenuScene()
{
	m_sound=0;
	m_music=0;
	SimpleAudioEngine::sharedEngine()->preloadEffect( s_pClick );
	m_pMainMenu = CCMenu::create();

	





    // add menu new game

	CCLabelBMFont* newlabel = CCLabelBMFont::create(g_PauseMenu[1].c_str(), s_pPathMenuFont);     
    CCMenuItemLabel* pNewItem = CCMenuItemLabel::create(newlabel, this, menu_selector(MenuScene::restartCallback));
    m_pMainMenu->addChild(pNewItem, 2);
    pNewItem->setPosition( ccp( VisibleRect::center().x, (VisibleRect::top().y - 2* LINE_SPACE) ));

	// add menu resume game
	CCLabelBMFont* resumelabel = CCLabelBMFont::create(g_PauseMenu[0].c_str(), s_pPathMenuFont);     
    CCMenuItemLabel* pResumeItem = CCMenuItemLabel::create(resumelabel, this, menu_selector(MenuScene::resumeCallback));
    m_pMainMenu->addChild(pResumeItem, 2);
    pResumeItem->setPosition( ccp( VisibleRect::center().x, (VisibleRect::top().y - 3* LINE_SPACE) ));


	// add option
	CCLabelBMFont* oplabel = CCLabelBMFont::create(g_PauseMenu[2].c_str(), s_pPathMenuFont);     
    CCMenuItemLabel* pOptionItem = CCMenuItemLabel::create(oplabel, this, menu_selector(MenuScene::optionCallback));
    m_pMainMenu->addChild(pOptionItem, 2);
    pOptionItem->setPosition( ccp( VisibleRect::center().x, (VisibleRect::top().y - 4 * LINE_SPACE) ));


	// add menu quit
	CCLabelBMFont* quitlabel = CCLabelBMFont::create(g_PauseMenu[3].c_str(), s_pPathMenuFont);     
    CCMenuItemLabel* pQuitItem = CCMenuItemLabel::create(quitlabel, this, menu_selector(MenuScene::quitCallback));
    m_pMainMenu->addChild(pQuitItem, 2);
    pQuitItem->setPosition( ccp( VisibleRect::center().x, (VisibleRect::top().y - 5 * LINE_SPACE) ));




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
}
MenuScene::~MenuScene()
{
	m_pSubMenu->release();
	m_pMainMenu->release();
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

GameOverLayer::GameOverLayer(GameScene *parent)
	:pScene(parent)
{
	CCLabelBMFont* title = CCLabelBMFont::create("Game Over", s_pPathMenuFont); 
	title->setPosition( ccp( VisibleRect::center().x, (VisibleRect::top().y - 1* LINE_SPACE) ));
	addChild(title, 1);

	if(pScene)
	{
		char string[18] = {0};
		sprintf(string, "Score: %d",pScene->getScore());
		CCLabelBMFont* score = CCLabelBMFont::create(string, s_pPathScoreFont); 
		score->setPosition( ccp( VisibleRect::center().x, (VisibleRect::top().y - 2* LINE_SPACE) ));
		addChild(score, 1);
	}

	m_pItemMenu = CCMenu::create();

	// add submit game item
	CCLabelBMFont* submitlabel = CCLabelBMFont::create(g_GameOverMenu[0].c_str(), s_pPathScoreFont);     
    pSubmitItem = CCMenuItemLabel::create(submitlabel, this, menu_selector(GameOverLayer::submitCallback));
    m_pItemMenu->addChild(pSubmitItem, 2);
    pSubmitItem->setPosition( ccp( VisibleRect::center().x, (VisibleRect::top().y - 3* LINE_SPACE) ));
	
	// add restart game item
	CCLabelBMFont* newlabel = CCLabelBMFont::create(g_GameOverMenu[1].c_str(), s_pPathScoreFont);     
    CCMenuItemLabel* pNewItem = CCMenuItemLabel::create(newlabel, this, menu_selector(GameOverLayer::restartCallback));
    m_pItemMenu->addChild(pNewItem, 2);
    pNewItem->setPosition( ccp( VisibleRect::center().x, (VisibleRect::top().y - 4* LINE_SPACE) ));

	// add back to menu item
	CCLabelBMFont* quitlabel = CCLabelBMFont::create(g_GameOverMenu[2].c_str(), s_pPathScoreFont);     
    CCMenuItemLabel* pQuitItem = CCMenuItemLabel::create(quitlabel, this, menu_selector(GameOverLayer::quitCallback));
    m_pItemMenu->addChild(pQuitItem, 2);
    pQuitItem->setPosition( ccp( VisibleRect::center().x, (VisibleRect::top().y - 5 * LINE_SPACE) ));

    m_pItemMenu->setContentSize(CCSizeMake(VisibleRect::getVisibleRect().size.width, 3 * (LINE_SPACE)));
    m_pItemMenu->setPosition(CCPointZero);
    addChild(m_pItemMenu,1);


}

GameOverLayer::~GameOverLayer()
{

}

void GameOverLayer::submitCallback(CCObject * pSender)
{
	CCNode *pNode=getParent();
    GameScene *pScene = static_cast<GameScene*>(pNode);

	//run
	PopoutMenu *next=new InputLayer();
	pScene->switchMenu(next);

}

void GameOverLayer::setSubmitEnable(bool canSubmit)
{
	pSubmitItem->setEnabled(false);
}
//////////////////////////////////////////////////////////////////////////
// implement InputLayer
//////////////////////////////////////////////////////////////////////////

InputLayer::InputLayer()
{
    setTouchEnabled(true);

	CCLabelBMFont* title = CCLabelBMFont::create("Submit your name", s_pPathScoreFont); 
	title->setPosition( ccp( VisibleRect::center().x, (VisibleRect::top().y - 1* LINE_SPACE) ));
	addChild(title, 1);

    // add CCTextFieldTTF
    CCSize s = CCDirector::sharedDirector()->getWinSize();

    CCTextFieldTTF * pTextField = CCTextFieldTTF::textFieldWithPlaceHolder("<click here for input>",
        s_pPathInputFont,
        30);
	pTextField->setPosition( ccp( VisibleRect::center().x, (VisibleRect::top().y - 2* LINE_SPACE) ));
    addChild(pTextField,1);

    m_pTrackNode = pTextField;

	CCMenu *pMenu=CCMenu::create();

	// add submit game item
	CCLabelBMFont* submitlabel = CCLabelBMFont::create("back", s_pPathScoreFont);     
    CCMenuItemLabel* pSubmitItem = CCMenuItemLabel::create(submitlabel, this, menu_selector(InputLayer::backCallback));
    pMenu->addChild(pSubmitItem, 4);
    pSubmitItem->setPosition( ccp( VisibleRect::center().x - LINE_SPACE, (VisibleRect::top().y - 5* LINE_SPACE) ));
	
	// add restart game item
	CCLabelBMFont* newlabel = CCLabelBMFont::create("next", s_pPathScoreFont);     
    CCMenuItemLabel* pNewItem = CCMenuItemLabel::create(newlabel, this, menu_selector(InputLayer::nextCallback));
    pMenu->addChild(pNewItem, 4);
    pNewItem->setPosition( ccp( VisibleRect::center().x + LINE_SPACE, (VisibleRect::top().y - 5* LINE_SPACE) ));
	pMenu->setContentSize(CCSizeMake(VisibleRect::getVisibleRect().size.width, 2 * (LINE_SPACE)));
    pMenu->setPosition(CCPointZero);
	
	addChild(pMenu,1);
}

void InputLayer::registerWithTouchDispatcher()
{
    CCDirector* pDirector = CCDirector::sharedDirector();
    pDirector->getTouchDispatcher()->addTargetedDelegate(this, 0, false);
}

void InputLayer::keyboardWillShow(CCIMEKeyboardNotificationInfo& info)
{
    CCLOG("TextInputTest:keyboardWillShowAt(origin:%f,%f, size:%f,%f)",
        info.end.origin.x, info.end.origin.y, info.end.size.width, info.end.size.height);

    if (! m_pTrackNode)
    {
        return;
    }

    CCRect rectTracked = getRect(m_pTrackNode);
    CCLOG("TextInputTest:trackingNodeAt(origin:%f,%f, size:%f,%f)",
        rectTracked.origin.x, rectTracked.origin.y, rectTracked.size.width, rectTracked.size.height);

    // if the keyboard area doesn't intersect with the tracking node area, nothing need to do.
    if (! rectTracked.intersectsRect(info.end))
    {
        return;
    }

    // assume keyboard at the bottom of screen, calculate the vertical adjustment.
    float adjustVert = info.end.getMaxY() - rectTracked.getMinY();
    CCLOG("TextInputTest:needAdjustVerticalPosition(%f)", adjustVert);

    // move all the children node of KeyboardNotificationLayer
    CCArray * children = getChildren();
    CCNode * node = 0;
    int count = children->count();
    CCPoint pos;
    for (int i = 0; i < count; ++i)
    {
        node = (CCNode*)children->objectAtIndex(i);
        pos = node->getPosition();
        pos.y += adjustVert;
        node->setPosition(pos);
    }
}

// CCLayer function

bool InputLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    CCLOG("++++++++++++++++++++++++++++++++++++++++++++");
    m_beginPos = pTouch->getLocation();    
    return true;
}

void InputLayer::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
    if (! m_pTrackNode)
    {
        return;
    }
    
    CCPoint endPos = pTouch->getLocation();    

    float delta = 5.0f;
    if (::abs(endPos.x - m_beginPos.x) > delta
        || ::abs(endPos.y - m_beginPos.y) > delta)
    {
        // not click
        m_beginPos.x = m_beginPos.y = -1;
        return;
    }

    // decide the trackNode is clicked.
    CCRect rect;
    CCPoint point = convertTouchToNodeSpaceAR(pTouch);
    CCLOG("KeyboardNotificationLayer:clickedAt(%f,%f)", point.x, point.y);

    rect = getRect(m_pTrackNode);
    CCLOG("KeyboardNotificationLayer:TrackNode at(origin:%f,%f, size:%f,%f)",
        rect.origin.x, rect.origin.y, rect.size.width, rect.size.height);

    this->onClickTrackNode(rect.containsPoint(point));
    CCLOG("----------------------------------");
}

void InputLayer::onClickTrackNode(bool bClicked)
{
    CCTextFieldTTF * pTextField = (CCTextFieldTTF*)m_pTrackNode;
    if (bClicked)
    {
        // TextFieldTTFTest be clicked
        CCLOG("TextFieldTTFDefaultTest:CCTextFieldTTF attachWithIME");
        pTextField->attachWithIME();
    }
    else
    {
        // TextFieldTTFTest not be clicked
        CCLOG("TextFieldTTFDefaultTest:CCTextFieldTTF detachWithIME");
        pTextField->detachWithIME();
    }
}


void InputLayer::nextCallback(CCObject * pSender)
{
	CCNode *pNode=getParent();
    GameScene *pScene = static_cast<GameScene*>(pNode);

	//run
	RankLayer *next=new RankLayer();
	CCTextFieldTTF *text=(CCTextFieldTTF*)m_pTrackNode;

	string name = string(text->getString());
	if(name.empty())
		return;
	if(name.size()>16)
		name.resize(16);
	next->rank(Rank(name,pScene->getScore()));
	next->addButtons(true);
	pScene->switchMenu(next);

}

void InputLayer::backCallback(CCObject * pSender)
{
	CCNode *pNode=getParent();
    GameScene *pScene = static_cast<GameScene*>(pNode);

	//run
	pScene->switchMenu(pScene->prevLayer);

}

RankLayer::RankLayer()
{
	scoreList = new list<Rank>();
}

RankLayer::~RankLayer()
{
	delete scoreList;
}

void RankLayer::onEnter()
{
	PopoutMenu::onEnter();

	char string[25] = {0};
	sprintf(string, "Score Rank");
	CCLabelBMFont* item = CCLabelBMFont::create(string, s_pPathScoreFont); 
	item->setPosition( ccp( VisibleRect::center().x, (VisibleRect::top().y - 1* LINE_SPACE) ));
	addChild(item, 1);

	unsigned int n(2);
	for (list<Rank>::iterator it=scoreList->begin();it!=scoreList->end();++it)
	{
		char string[28] = {0};
		sprintf(string, "%d.%s   %d",n-1, it->name.c_str(),it->score);
		CCLabelBMFont* item = CCLabelBMFont::create(string, s_pPathScoreFont); 
		item->setPosition( ccp( VisibleRect::center().x, (VisibleRect::top().y - 1* LINE_SPACE - n* RANK_SPACE) ));
		item->setScale(0.5f);
		addChild(item, 1);
		++n;
	}
}

void RankLayer::addButtons(bool isGameOver)
{
	CCMenu *pMenu=CCMenu::create();
	if(isGameOver)
	{
		// add back item
		CCLabelBMFont* submitlabel = CCLabelBMFont::create("back", s_pPathScoreFont);     
		CCMenuItemLabel* pSubmitItem = CCMenuItemLabel::create(submitlabel, this, menu_selector(RankLayer::backCallback));
		pMenu->addChild(pSubmitItem, 2);
		pSubmitItem->setPosition( ccp( VisibleRect::center().x - LINE_SPACE, (VisibleRect::top().y - 5* LINE_SPACE) ));
	
		// add next item
		CCLabelBMFont* newlabel = CCLabelBMFont::create("OK", s_pPathScoreFont);     
		CCMenuItemLabel* pNewItem = CCMenuItemLabel::create(newlabel, this, menu_selector(RankLayer::nextCallback));
		pMenu->addChild(pNewItem, 2);
		pNewItem->setPosition( ccp( VisibleRect::center().x + LINE_SPACE, (VisibleRect::top().y - 5* LINE_SPACE) ));
	}
	else
	{
		// add back item
		CCLabelBMFont* submitlabel = CCLabelBMFont::create("back", s_pPathScoreFont);     
		CCMenuItemLabel* pSubmitItem = CCMenuItemLabel::create(submitlabel, this, menu_selector(RankLayer::quitCallback));
		pMenu->addChild(pSubmitItem, 2);
		pSubmitItem->setPosition( ccp( VisibleRect::center().x, (VisibleRect::top().y - 5* LINE_SPACE) ));
	}
	pMenu->setContentSize(CCSizeMake(VisibleRect::getVisibleRect().size.width, 2 * (LINE_SPACE)));
    pMenu->setPosition(CCPointZero);

	addChild(pMenu);
}


bool comp(const Rank &lhs, const Rank &rhs)
{
 return lhs.score > rhs.score;
}

void RankLayer::rank()
{
	if(!scoreList->empty())
		scoreList->clear();
	string fullpath = CCFileUtils::sharedFileUtils()->fullPathForFilename(s_pPathExternalScore);
	fstream f(fullpath.c_str(),ios::in);
	if(f)
	{
		while(!f.eof())
		{
			char n[18]={0};
			int s(0);
			f>>n>>s;
			scoreList->push_back(Rank(string(n),s));
		}
	}
	f.close();
}

void RankLayer::rank(const Rank input)
{
	rank();
	scoreList->push_back(input);
	scoreList->sort(comp);

	if(scoreList->size()>8)
		scoreList->resize(8);
}

void RankLayer::nextCallback(CCObject * pSender)
{
	string fullpath = CCFileUtils::sharedFileUtils()->fullPathForFilename(s_pPathExternalScore);
	fstream f(fullpath.c_str(),ios::out);
	if(f)
	{
		for (list<Rank>::iterator it=scoreList->begin();it!=scoreList->end();++it)
		{
			char n[18] = {0};
			sprintf(n, "%s ",it->name.c_str());
			f<<n<<it->score;
		}
	}
	f.close();
	CCNode *pNode=getParent();
    GameScene *pScene = static_cast<GameScene*>(pNode);

	//run
	GameOverLayer *next=new GameOverLayer();

	next->setSubmitEnable(false);

	pScene->switchMenu(next);
}

void RankLayer::backCallback(CCObject * pSender)
{
	CCNode *pNode=getParent();
    GameScene *pScene = static_cast<GameScene*>(pNode);

	//run
	pScene->switchMenu(pScene->prevLayer);

}

void RankLayer::quitCallback(CCObject * pSender)
{
	jumpOut();
}